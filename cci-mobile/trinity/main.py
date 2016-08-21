

import sys
import os
import copy
import logging
import importlib
from time import gmtime, strftime , sleep
import subprocess as proc
import threading
import socket
import datetime
from functools import partial

import kivy
from kivy.uix.accordion import Accordion, AccordionItem
from kivy.uix.carousel import Carousel
from kivy.uix.label import Label
from kivy.app import App
from kivy.uix import image
from kivy.core.window import Window
from kivy.uix.switch import Switch
from kivy.uix.slider import Slider
from kivy.uix.textinput import TextInput
from kivy.uix.scrollview import ScrollView
from kivy.uix.dropdown import DropDown
from kivy.uix.popup import Popup
from kivy.uix.treeview import TreeView , TreeViewLabel , TreeViewNode
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.image import Image
from kivy.config import ConfigParser
from kivy.uix.progressbar import ProgressBar
from kivy.clock import Clock , mainthread
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.properties import StringProperty, ObjectProperty
from kivy.uix.settings import SettingsWithSidebar , SettingsWithSpinner

# cci



kivy.require( '1.9.1' )

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'
timestamp = 'cci-trinity~ {:%Y-%m-%d %H:%M:%S}'.format(datetime.datetime.now())
t = 3

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





class ccitrinityApp( App ) :
			"""
			trinity
			"""


			def __init__( self ) :
				"""

				:return:
				"""

				super( ccitrinityApp , self ).__init__()

				# logger
				self._logger = logging.getLogger( "cci trinity" )
				self._logger.setLevel( logging.DEBUG )
				fh = logging.FileHandler(  'trinity' + '-debug.log', mode = 'a' )
				fh.setLevel( logging.DEBUG )
				formatter = logging.Formatter( log_format )
				fh.setFormatter( formatter )
				self._logger.addHandler( fh )
				self._logger.info( self.__class__.__name__ + '...'  )
				self._pid = None
				self._clock_event = None



			def on_start(self) :
						"""

						:return:
						"""


						self._update_status( self.root.ids.status_text , '...initializing...' )
						is_running = False
						try :
							 pid = None
							 try :
								 with open( 'pid' , 'r' ) as pidfile :
									pid = pidfile.read().strip()
							 except :
								 pass

							 # check if process is running
							 if pid :
								 try :
									# throws exception if process doesn't exist
									is_running = os.path.exists( '/proc/%s' % pid )
									self._pid = pid
								 except :
									# pid not running
									pass

							 if is_running is False :


								self.root.ids.bootstrap_btn.background_color = [0,1,0,1]
								self.root.ids.bootstrap_btn.text = 'start trinity'
								self._update_status( self.root.ids.status_text , ' ....trinity....' )

								"""
								 # wrqputite pid
								 with open( 'pid' , 'w' ) as pidfile :
									 pidfile.write( str( os.getpid() ) + '\n'  )
								 # start server
								 IOLoop.instance().start()
								"""

							 else :
								self._update_status( self.root.ids.status_text , ' ....trinity running....' )
								self.root.ids.bootstrap_btn.background_color = [1,0,0,1]
								self.root.ids.bootstrap_btn.text = 'stop trinity'
								self.root.ids.process_info.text = 'pid: %s  port 7080' % self._pid
								self._logger.info( '...server already running... pid %s....'  % self._pid )



						except Exception as e:
							_logger.error( '...error in  trinity server...' + e.message )
							sys.exit( 1 )




			# android mishegas
			def on_pause(self):
				# save data


				return True



			def on_resume( self ):
				# something


				pass



			def _debug_log_snippet( self ) :
				"""

				:return:
				"""

				try :

					cmd = [ 'tail' ,
							'-n' ,
							'10' ,
							'cci-trinity-server.log-debug.log'
						   ]
					return proc.check_output( cmd )
				except proc.CalledProcessError as e:
					self._logger.error( '..._debug_log_snippet...' + e.message )



			@staticmethod
			def _update_status( container , status ) :
				"""

				:param status:
				:return:
				"""
				container.text = container.text + timestamp + status + '\n'






			def _on_start_trinity( self ) :
				"""

				:return:
				"""

				pid = str()

				if self.root.ids.bootstrap_btn.text == 'start trinity' :
					try :
						self._update_status( self.root.ids.status_text , ' ....starting trinity....' )

						b_ret = self._bootstrap_trinity()

						if not b_ret :
							self._update_status( self.root.ids.status_text , ' ....trinity bootstrap failed....' )
							return
						else :
							self._update_status( self.root.ids.status_text , ' ....trinity bootstrapped..running....' )
							self.root.ids.bootstrap_btn.background_color = [1,0,0,1]
							self.root.ids.bootstrap_btn.text = 'stop trinity'
							self._update_status( self.root.ids.status_text , ' ...trinity started...' )
							self._clock_event = Clock.schedule_interval( self._pid_callback, 2 )
					except Exception as e :
						self._logger.error( '..._on_start_trinity...' + e.message )
						self._update_status( self.root.ids.status_text , e.message )
					"""
					try :
						self._update_status( self.root.ids.status_text , ' ....starting trinity async....' )

						b_ret = self._bootstrap_trinity_async()

						if not b_ret :
							self._update_status( self.root.ids.status_text , ' ....trinity async bootstrap failed....' )
						else :

							self._update_status( self.root.ids.status_text , ' ....trinity async bootstrapped..running....' )
							self.root.ids.bootstrap_btn.background_color = [1,0,0,1]
							self.root.ids.bootstrap_btn.text = 'stop trinity'
							self._update_status( self.root.ids.status_text , ' ...trinity async started...' )
							#self._clock_event = Clock.schedule_interval( self._pid_callback, 2 )
					except Exception as e :
						self._logger.error( '..._on_start_trinity...async' + e.message )
						self._update_status( self.root.ids.status_text , e.message )
					"""
				else :
					try :
						try :
							 with open( 'pid' , 'r' ) as pidfile :
								pid = pidfile.read().strip()
							 self._pid = pid
						except :
							 pass

						try :
							pos = sys.platform.find( 'linux4' )
							cmd = list()
							if pos == -1 :
								andr = False
							else :
								andr = True

							cmd = ['su' ,
								   '-c' ,
								   'kill' ,
								   '-9' ,
								   pid]


							proc.check_output( cmd )

							self._update_status( self.root.ids.status_text , ' ....trinity server stopped ....' )
							self.root.ids.bootstrap_btn.background_color = [0,1,0,1]
							self.root.ids.bootstrap_btn.text = 'start trinity'
							if self._clock_event :
								self._clock_event.cancel()
							self.root.ids.process_info.text = 'port: 7080'
						except proc.CalledProcessError as e:
							self._logger.error( 'kill server failed...' + e.message )
							self._update_status( self.root.ids.status_text , ' ...kill server failed...' + e.message )

					except Exception as e :
						self._logger.error( '..._on_stop_trinity...' + e.message )
						self._update_status( self.root.ids.status_text , e.message )





			def _pid_callback( self , dt ) :
					pid = str()


					with open( 'pid' , 'r' ) as pidfile :
						pid = pidfile.read().strip()
					self.root.ids.process_info.text = 'pid: %s   ~  port: 7080' % pid





			def _bootstrap_trinity( self ) :
						"""

						:return:
						"""

						# another process ont that port?
						#

						b_ret = False
						try:
							s = socket.socket()
							s.setsockopt( socket.SOL_SOCKET , socket.SO_REUSEADDR , 1 )
							s.bind( ( socket.gethostname()  , 7080 ) )
						except socket.error as e:
							self._logger.error(  '..bootstrap failed...errno:%d...%s' % ( e[0] , e[1] ) )
							return

						pid = str()
						try :

								self._logger.info( "...bootstrapping cci_trinity....." )
								pos = sys.platform.find( 'linux4' )
								if pos == -1 :
									andr = False
								else :
									andr = True
								cmd = list()


								cmd = [
								  "su" ,
								  "-c" ,
								  "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
								  "./cci_trinity.pyo" ,
								  "&"
								  ]


								proc.Popen( cmd )

								try:
									s = socket.socket()
									s.setsockopt( socket.SOL_SOCKET , socket.SO_REUSEADDR , 1 )
									s.bind( ( socket.gethostname()  , 7080 ) )
									b_ret = True
									self._logger.info( "bootstrapped cci_trinity....." )
								except socket.error as e:
									self._logger.info( "failed tp bootstrap cci_trinity....." )
									b_ret = False



						except proc.CalledProcessError as e:
							self._logger.error( 'bootstrap failed...' + e.message )
						except OSError as e :
							self._logger.error( 'file does not exist?...' + e.message )
							#sys.exit( 1 )
						except ValueError as e :
							self._logger.error( 'arguments foobar...' + e.message )
							#sys.exit( 1 )
						except Exception as e :
							self._logger.error(  e.message )
							#sys.exit( 1 )

						return b_ret




			def _bootstrap_trinity_async( self ) :
						"""

						:return:
						"""
						b_ret = False

						try :

								self._logger.info( "...bootstrapping cci_trinity_async....." )
								pos = sys.platform.find( 'linux4' )
								if pos == -1 :
									andr = False
								else :
									andr = True
								cmd = list()


								cmd = [
								  "su" ,
								  "-c" ,
								  "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
								  "./cci_trinity_async.pyo" ,
								  "&"
								  ]


								proc.Popen( cmd )

								try:
									s = socket.socket()
									s.setsockopt( socket.SOL_SOCKET , socket.SO_REUSEADDR , 1 )
									s.bind( ( socket.gethostname()  , 7081 ) )
									b_ret = True
									self._logger.info( "bootstrapped cci_trinity_async....." )
								except socket.error as e:
									self._logger.info( "failed tp bootstrap cci_trinity_async....." + e.message  )
									b_ret = False



						except proc.CalledProcessError as e:
							self._logger.error( 'bootstrap failed.async..' + e.message )
						except OSError as e :
							self._logger.error( 'async file does not exist?...' + e.message )
							#sys.exit( 1 )
						except ValueError as e :
							self._logger.error( 'arguments foobar in async ...' + e.message )
							#sys.exit( 1 )
						except Exception as e :
							self._logger.error(  e.message )
							#sys.exit( 1 )

						return b_ret




			# attributes
			@property
			def logger( self ) :
				return self._logger
			@logger.setter
			def logger( self , log ) :
				self._logger = log




if __name__ == '__main__':


			ct = ccitrinityApp()
			ct.run()




