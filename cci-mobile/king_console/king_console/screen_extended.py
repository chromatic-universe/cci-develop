import threading
from kivy.app import App
from kivy.clock import Clock , mainthread
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label
from kivy.uix.bubble import Bubble
from kivy.uix.actionbar import ActionBar , ActionButton
from kivy.uix.popup import Popup
from kivy.uix.button import Button
from kivy.lang import Builder
from kivy.uix.scrollview import ScrollView
from kivy.uix.textinput import TextInput
from kivy.uix.boxlayout import BoxLayout
from kivy.properties import StringProperty, ObjectProperty
from kivy.uix.treeview import TreeViewLabel
from kivy.uix.screenmanager import ScreenManager, \
	                               Screen ,\
	                               RiseInTransition ,\
								   SwapTransition , \
								   FallOutTransition , \
								   SlideTransition
from kivy.graphics import Color
from kivy.core.window import Window


#cci
import screen
from king_console import resource_factory \
	                     as resources
from king_console import kc_ping , \
						 kc_arp , \
						 kc_tcp , \
						 kc_nmap
import random
import datetime
from time import gmtime, strftime , sleep
import subprocess as proc
import Queue
from requests import put, get



# -------------------------------------------------------------------------------------------------
class DatalinkScreen( Screen ) :
					"""


					"""
					stop = threading.Event()

					accordion_id = ObjectProperty()
					console_arp_monitor_txt = ObjectProperty()
					start_monitor_btn = ObjectProperty()
					console_params = ObjectProperty()




					@staticmethod
					def _retr_resource( resource_id ) :
						"""

						:param resource_id:
						:return ui resource:
						"""

						return resources.const_resource_ids[resource_id]





					def _post_function_call( self , func , params ) :
						"""

						:param func:
						:param params:
						:return:
						"""

						package = ( func , params )
						App.get_running_app().dbq.put( package )




					def _post_payload( self , func , params ) :
						"""

						:param func:
						:param params:
						:return:
						"""

						if not App.get_running_app()._call_stack_debug :
							package = ( func , params )
							App.get_running_app().dbq.put( package )





					def _on_arp_monitor_start( self ) :
						"""

						:return:
						"""

						self.ids.console_arp_monitor_txt.text += '...standby....\n\n'
						if self.ids.start_monitor_btn.text == 'start' :

							thred = threading.Thread( target = self._on_arp_monitor ,
													  kwargs=dict( console=self.console_arp_monitor_txt ,
																   items = 15 ) )
							if thred :
								moniker = 'arp monitor console'
								thread_atom = { 'thread_id' : str( thred.ident ) ,
												'stop_alert'  : threading.Event() ,
												'instance' : thred
											  }
								App.get_running_app()._thrd.thrds[moniker] = thread_atom


							thred.start()

							self.ids.console_arp_monitor_txt.text += '...working.....'
							self.ids.start_monitor_btn.text = 'stop'
							self.ids.start_monitor_btn.color = [1,0,0.1]
						else :
							thr = App.get_running_app()._thrd.thrds['arp monitor console']
							thr['stop_alert'].set()
							self.ids.start_monitor_btn.text = 'start'
							self.ids.start_monitor_btn.color = [0,1,0.1]
							self.ids.console_arp_monitor_txt.text = ''




					@mainthread
					def _update_console_payload( self , content , params = '(no params)' ) :
						"""

						:param console slide:

						:return:
						"""


						self.ids.console_arp_monitor_txt.text = content + self.ids.console_arp_monitor_txt.text
						self.ids.console_params.text = params


						self.canvas.ask_update()




					def _on_arp_monitor( self , console = None , items = 15 ) :
						"""
						:param console:
						:param items:
						:return
						"""


						thr = App.get_running_app()._thrd.thrds['arp monitor console']
						alarm = thr['stop_alert']

						App.get_running_app()._logger.info( self.__class__.__name__ + '...on_arp_monitor'  )

						boiler = str()

						try :

							if alarm.isSet() :
									return
						except :
							pass


						try :

							cmd = ["su" ,
								   "-c" ,
								   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
								   "./king_console/kc_arp.pyo" ,
								   '-x' ,
								    '12'
								  ]
							"""
							cmd = [ "python" ,
								   "./king_console/kc_arp.py" ,
								   '-x' ,
								   '8'
								  ]
							"""
							try :
								while not alarm.isSet() :
									boiler = proc.check_output( cmd  )

									pos = boiler.find( '[]' )
									if pos != -1 :
										boiler = boiler[:pos]

									self._update_console_payload( boiler  )
									sleep( 1 )
							except proc.CalledProcessError as e :
								b_ret = False
						except Exception as e :
							b_ret = False
							App.get_running_app()._logger.error( e.message )


						self._post_function_call( 'insert_session_call' , [ App.get_running_app()._session_id ,
																			'datalink' ,
																			'arp_monitor' ,
							  												'(no_params)' ,
																			boiler ] )








# -------------------------------------------------------------------------------------------------
class NetworkScreen( Screen ) :
					"""


					"""
					stop = threading.Event()

					action_bar = ObjectProperty()
					accordion_id = ObjectProperty()
					_console_text = ObjectProperty()
					view_btn_a = ObjectProperty()
					action_view = ObjectProperty()


					@staticmethod
					def _retr_resource( resource_id ) :
						"""

						:param resource_id:
						:return ui resource:
						"""

						return resources.const_resource_ids[resource_id]





					def _post_function_call( self , func , params ) :
						"""

						:param func:
						:param params:
						:return:
						"""

						package = ( func , params )
						App.get_running_app().dbq.put( package )




					def _post_payload( self , func , params ) :
						"""

						:param func:
						:param params:
						:return:
						"""

						if not App.get_running_app()._call_stack_debug :
							package = ( func , params )
							App.get_running_app().dbq.put( package )




					def add_console(  self ,
								   content ,
								   tag  ) :
							"""
							:param parent:
							:param content:
							:param: console_count:
							:param tag:

							:return:
							"""

							layout = GridLayout( cols = 1 ,
												 orientation = 'horizontal'
												  )
							bar = Builder.load_string( self._retr_resource( 'dlg_action_bar_3' ) )
							bar.ids.view_btn_a.text = 'back'
							bar.ids.view_btn_a.bind( on_press =
								lambda a:App.get_running_app()._manip_extended_window() )
							layout.add_widget( bar )
							layout.add_widget( Label( text = tag  ,
													  color = [ 1, 0 , 0 , 1] ,
													  font_size = 16 ,
													  size_hint_y = 0.1 ) )

							scrolly = Builder.load_string( self._retr_resource( 'text_scroller' ) )
							tx = scrolly.children[0]
							tx.text = ''

							layout.add_widget( scrolly )
							layout.add_widget( Label( text =  datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S" )  ,
													font_size = 16  ,
													size_hint_y = 0.2 ,
													color = [ 1, 0 , 0 , 1] ) )

							return layout




# -------------------------------------------------------------------------------------------------
class AppDiscoveryScreen( Screen ) :
					"""


					"""
					stop = threading.Event()

					action_bar = ObjectProperty()
					accordion_id = ObjectProperty()
					_console_text = ObjectProperty()
					console_timestamp = ObjectProperty()


					@staticmethod
					def _retr_resource( resource_id ) :
						"""

						:param resource_id:
						:return ui resource:
						"""

						return resources.const_resource_ids[resource_id]





					def _post_function_call( self , func , params ) :
						"""

						:param func:
						:param params:
						:return:
						"""

						package = ( func , params )
						App.get_running_app().dbq.put( package )




					def _post_payload( self , func , params ) :
						"""

						:param func:
						:param params:
						:return:
						"""

						if not App.get_running_app()._call_stack_debug :
							package = ( func , params )
							App.get_running_app().dbq.put( package )




					def add_console(  self ,
								   content ,
								   tag  ) :
							"""
							:param parent:
							:param content:
							:param: console_count:
							:param tag:

							:return:
							"""

							layout = GridLayout( cols = 1 ,
												 orientation = 'horizontal'
												  )
							bar = Builder.load_string( self._retr_resource( 'dlg_action_bar_3' ) )
							bar.ids.view_btn_a.text = 'back'
							bar.ids.view_btn_a.bind( on_press =
								lambda a:App.get_running_app()._manip_extended_window() )
							layout.add_widget( bar )
							layout.add_widget( Label( text = tag  ,
													  color = [ 1, 0 , 0 , 1] ,
													  font_size = 16 ,
													  size_hint_y = 0.1 ) )

							scrolly = Builder.load_string( self._retr_resource( 'text_scroller' ) )
							tx = scrolly.children[0]
							tx.text = ''

							layout.add_widget( scrolly )
							layout.add_widget( Label( text =  datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S" )  ,
													font_size = 16  ,
													size_hint_y = 0.2 ,
													color = [ 1, 0 , 0 , 1] ) )

							return layout

