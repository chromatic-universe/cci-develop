# kivy
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
from kivy.uix.popup import Popup
from kivy.uix.treeview import TreeView , TreeViewLabel , TreeViewNode
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.config import ConfigParser
from kivy.uix.progressbar import ProgressBar
from kivy.uix.dropdown import DropDown
from kivy.clock import Clock , mainthread
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.properties import StringProperty, ObjectProperty
from kivy.uix.settings import SettingsWithSidebar , SettingsWithSpinner
from kivy.config import Config
from kivy.loader import Loader
from kivy.utils import get_color_from_hex


Window.softinput_mode = 'pan'

# python standard
import os
import copy
import logging
import importlib
from time import gmtime, strftime , sleep
import subprocess as proc
import threading
import requests

try:  # python 2
    from urllib import urlencode
except ImportError:  # python 3
    from urllib.parse import urlencode

try:  # python 2
    from urllib2 import urlopen
except ImportError:  # python 3
    from urllib.request import urlopen


from bimini import resource_factory \
	                     as resources , \
						 screen


kivy.require( '1.9.1' )

# ------------------------------------------------------------------------------------------------
class ConsoleAccordion( Accordion ) :

		btn_text = StringProperty('')
		_orientation = StringProperty('vertical')
		_inner_orientation = StringProperty( 'horizontal' )
		orientation_handler = ObjectProperty(None)

		stop = threading.Event()

		def __init__( self, *args, **kwargs):
			super( ConsoleAccordion , self ).__init__( *args, **kwargs)

			# get the original orientation
			self._orientation = 'horizontal' if Window.width > Window.height else 'vertical'
			# inform user
			self.btn_text = self._orientation
			self.orientation = self._orientation
			self._inner_orientation =  'vertical' if self.orientation == 'horizontal' else 'horizontal'


		def check_orientation( self , width , height ) :
			"""

			:param width:
			:param height:
			:return:
			"""

			orientation = 'vertical' if height > width else 'horizontal'
			if orientation != self._orientation:
				self._orientation = orientation
				self.orientation_cb(orientation)



		def orientation_cb( self , orientation ) :
			"""

			:param orientation:
			:return:
			"""
			self.btn_text = orientation
			self.orientation = 'horizontal' if Window.width > Window.height else 'vertical'
			self._inner_orientation =  'vertical' if self._orientation == 'horizontal' else 'horizontal'




# ------------------------------------------------------------------------------------------------
class biminiApp( App ) :
				"""
				urnack
				"""


				def __init__( self ) :
					"""

					:return:
					"""

					super( biminiApp , self ).__init__()

					# logger
					self._logger = logging.getLogger( "cci-bimini-client" )
					self._logger.setLevel( logging.DEBUG )
					fh = logging.FileHandler(  'cci-bimini.log' + '-debug.log', mode = 'a' )
					fh.setLevel( logging.DEBUG )
					formatter = logging.Formatter( resources.log_format )
					fh.setFormatter( formatter )
					self._logger.addHandler( fh )
					self._logger.info( self.__class__.__name__ + '...'  )

					try :

						from kivy.support import install_twisted_reactor
						install_twisted_reactor()
						from twisted.internet import reactor, protocol

						self._logger.info( '...twisted..ok' )
					except Exception as e :
						self._logger.error( e.message )

					self.settings_cls = SettingsWithSpinner
					Window.on_rotate = self._on_rotate


				def on_connect( self ) :
					"""

					:return:
					"""

					try :
						self._logger.info( ',,,on_connect...'  )
						self.url = ('http://%s:7080/desktop.jpeg' %
									self.root.ids.server.text )
						self.send_url = ('http://%s:7080/click?' %
										 self.root.ids.server.text)


						self.reload_desktop()
					except IOError as e :
						self._logger.error( e.message )
					except Exception as e :
						self._logger.error( e.message )



				def reload_desktop( self , *args ) :
					"""

					:param args:
					:return:
					"""

					try :
						desktop = Loader.image( self.url , nocache=True )
						desktop.bind( on_load=self.desktop_loaded )

					except IOError as e :
						self._logger.error( e.message )



				def desktop_loaded( self , desktop ) :
					"""

					:param desktop:
					:return:
					"""

					try :
						if desktop.image.texture:
							self.root.ids.desktop.texture = \
								desktop.image.texture
						del desktop

						Clock.schedule_once(self.reload_desktop, 1)

						if self.root.current == 'login':
							self.root.current = 'desktop'
							self.move_to_accordion_item( self.root.ids.cci_bimini_accordion ,
														 'remote console' )
					except IOError as e :
						self._logger.error( e.message )


				def send_click( self , event ):

					try :

						params = {'x': int(event.x),
								  'y': int(self.root.ids.desktop.size[1] -
										   event.y)}
						self._logger.info( '...event x: %d , event y: %d ....' % ( event.x , event.y ) )
						self._logger.info( self.send_url + urlencode( params ) )
						urlopen( self.send_url + urlencode( params ) )


					except Exception as e :
						self._logger.error( e.message )


				def on_pause(self):
					# save data
					return True


				def on_resume(self):
					# something
					pass


				def _on_rotate( self , rotation ) :
					"""

					:param rotation:
					:return:
					"""

					pass


				def move_to_accordion_item( self , acc , tag = None ) :
					"""
					workaround for android nesting bug
					:param acc:
					:return:
					"""

					for child in acc.children :
						if child.title == tag :
							child.collapse = False
							child.canvas.ask_update()



# --------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':

				Config.set( 'graphics', 'width', '960' )
				Config.set( 'graphics', 'height', '540' )
				Config.set( 'input', 'mouse', 'mouse,disable_multitouch' )

				from kivy.core.window import Window  # load after Config.set
				#Window.clearcolor = get_color_from_hex('#95a5a6')

				biminiApp().run()
