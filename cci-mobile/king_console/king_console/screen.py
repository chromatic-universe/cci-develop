# screen.py     william k. johnson 2016
import threading
from kivy.app import App
from kivy.clock import Clock , mainthread
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label
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

from time import gmtime, strftime , sleep
import subprocess as proc
import ping

# ---------------------------------------------------------------------------------------------
def ping_subnet( destination = None ) :
			"""
			ping subnet
			:param  destination , parses local subnet from addr:
			:return ping reply obj list:
			"""

			prefix = chomp( source_str = destination , delimiter = '.' , keep_trailing_delim = True )
			replies = list()

			'''
			for each address in subnet
			'''
			for addr in range( 0 , 254 ):
				try :
					#put request on wire
					print prefix + str( addr )
					reply = ping_atom( prefix + str( addr ) )
					if reply is not None :
						replies.append( reply )
						print reply.display()
				except Exception as err :
					print err

			return replies


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
				parent,add_widget( layout )




# -------------------------------------------------------------------------------------------------
class TreeManagerLabel( TreeViewLabel ) :
	"""

	"""
	font_size = 18



# -------------------------------------------------------------------------------------------------
# screens
class CciScreen( Screen ) :
				"""

				"""

				stop = threading.Event()

				accordion_id = ObjectProperty()
				_console_text = ObjectProperty()
				_console_count = 1
				lock = threading.Lock()

				@staticmethod
				def _retr_resource( resource_id ) :
					"""

					:param resource_id:
					:return ui resource:
					"""

					return resources.const_resource_ids[resource_id]


				def _on_ping_start( self ) :
					"""

					:return:
					"""
					threading.Thread( target = self.ping_thread_exec ,kwargs=dict(func=self.on_ping_ip_input)).start()


				def _on_ping_subnet_start( self ) :
					"""

					:return:
					"""
					threading.Thread( target = self.ping_thread_exec ,kwargs=dict(func=self.on_ping_ip_subnet)).start()


				@mainthread
				def move_to_accordion_item( self , acc , tag = None ) :
					"""
					workaround for android nesting bug
					:param acc:
					:return:
					"""

					for child in acc.children :
						if child.title == 'king console' :
							child.collapse = False
							child.canvas.ask_update()

					self.ids.ping_btn.text = "execute"


				def ping_thread_exec( self , func = None ) :
					"""

					:return:
					"""


					if func == self.on_ping_ip_input :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_ping' )
						self._update_main_console( App.get_running_app()._console_count )
						func()
					elif func == self.on_ping_ip_subnet :
						# update main thread from decorator
						self.move_to_accordion_item( self.ids.cci_accordion ,
																 'ids_ping_subnet' )
						self._update_main_console( App.get_running_app()._console_count )
						func()



				@mainthread
				def _update_main_console( self , count ) :
					"""

					:return:
					"""

					self.ids.cci_action_prev.title = 'king console(' + str( count ) + ')'

					carousel = self.ids.maelstrom_carousel_id
					layout = GridLayout( cols = 1 ,
										 padding = [0 , 5 , 0 ,5]
										  )
					App.get_running_app()._console_count += 1
					layout.add_widget( Label( text = 'icmp ping console #'  + str( App.get_running_app()._console_count ),
											color = [ 1, 0 , 0 , 1] ,
											font_size = 16 ,
											id = 'content' ,
											size_hint_y = 0.1 ) )

					scrolly = Builder.load_string( self._retr_resource( 'text_scroller' ) )
					tx = scrolly.children[0]
					self._console_text = tx
					tx.text = 'standby,,,,working...'
					layout.add_widget( scrolly )

					layout.add_widget( Label( text = strftime("%Y-%m-%d %H:%M:%S", gmtime()) ,
											font_size = 16  ,
											size_hint_y = 0.2 ,
											color = [ 1, 0 , 0 , 1] ) )

					self.lock.acquire()
					try :
						carousel.add_widget( layout )
						carousel.index = len( carousel.slides ) - 1
					finally :
						self.lock.release()


				@mainthread
				def _update_console_content( self , idx , content ) :
					"""

					:param console slide:

					:return:
					"""

					idx.children[0].children[0].text = content
					self.canvas.ask_update()

					print content



				def _on_full_screen( self ) :
					"""

					:return:
					"""

					if not App.get_running_app()._full_screen :
						pass


				# icmp handlers
				def on_ping_ip_input( self  ) :
					"""
					input ping variable
					:return:
					"""

					out = str()
					b_ret = True
					App.get_running_app()._logger.info( self.__class__.__name__ + '...on_ping_ip_input'  )


					ip = self.ids.ip_input.text
					try :

						cmd = ["su" ,
							   "-c" ,
							   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
							   "./king_console/ping.pyo" ,
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


					boiler = 'maelstrom[icmp]->ping: ' + \
							  ' ' + self.ids.ip_input.text
					boiler += '\n'
					boiler += out
					App.get_running_app()._logger.info( self.__class__.__name__ + '...boiler='  + boiler)

					pos = boiler.find( '#[QPython]' )
					if pos :
						boiler = boiler[:pos]

					self._console_text.text = boiler



				def on_ping_ip_subnet( self  ) :
					"""
					input ping variable
					:return:
					"""

					out = str()
					b_ret = True
					App.get_running_app()._logger.info( self.__class__.__name__ + '...on_ping_ip_subnet'  )


					ip = self.ids.ip_subnet_input.text
					prefix = ping.chomp( source_str = ip , delimiter = '.' , keep_trailing_delim = True )

					self.lock.acquire()
					try :
						idx = self.ids.maelstrom_carousel_id.current_slide
					finally :
						self.lock.release()

					# for each address in subnet
					for addr in range( 0 , 254 ):
						try :
							self._update_console_content( idx , prefix + str( addr ) )
							sleep( 3 )
							"""
							reply = ping_atom( prefix + str( addr ) )
							if reply is not None :
								replies.append( reply )
								print reply.display()
							"""
						except Exception as err :
							print err






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

