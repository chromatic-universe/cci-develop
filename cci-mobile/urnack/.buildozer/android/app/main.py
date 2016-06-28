import kivy
from kivy.uix.accordion import Accordion, AccordionItem
from kivy.uix.carousel import Carousel
from kivy.uix.label import Label
from kivy.app import App
from kivy.uix import image
from kivy.uix.settings import SettingsWithSidebar
from kivy.core.window import Window

import elasticsearch

#from scapy.all import *

kivy.require( '1.9.1' )

class urnackApp( App ) :
			"""
			urnack
			"""


			def __init__( self ) :
				"""

				:return:
				"""

				super( urnackApp , self ).__init__()

				self.settings_cls = SettingsWithSidebar

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



			def on_pause(self):
				# save data
				return True

			def on_resume(self):
				# something
				pass





if __name__ == '__main__':

         urnackApp().run()
