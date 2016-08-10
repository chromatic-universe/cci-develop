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
from kivy.uix.bubble import Bubble
from kivy.config import ConfigParser
from kivy.uix.progressbar import ProgressBar
from kivy.clock import Clock , mainthread
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.properties import StringProperty, ObjectProperty

import os
import copy
import logging
import importlib
from time import gmtime, strftime , sleep
import subprocess as proc
import threading
import requests
from functools import partial

import sqlite3
import Queue
import uuid


from king_console.screen import ConsolePopup
from king_console import resource_factory \
	                     as resources
from king_console import cci_mini_mongo as mongo_client

# -----------------------------------------------------------------------------------
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return proc.check_output( ['cat' , '/sys/class/net/wlan0/address'] ).strip().lower()
		except :
			pass



class kc_config( object ) :
				"""
				config
				"""


				def __init__( self  ,   log = None ) :

					"""
					:param log
					:return:
					"""

					if log is None :
						raise Exception( 'no logger provided' )




				@classmethod
				def _retr_resource( cls , resource_id ) :
					"""

					:param resource_id:
					:return ui resource:
					"""

					return resources.const_resource_ids[resource_id]



				@classmethod
				def _post_function_call( cls , func , params ) :
					"""

					:param func:
					:param params:
					:return:
					"""

					package = ( func , params )
					App.get_running_app().dbq.put( package )



				def _show_info( self, container ) :
					"""
					:param text container
					:return
					"""

					pass


				def _on_test_connect( self ) :
					"""
					:return
					"""

					pass


				def show_config( self ) :
					"""

					:param bootstrap:
					:return:
					"""

					pass











# ------------------------------------------------------------------------------------------
class kc_mongo_config( kc_config ) :
				"""

				"""

				def __init__( self  , bootstrap = None ,
							          log = None ,
									  device_id = None ,
									  last_ip = None ,
									  last_real_ip = None ) :
							"""

							:param bootstrap:
							:return:
							"""



							if log is None :
								raise Exception( 'no logger provided' )

							super( kc_mongo_config , self ).__init__( log )

							self._bootstrap = bootstrap
							self._logger = log
							self._id = device_id
							self._last_ip = last_ip
							self._last_real_ip = last_real_ip




				def _show_info( self, container ) :
							"""

							:param container:
							:return:
							"""

							mongo = mongo_client.cci_mini_mongo( bootstrap = self._bootstrap ,
																 device_id = self._id )
							s = str()
							if mongo.connected :
								for key , value in mongo.device_info.iteritems() :
									s += str( key ) + ':   '  + str( value ) + '\n'
							else :
								s = 'mongo disconnected....no route to host...' ,
								s += 'could not connect to mongo host...'

							container.text = s





				def _on_test_connect( self ) :
							"""

							:return:
							"""


							layout = GridLayout( orientation = 'horizontal' ,
											  cols = 1 ,
											  background_color = [0,0,0,0])
							grid = GridLayout( cols=1 , orientation = 'horizontal', size_hint_y = None , size=(400 , 500  ) )

							action_bar = Builder.load_string( self._retr_resource( 'dlg_action_bar_2' ) )
							layout.add_widget( action_bar )
							grid.add_widget( Image( source = './image/mongodb-log.png'  , size_hint_y = .25 ) )
							view = Builder.load_string( self._retr_resource( 'text_scroller') )
							view.children[0].text = ''
							vx = view.children[0]
							grid.add_widget( view )
							btn = Button(    text = 'test'  ,
											 valign = 'middle',
											 id = 'test_btn' ,
											 background_color = [0,0,0,0] ,
											 color = [1,0,0,1]  ,
											 size_hint_y = .15 )
							btn.bind( on_press = lambda a:self._show_info( vx ) )
							grid.add_widget( btn )
							layout.add_widget( grid )

							popup = ConsolePopup( title='mongo connect' , content = layout )
							popup.open()



				def show_config( self ) :
							"""

							:param bootstrap:
							:return:
							"""


							layout = GridLayout( orientation = 'horizontal' ,
											  cols = 1 ,
											  background_color = [0,0,0,0])
							action_bar = Builder.load_string( self._retr_resource( 'dlg_action_bar_2' ) )
							layout.add_widget( action_bar )
							layout.add_widget( Image( source = './image/mongodb-log.png' , pos_hint_y = 0 ,
													  size_hint_y = .2 ) )
							scroll = ScrollView()
							grid = GridLayout( cols=1 , orientation = 'horizontal' , size_hint_y = None , size=(400 , 500 ) )
							grid.add_widget( Label(  text = 'active:' ) )
							grid.add_widget( Switch( active = True ) )
							grid.add_widget( Label(  text = 'bootstrap:' ) )
							grid.add_widget( TextInput(  text = self._bootstrap ,
														id = 'mongo_bootstrap' ,
														cursor_blink =  True ,
														readonly = False ,
														multiline =  True ,
														size_hint_y = .5 ) )
							grid.add_widget( Label(  text = 'booststrap port:' ) )
							grid.add_widget( TextInput(  text = '27017' ,
														id = 'mongo_bootstrap_port' ,
														cursor_blink =  True ,
														readonly = False ,
														multiline =  True ,
														size_hint_y = .5 ) )
							btn = Button(    text = 'manip'  ,
											 valign = 'middle',
											 id = 'test_btn' ,
											 background_color = [0,0,0,0] ,
											 color = [1,0,0,1] )

							grid.add_widget( btn )
							scroll.add_widget( grid )
							layout.add_widget( scroll )


							#event = threading.Event()

							try :

								popup = ConsolePopup( title='document context' , content=layout )
								b = popup.content.children[0].children[0].children[0]
								#btn = popup.content.children[1].children[0].children[0]
								b.bind( on_press = lambda a:self._on_test_connect() )
								popup.open()

							finally :
								#App.get_running_app().dbpq_lk.release()
								pass




				def _update_device_session( self ,
											open = True
											 ) :
							"""

							:return:
							"""

							s = str()
							if open :
								s = 'true'
							else :
								s = 'false'

							mongo = mongo_client.cci_mini_mongo( bootstrap = self._bootstrap ,
																 device_id = self._id )

							if mongo.connected :
								db = mongo.mongo['cci_maelstrom']
								result = db['auth_devices'].update_one (
									{"device_id": self._id } ,
										{
											"$set":
											{
												"active" : s ,
												"last_known_ip" : self._last_ip ,
												"last_known_remote_ip" : self._last_real_ip
											},
											"$currentDate": { "last_active" : True }

										}

								)

								if result.matched_count == 0 :
									self._logger.error( '..could not update mongo db device info...' )
								else :
									self._logger.info( '..updated mongo db device info...' )



