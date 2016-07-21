# screen.py     william k. johnson 2016
import threading
from kivy.app import App
from kivy.clock import Clock , mainthread
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label
from kivy.uix.bubble import Bubble
from kivy.uix.actionbar import ActionBar , ActionButton
from kivy.uix.popup import Popup
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.properties import StringProperty, ObjectProperty
from kivy.uix.treeview import TreeViewLabel
from kivy.uix.screenmanager import ScreenManager, \
	                               Screen ,\
	                               RiseInTransition ,\
								   SwapTransition , \
								   FallOutTransition , \
								   SlideTransition

#cci
from king_console import resource_factory \
	                     as resources
from king_console import kc_ping , \
						 kc_arp , \
						 kc_tcp , \
						 kc_nmap
import random
from time import gmtime, strftime , sleep
import subprocess as proc



# -------------------------------------------------------------------------------------------------
def uniqueid():
    seed = random.getrandbits(32)
    while True:
       yield seed
       seed += 1


# -------------------------------------------------------------------------------------------------
def add_console( self ,
				  parent ,
				  content ,
				  console_count ,
				  tag  ) :
				"""
				:param parent:
				:param content:
				:param: console_count:
				:param tag:

				:return:
				"""

				layout = GridLayout( cols = 1 ,
									 padding = [0 , 5 , 0 ,5]
									  )
				self._console_count += 1
				layout.add_widget( Label( text = tag + str( console_count ) ,
										color = [ 1, 0 , 0 , 1] ,
										font_size = 16 ,
										size_hint_y = 0.1 ) )

				scrolly = Builder.load_string( self._retr_resource( 'text_scroller' ) )
				tx = scrolly.children[0]
				tx.text = content
				layout.add_widget( scrolly )
				layout.add_widget( Label( text = strftime("%Y-%m-%d %H:%M:%S", gmtime()) ,
										font_size = 16  ,
										size_hint_y = 0.2 ,
										color = [ 1, 0 , 0 , 1] ) )
				parent.add_widget( layout )





# -------------------------------------------------------------------------------------------------
class TreeManagerLabel( TreeViewLabel ) :
				"""

				"""
				font_size = 18


# -------------------------------------------------------------------------------------------------
class ConsolePopup( Popup  ) :
				"""

				"""
				def on_press_dismiss( self , *args) :

					self.dismiss()

					return False


				def on_press_context( self , *args) :

					self.dismiss()

					return False


				def on_dismiss( self ) :
					pass



# -------------------------------------------------------------------------------------------------
# screens
class CciScreen( Screen ) :
				"""

				"""


				stop = threading.Event()

				accordion_id = ObjectProperty()
				_console_text = ObjectProperty()
				_console_count = 1


				@staticmethod
				def _retr_resource( resource_id ) :
					"""

					:param resource_id:
					:return ui resource:
					"""

					return resources.const_resource_ids[resource_id]



				def _on_show_history( self ) :
					"""

					:return:
					"""

					layout = GridLayout( orientation = 'horizontal' ,
									  cols = 1 )

					action_bar = Builder.load_string( self._retr_resource( 'dlg_action_bar' ) )
					layout.add_widget( action_bar )
					popup = ConsolePopup( title='console history' , content=layout, size=( 200,200 ) )
					btn = popup.content.children[0].children[0].children[0]
					btn.on_press = popup.on_press_context
					popup.open()



				def  _start_( self  , slug  , func ) :
					"""

					:param moniker:
					:param func:
					:return:
					"""
					#add thread object to manager
					thred = threading.Thread( target = self._thread_exec ,kwargs=dict( func=func ) )
					if thred :
						moniker = slug +  ' #'  + str( App.get_running_app()._console_count + 1 )
						thread_atom = { 'thread_id' : str( thred.ident ) ,
										'stop_alert'  : threading.Event() ,
										'instance' : thred
									  }
						App.get_running_app()._thrd.thrds[moniker] = thread_atom

					thred.start()



				def _on_ping_start( self ) :
					"""

					:return:
					"""

					#add thread object to manager
					self._start_( 'icmp ping console' , self.on_ping_ip_input )



				def _on_ping_subnet_start( self ) :
					"""

					:return:
					"""
					self._start_( 'icmp ping console' , self.on_ping_ip_subnet )


				def _on_nmap_fingerprint_start( self ) :
					"""

					:return:
					"""
					self._start_( 'nmap fingerprint console' , self.on_nmap_fingerprint )
						
						
				def _on_arp_start( self ) :
					"""

					:return:
					"""

					#add thread object to manager
					thred = threading.Thread( target = self._thread_exec ,kwargs=dict(func=self.on_arp_ip_input))
					if thred :
						moniker = 'arp console #'  + str( App.get_running_app()._console_count + 1 )
						thread_atom = { 'thread_id' : str( thred.ident ) ,
										'stop_alert'  : threading.Event() ,
										'instance' : thred
									  }
						App.get_running_app()._thrd.thrds[moniker] = thread_atom

					thred.start()



				def _on_arp_scan_start( self ) :
					"""

					:return:
					"""

					#add thread object to manager
					thred = threading.Thread( target = self._thread_exec ,kwargs=dict(func=self.on_arp_ip_scan))
					if thred :
						moniker = 'arp console #'  + str( App.get_running_app()._console_count + 1 )
						thread_atom = { 'thread_id' : str( thred.ident ) ,
										'stop_alert'  : threading.Event() ,
										'instance' : thred
									  }
						App.get_running_app()._thrd.thrds[moniker] = thread_atom

					thred.start()




				def _on_tcp_syn_scan_start( self ) :
					"""

					:return:
					"""

					#add thread object to manager
					thred = threading.Thread( target = self._thread_exec ,kwargs=dict( func=self.on_tcp_syn_ack_scan ) )
					if thred :
						moniker = 'tcp console #'  + str( App.get_running_app()._console_count + 1 )
						thread_atom = { 'thread_id' : str( thred.ident ) ,
										'stop_alert'  : threading.Event() ,
										'instance' : thred
									  }
						App.get_running_app()._thrd.thrds[moniker] = thread_atom

					thred.start()


				def _on_tcp_syn_scan_ports_start( self ) :
					"""

					:return:
					"""

					#add thread object to manager
					self._start_( 'tcp console scan' , self.on_tcp_syn_scan_ports )



				@mainthread
				def move_to_accordion_item( self , acc , tag = None ) :
					"""
					workaround for android nesting bug
					:param acc:
					:return:
					"""

					for child in acc.children :
						if child.title == 'cci-maelstrom' :
							child.collapse = False
							child.canvas.ask_update()

					self.ids.ping_btn.text = "execute"


				def _thread_exec( self , func = None ) :
					"""

					:return:
					"""


					if func == self.on_ping_ip_input :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_ping' )
						self._update_main_console( count=App.get_running_app()._console_count ,
												   moniker='icmp ping console #' )
						func()
					elif func == self.on_ping_ip_subnet :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_ping_subnet' )
						self._update_main_console( count=App.get_running_app()._console_count ,
												   threaded=True ,
												   func=func ,
												   moniker='icmp ping console #' )
					elif func == self.on_arp_ip_input :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_arp' )
						self._update_main_console( count=App.get_running_app()._console_count ,
												   moniker='arp console #' )
						func()
					elif func == self.on_arp_ip_scan :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_arp_scan' )
						self._update_main_console( count=App.get_running_app()._console_count ,
												   moniker='arp console #' )
						func()
					elif func == self.on_tcp_syn_ack_scan :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_tcp_syn_scan' )
						self._update_main_console( count=App.get_running_app()._console_count ,
												   moniker='tcp console #' )
						func()
					elif func == self.on_tcp_syn_scan_ports :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_tcp_syn_scan_ports' )
						self._update_main_console( count=App.get_running_app()._console_count ,
												   moniker='tcp console scan #' )
						func()
					elif func == self.on_nmap_fingerprint :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_nmap_fingerprint' )
						self._update_main_console( count=App.get_running_app()._console_count ,
												   moniker='nmap fingerprint console #' )
						func()




				@mainthread
				def _update_main_console( self ,
										  count ,
										  threaded = False ,
										  func = None ,
										  moniker = None ) :
					"""

					:return:
					"""



					self.ids.cci_action_prev.title = 'king console(' + str( count ) + ')'

					carousel = self.ids.maelstrom_carousel_id
					layout = GridLayout( cols = 1 ,
										 padding = [0 , 5 , 0 ,5]
										  )
					App.get_running_app()._console_count += 1
					layout.add_widget( Label( text = moniker  + str( App.get_running_app()._console_count ),
											color = [ 1, 0 , 0 , 1] ,
											font_size = 16 ,
											id = 'content' ,
											size_hint_y = 0.1 ) )
					# console text
					scrolly = Builder.load_string( self._retr_resource( 'text_scroller' ) )
					tx = scrolly.children[0]
					self._console_text = tx
					tx.text = 'standby...working...'
					#scrollbox
					layout.add_widget( scrolly )
					#footer
					layout.add_widget( Label( text = strftime("%Y-%m-%d %H:%M:%S", gmtime()) ,
											font_size = 16  ,
											size_hint_y = 0.2 ,
											color = [ 1, 0 , 0 , 1] ) )


					carousel.add_widget( layout )
					carousel.index = len( carousel.slides ) - 1
					self.canvas.ask_update()

					if threaded :
						func()



				@mainthread
				def _update_console_content( self , content , container ) :
					"""

					:param console slide:

					:return:
					"""

					container.text += content + '\n'
					self.canvas.ask_update()
					
					

				def _on_full_screen( self ) :
					"""

					:return:
					"""

					if not App.get_running_app()._full_screen :
						pass



				# icmp handlers
				def on_ping_ip_input( self  , in_ip = None ) :
					"""
					input ping variable
					:return:
					"""

					out = str()
					b_ret = True
					App.get_running_app()._thrd.rlk.acquire()
					App.get_running_app()._logger.info( self.__class__.__name__ + '...on_ping_ip_input'  )
					App.get_running_app()._thrd.rlk.release()

					ip = str()
					if in_ip is None :
						ip = self.ids.ip_input.text
					else :
						ip = in_ip

					try :

						cmd = ["su" ,
							   "-c" ,
							   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
							   "./king_console/kc_ping.pyo" ,
							   "-s" ,
							   ip
							  ]

						try :
							out = proc.check_output( cmd  )
							App.get_running_app()._logger.info( out )
						except proc.CalledProcessError as e :
							b_ret = False
					except Exception as e :
						b_ret = False
						App.get_running_app()._logger.error( e.message )


					thr = App.get_running_app()._thrd.thrds['icmp ping console #'  + str( App.get_running_app()._console_count )]
					if thr :
						if thr['stop_alert'].isSet() :
							return

					boiler = 'maelstrom[icmp]->ping: ' + \
							  ' ' + self.ids.ip_input.text
					boiler += '\n'
					boiler += out
					App.get_running_app()._logger.info( self.__class__.__name__ + '...boiler='  + boiler)

					pos = boiler.find( '#[QPython]' )
					if pos :
						boiler = boiler[:pos]

					if in_ip is None :
						self._console_text.text = boiler

					return boiler



				def on_ping_ip_subnet( self  ) :
					"""
					input ping variable
					:return:
					"""

					# sentinel function so we don't have to use  lock object
					# started at at end of ui update
					threading.Thread( target = self._ping_ip_subnet ).start()



				def on_arp_ip_input( self  ) :
					"""
					input arp variable
					:return:
					"""

					# sentinel function so we don't have to use  lock object
					# started at at end of ui update
					threading.Thread( target = self._on_arp_ip_input() ).start()



				def on_arp_ip_scan( self  ) :
					"""
					input arp variable
					:return:
					"""

					# sentinel function so we don't have to use  lock object
					# started at at end of ui update
					threading.Thread( target = self._on_arp_ip_scan( range=True ) ).start()



				def on_tcp_syn_ack_scan( self ) :
					"""


					:return:
					"""

					# sentinel function so we don't have to use  lock object
					# started at at end of ui update
					threading.Thread( target = self._on_tcp_syn_ack_scan() ).start()



				def on_tcp_syn_scan_ports( self , in_ip = None , range = False ) :
					"""

					:param in_ip:
					:param range:
					:return:
					"""

					# sentinel function so we don't have to use  lock object
					# started at at end of ui update
					threading.Thread( target = self._on_tcp_syn_scan_ports() ).start()



				def on_nmap_fingerprint( self ) :
					"""

					:return:
					"""

					# sentinel function so we don't have to use  lock object
					# started at at end of ui update
					threading.Thread( target = self._on_nmap_fingerprint() ).start()





				def _ping_ip_subnet( self ) :
					"""

					:return:
					"""

					App.get_running_app()._thrd.rlk.acquire()
					App.get_running_app()._logger.info( self.__class__.__name__ + '...on_ping_ip_subnet'  )
					App.get_running_app()._thrd.rlk.release()


					ip = self.ids.ip_subnet_input.text
					prefix = kc_ping.chomp( source_str = ip , delimiter = '.' , keep_trailing_delim = True )

					slide = self.ids.maelstrom_carousel_id.current_slide
					#text box
					container = slide.children[1].children[0]
					container.text = 'working...\n'
					# for each address in subnet
					for addr in range( 0 , 254 ):
						thr = App.get_running_app()._thrd.thrds['icmp ping console #'  + str( App.get_running_app()._console_count )]
						if thr :
							if thr['stop_alert'].isSet() :
								break
						try :

							reply = self.on_ping_ip_input( in_ip=prefix + str( addr ) )
							pos = reply.find( '<reply>' )
							rejoinder = str()
							if pos == -1 :
								rejoinder = 'failed'
							else :
								rejoinder = 'succeeded'

							# have to update main thread by proxy - opengl
							self._update_console_content( prefix + str( addr ) + '... ' + rejoinder , container )
							#container.text += reply + '\n'

							sleep( 0.25 )


						except Exception as err :
							print err
				
				
				
				# arp handlers
				def _on_arp_ip_input( self  , range = False ) :
						"""
						:param in_ip : input arp variable
						:return:
						"""

						out = str()
						App.get_running_app()._thrd.rlk.acquire()
						App.get_running_app()._logger.info( self.__class__.__name__ + '...on_arp_ip_input'  )
						App.get_running_app()._thrd.rlk.release()

						ip = str()
						sw = str()
						if range is False :
							ip = self.ids.ip_arp_input.text
							sw = '-s'
						else :
							ip = self.ids.arp_subnet_input.text
							sw = '-n'

						try :

							cmd = ["su" ,
								   "-c" ,
								   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
								   "./king_console/kc_arp.pyo" ,
								   sw ,
								   ip
								  ]

							try :
								out = proc.check_output( cmd  )
								App.get_running_app()._logger.info( out )
							except proc.CalledProcessError as e :
								b_ret = False
						except Exception as e :
							b_ret = False
							App.get_running_app()._logger.error( e.message )

						thr = App.get_running_app()._thrd.thrds['arp console #'  + str( App.get_running_app()._console_count )]
						if thr :
							if thr['stop_alert'].isSet() :
								return

						boiler = 'maelstrom[arp]->scan1: ' + \
								  ' ' + ip
						boiler += '\n'
						boiler += out
						App.get_running_app()._logger.info( self.__class__.__name__ + '...boiler='  + boiler)

						pos = boiler.find( '#[QPython]' )
						if pos :
							boiler = boiler[:pos]

						self._console_text.text = boiler



				def _on_arp_ip_scan( self  , in_ip = None , range = False ) :
						"""
						:param in_ip : input arp variable
						:return:
						"""
						self._on_arp_ip_input( range=range )



				# tcp handlers
				def _on_tcp_syn_ack_scan( self ) :
						"""
						:param in_ip :
						:param range :
						:return
						"""
						ip = str()
						port = 80
						ip , port = self.ids.ip_input_syn_ack.text.split( ':' )



						out = str()
						App.get_running_app()._thrd.rlk.acquire()
						App.get_running_app()._logger.info( self.__class__.__name__ + '...on_tcp_syn_ack_scan'  )
						App.get_running_app()._thrd.rlk.release()

						try :

							cmd = ["su" ,
								   "-c" ,
								   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
								   "./king_console/kc_tcp.pyo" ,
								   '-s' ,
								   ip ,
								   '-p' ,
								   port
								  ]

							try :
								out = proc.check_output( cmd  )
								App.get_running_app()._logger.info( out )
							except proc.CalledProcessError as e :
								b_ret = False
						except Exception as e :
							b_ret = False
							App.get_running_app()._logger.error( e.message )

						thr = App.get_running_app()._thrd.thrds['tcp console #'  + str( App.get_running_app()._console_count )]
						if thr :
							if thr['stop_alert'].isSet() :
								return

						boiler = 'maelstrom[tcp]->scan1: ' + \
								  ' ' + ip
						boiler += '\n'
						boiler += out
						App.get_running_app()._logger.info( self.__class__.__name__ + '...boiler='  + boiler)

						pos = boiler.find( '#[QPython]' )
						if pos :
							boiler = boiler[:pos]

						self._console_text.text = boiler




				def _on_tcp_syn_scan_ports( self ) :
						"""
						:param in_ip :
						:param range :
						:return
						"""
						ip = self.ids.ip_input_syn_ack_port.text
						ports = self.ids.ip_input_syn_ack_scan.text

						out = str()
						boiler = str()
						App.get_running_app()._thrd.rlk.acquire()
						App.get_running_app()._logger.info( self.__class__.__name__ + '...on_tcp_syn_scan_ports'  )
						App.get_running_app()._thrd.rlk.release()

						try :

							cmd = ["su" ,
								   "-c" ,
								   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
								   "./king_console/kc_tcp.pyo" ,
								   '-s' ,
								   ip ,
								   '-r' ,
								   ports
								  ]

							try :
								out = proc.check_output( cmd  )
								App.get_running_app()._logger.info( out )
							except proc.CalledProcessError as e :
								b_ret = False
						except Exception as e :
							b_ret = False
							App.get_running_app()._logger.error( e.message )

						t = App.get_running_app()._thrd.thrds
						thr = App.get_running_app()._thrd.thrds['tcp console scan #'  + str( App.get_running_app()._console_count )]
						if thr :
							if thr['stop_alert'].isSet() :
								return

						boiler = 'maelstrom[tcp]->scan_ports1: '
						boiler += ip
						boiler += '\n'
						boiler += out
						App.get_running_app()._logger.info( self.__class__.__name__ + '...boiler='  + boiler)

						pos = boiler.find( '#[QPython]' )
						if pos :
							boiler = boiler[:pos]

						self._console_text.text = boiler




				def _on_nmap_fingerprint( self )  :
						"""

						:return
						"""

						ip = self.ids.ip_input_nmap_finger
						out = str()
						boiler = str()
						App.get_running_app()._thrd.rlk.acquire()
						App.get_running_app()._logger.info( self.__class__.__name__ + '...on_nmap_fingerprint'  )
						App.get_running_app()._thrd.rlk.release()

						try :
							out = kc_nmap.quick_fingerprint( ip )
						except Exception as e :
							b_ret = False
							App.get_running_app()._logger.error( e.message )


						thr = App.get_running_app()._thrd.thrds['nmap fingerprint console #'  + str( App.get_running_app()._console_count )]
						if thr :
							if thr['stop_alert'].isSet() :
								return

						boiler = 'maelstrom[tcp]->nmap_quick_fingerprint1: '
						boiler += ip
						boiler += '\n'
						boiler += out

						self._console_text.text = boiler




# -------------------------------------------------------------------------------------------------
class NetworkScreen( Screen ) :
		"""


		"""
		pass


# -------------------------------------------------------------------------------------------------
class TcpScreen( Screen ) :
		"""


		"""
		pass


# -------------------------------------------------------------------------------------------------
class FullScreen( Screen ) :
		"""

		"""
		_visible = ObjectProperty()

# -------------------------------------------------------------------------------------------------
class ViewManagerScreen( Screen ) :
		"""


		"""


		def __init__( self ) :
			"""

			ctor
			"""

			super( ViewManagerScreen , self ).__init__()



# -------------------------------------------------------------------------------------------------
class ScreenManagement( ScreenManager ) :
		"""


		"""

		transition = SlideTransition()

