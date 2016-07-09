import kivy
from kivy.uix.accordion import Accordion, AccordionItem
from kivy.uix.carousel import Carousel
from kivy.uix.label import Label
from kivy.app import App
from kivy.uix import image
from kivy.uix.settings import SettingsWithSidebar , SettingsWithSpinner
from kivy.core.window import Window

#cci
import urnack.cci_mini_elastic as cci_elastic
import urnack.cci_mini_mongo as cci_mongo

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

				self.settings_cls = SettingsWithSpinner



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
				self.root.ids.acc_item_elastic.text = elastic_cci.server_banner

				mongo_cci = cci_mongo.cci_mini_mongo( 'cci-aws-3' )
				self.root.ids.acc_item_mongo.text = mongo_cci.device_info

			def on_pause(self):
				# save data
				return True



			def on_resume(self):
				# something
				pass





if __name__ == '__main__':

         urnackApp().run()
