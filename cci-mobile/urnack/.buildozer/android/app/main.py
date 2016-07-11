

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
from kivy.clock import Clock , mainthread
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.properties import StringProperty, ObjectProperty
from kivy.uix.settings import SettingsWithSidebar , SettingsWithSpinner
from kivy.uix.screenmanager import ScreenManager, \
	                               Screen ,\
	                               RiseInTransition ,\
								   SwapTransition , \
								   FallOutTransition , \
								   SlideTransition
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
import sqlite3


#cci
import urnack.cci_mini_elastic as cci_elastic
import urnack.cci_mini_mongo as cci_mongo
from urnack import resource_factory \
	                     as resources , \
						 screen

import pika
from pika import BlockingConnection

#from scapy.all import *

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
class urnackApp( App ) :
				"""
				urnack
				"""


				def __init__( self ) :
					"""

					:return:
					"""

					super( urnackApp , self ).__init__()

					self.settings_cls = SettingsWithSpinner

					#view manager
					self._view_manager = None
					self._console_count = 1

					Window.on_rotate = self._on_rotate



				# helpers
				@staticmethod
				def _retr_resource( resource_id ) :
					"""

					:param resource_id:
					:return ui resource:
					"""

					return resources.const_resource_ids[resource_id]



				# settings
				def build_settings( self , settings ) :
					"""

					:param settings:
					:return:
					"""
					with open( "settings.json", "r" ) as settings_json :
						settings.add_json_panel( 'cci-urnack contexts',
												 self.config ,
												 data=settings_json.read() )
					with open( "settings_env.json", "r" ) as settings_json :
						settings.add_json_panel( 'cci-urnack environment',
												 self.config ,
												 data=settings_json.read() )
					with open( "settings_stream.json", "r" ) as settings_json :
						settings.add_json_panel( 'cci-urnack stream data',
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


				def on_start( self ) :
					"""

					:return:
					"""

					server_param =  [{ 'host' :'search-chromatic-search-p647s4rdqjcgub7tt7neealjn4.us-west-2.es.amazonaws.com' ,
										'port' : 80}]
					elastic_cci = cci_elastic.cci_mini_elastic( server_param , True )
					self.root.current_screen.ids.acc_item_elastic.text = elastic_cci.server_banner

					mongo_cci = cci_mongo.cci_mini_mongo( 'cci-aws-3' )
					self.root.current_screen.ids.acc_item_mongo.text = mongo_cci.device_info

					self.root.current_screen.ids.console_interfaces.text = 'blase'


					content = None
					with open( 'cci_mini_elastic.log-debug.log' ) as f :
						content = f.readlines()
					self.root.current_screen.ids.console_interfaces.text = '\n'.join( content )


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
						if child.title == 'king console' :
							child.collapse = False
							child.canvas.ask_update()

					self.root.current_screen.ids.ping_btn.text = "execute"



# --------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':

         urnackApp().run()
