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


# ------------------------------------------------------------------------------------------
class kc_mongo_config( object ) :
				"""

				"""

				def __init__( self  , bootstrap = None , log = None ) :
							"""

							:param bootstrap:
							:return:
							"""

							if log is None :
								raise Exception( 'no logger provided' )

							self._booststrap = bootstrap



				@staticmethod
				def _retr_resource( resource_id ) :
					"""

					:param resource_id:
					:return ui resource:
					"""

					return resources.const_resource_ids[resource_id]



				@staticmethod
				def _post_function_call( func , params ) :
					"""

					:param func:
					:param params:
					:return:
					"""

					package = ( func , params )
					App.get_running_app().dbq.put( package )





				def _on_mongo_test_connect( self ) :
							"""

							:return:
							"""

							mongo = mongo_client.cci_mini_mongo( bootstrap = 'cci-aws-3' )
							layout = GridLayout( orientation = 'horizontal' ,
											  cols = 1 ,
											  background_color = [0,0,0,0])
							grid = GridLayout( cols=1 , orientation = 'horizontal', size_hint_y = None , size=(400 , 500  ) )
							if mongo.connected :
									action_bar = Builder.load_string( self._retr_resource( 'dlg_action_bar_2' ) )
									layout.add_widget( action_bar )
									for key , value in mongo.device_info.iteritems() :
										grid.add_widget( Label( text = str( key ) + ':  '  + str( value )  ,
										                        text_size = (400 , None ) ) )

									scroller = ScrollView( )
									scroller.add_widget( grid )
									layout.add_widget( scroller )
									popup = ConsolePopup( title='connected...auth_devices info...' ,
														  content = layout )
									popup.open()
							else :
								popup = ConsolePopup( title='mongo disconnected....no route to host...' ,
													  content = Label( text = 'could not connect to mongo host...' ) ,
													  size = ( 400 ,400 ) )
								popup.open()







				def show_mongo_config( self ) :
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
							grid.add_widget( TextInput(  text = 'cci-aws-3' ,
														id = 'mongo_bootstrap' ,
														cursor_blink =  True ,
														readonly = False ,
														multiline =  True ) )
							grid.add_widget( Label(  text = 'booststrap port:' ) )
							grid.add_widget( TextInput(  text = '27017' ,
														id = 'mongo_bootstrap_port' ,
														cursor_blink =  True ,
														readonly = False ,
														multiline =  True ) )
							btn = Button(    text = 'test connect'  ,
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
								b.bind( on_press = lambda a:self._on_mongo_test_connect() )

							finally :
								#App.get_running_app().dbpq_lk.release()
								pass

							popup.open()