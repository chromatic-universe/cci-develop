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
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.config import ConfigParser
from kivy.uix.progressbar import ProgressBar
from kivy.clock import Clock
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.uix.settings import SettingsWithSidebar , SettingsWithSpinner
from kivy.uix.screenmanager import ScreenManager, \
	                               Screen ,\
	                               RiseInTransition ,\
								   SwapTransition , \
								   FallOutTransition , \
								   SlideTransition
Window.softinput_mode = 'pan'

# python standard
import logging
import importlib
from time import gmtime, strftime , sleep

import subprocess as proc

#cci
from cci_maelstrom import *

kivy.require( '1.9.1' )

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'
bx="""
ScrollView:
    id: scrlv
    TextInput:
        text: 'foo'
        size_hint: 1, None
        cursor_blink: True
		background_color: [0,0,0,0]
		foreground_color: [1,1,1,1]
		multiline: True
		font_size: 16
		readonly: True
        height: max( (len(self._lines)+1) * self.line_height, scrlv.height)
"""

class CciScreen( Screen ):
    pass


class NetworkScreen( Screen ):
    pass

class TcpScreen( Screen ):
    pass



class ScreenManagement( ScreenManager ) :
	transition = SlideTransition()


class dynamic_import :
		"""
		dynamic import
		"""

		def __init__( self , module_name , class_name ) :
			"""
			constructor
			:param module_name:
			:param class_name:
			:return:
			"""

			module = __import__( module_name )
			_class = getattr(module, class_name)
			self._instance = _class()

		@property
		def cls_instance( self ) :
			return self._instance
		@cls_instance.setter
		def cls_instance( self , cls ) :
			self._instance = cls



class maelstromApp( App ) :
		"""
		maelstrom
		"""


		def __init__( self ) :
			"""

			:return:
			"""

			super( maelstromApp , self ).__init__()

			self.settings_cls =  SettingsWithSpinner

			# logger
			self._logger = logging.getLogger( "cci_maelstrom" )
			self._logger.setLevel( logging.DEBUG )
			fh = logging.FileHandler(  'cci_maelstrom.log' + '-debug.log', mode = 'a' )
			fh.setLevel( logging.DEBUG )
			formatter = logging.Formatter( log_format )
			fh.setFormatter( formatter )
			self._logger.addHandler( fh )
			self._logger.info( self.__class__.__name__ + '...'  )
			self._ret_text = str()

			self._console_count = 1


		# settings
		def build_settings( self , settings ) :
			"""

			:param settings:
			:return:
			"""
			with open( "settings.json", "r" ) as settings_json :
				settings.add_json_panel( 'cci-maelstrom contexts',
										 self.config ,
										 data=settings_json.read() )
			with open( "settings_env.json", "r" ) as settings_json :
				settings.add_json_panel( 'cci-maelstrom environment',
										 self.config ,
										 data=settings_json.read() )
			with open( "settings_stream.json", "r" ) as settings_json :
				settings.add_json_panel( 'cci-maelstrom stream data',
										 self.config ,
										 data=settings_json.read() )
			self.use_kivy_settings = False

		def build_config( self , config ) :
			"""

			:param config:
			:return:
			"""
			config.setdefaults( 'physical', {
											'packet_timeout': 3 ,
											'show_stream': 1 ,
											} )
			config.setdefaults( 'network-icmp', {
											'packet_timeout': 1 ,
											'show_stream': 1 ,
											'default_address' : 'www.chromaticuniverse.xyz'
											} )

		def on_config_change(self, config, section, key, value):
			"""

			:param config:
			:param section:
			:param key:
			:param value:
			:return:
			"""
			self._logger.info("main.py: app.on_config_change: {0}, {1}, {2}, {3}".format(
				config, section, key, value))

			"""
			if section == "section1":
				if key == "key1":
					self.root.ids.label. = value
				elif key == 'font_size':
					self.root.ids.label.font_size = float(value)
				elif key == 'default_user':
					self.root.ids.label.default_user = value
			"""

		# android mishegas
		def on_pause(self):
			# save data
			self._logger.info( self.__class__.__name__ + '...'  + 'on_pause' )

			return True

		def on_resume( self ):
			# something
			self._logger.info( self.__class__.__name__ + '...'  + 'on_resume' )

			pass

		# icmp handlers
		def on_ping_ip_input( self ) :
			"""
			input ping variable
			:return:
			"""

			out = str()
			b_ret = True

			self._move_to_accordion_item( self.root.current_screen.ids.cci_accordion ,
										  self.root.current_screen.ids.ip_input )
			try :

				cmd = ["su" ,
					   "-c" ,
					   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
					   "/system/bin/ping.py"]
				try :
					out = proc.check_output( cmd  )
					self._logger.info( out )
				except proc.CalledProcessError as e :
					b_ret = False
			except Exception as e :
				self._logger.error( e )

			carousel = self.root.current_screen.ids.maelstrom_carousel_id
			if b_ret :
				res = 'ping succeeded....'
			else :
				res = 'ping failed......'
			boiler = 'maelstrom[icmp]->ping: ' + \
					  res + \
					  ' ' + self.root.current_screen.ids.ip_input.text
			boiler += '\n'
			boiler += out
			pos = boiler.find( '#[QPython]' )
			if pos :
				boiler = boiler[:pos]


			layout = GridLayout( cols = 1 ,
								 padding = [0 , 5 , 0 ,5]
								  )
			layout.add_widget( Label( text = 'icmp ping console #'+ str( self._console_count ),
									color = [ 1, 0 , 0 , 1] ,
									font_size = 16 ,
									size_hint_y = 0.1 ) )

			scrolly = Builder.load_string( bx )
			tx = scrolly.children[0]
			tx.text = boiler
			layout.add_widget( scrolly )
			layout.add_widget( Label( text = strftime("%Y-%m-%d %H:%M:%S", gmtime()) ,
									font_size = 16  ,
									size_hint_y = 0.2 ,
									color = [ 1, 0 , 0 , 1] ) )
			carousel.add_widget( layout )

			carousel.index = len( carousel.slides ) - 1
			self._console_count += 1


		def _selected_accordion_item( self ) :
			"""

			:return accordion item selected:
			"""
			for item in self.root.current_screen.ids.cci_accordion.children :
				try:
					if not item.collapse :
						return item
				except :
					pass


		def accordion_touch_up( self ) :
			"""
			:return:
			"""
			for item in self.root.current_screen.children :
				try:
					if not item.collapse :
						self._logger.info( self.__class__.__name__ + '...' +
										   item.title + '...accordion_item_touch_down' )
				except :
					pass


		def _move_to_accordion_item( self , acc , tag = None ) :
			"""
			workaround for android nesting bug
			:param acc:
			:return:
			"""

			for child in acc.children :
				if child.title == 'cci-maelstrom' :
					child.collapse = False
					child.canvas.ask_update()

			self.root.current_screen.ids.ping_btn.text = "execute"


		def _open_extended_window( self ) :
			"""

			:return:
			"""

			item = self._selected_accordion_item()
			self.root.current = 'screen_' + item.title


		def _manip_extended_window( self ) :
			"""

			:return:
			"""

			self.root.current = 'screen_cci'



		# attributes
		@property
		def logger( self ) :
			return self._logger
		@logger.setter
		def logger( self , log ) :
			self._logger = log

        

      

if __name__ == '__main__':


        maelstrom = maelstromApp()
        maelstrom.run()
        maelstrom.logger.info( "main...app running....." )
            
