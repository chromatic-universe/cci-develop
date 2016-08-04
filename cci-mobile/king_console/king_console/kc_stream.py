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

import cci_mini_mongo
import cci_mini_elastic


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



				def show_mongo_config( self ) :
							"""

							:param bootstrap:
							:return:
							"""


							layout = GridLayout( orientation = 'horizontal' ,
											  cols = 1 ,
											  background_color = [0,0,0,0])
							action_bar = Builder.load_string( self._retr_resource( 'dlg_action_bar' ) )
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
							grid.add_widget( Button( text = 'test connect'  ,
													 valign = 'middle',
													 background_color = [0,0,0,0] ,
											         color = [1,0,0,1] ) )
							scroll.add_widget( grid )
							layout.add_widget( scroll )


							#event = threading.Event()

							try :
								#event.wait( timeout=5 )
								#get payload
								"""
								App.get_running_app().dbpq_lk.acquire()
								lst = list()
								while not App.get_running_app().dbpq.empty() :
									payload = App.get_running_app().dbpq.get()
									#m = [ str( x )  for x in payload]
									#lst.append( m )
									for x in payload :
										s = '%s segment=%s \ncall moniker=%s \nparams=%s' \
												% ( str( x[5] ) ,
														 x[2] ,
														 x[3] ,
														 x[4]
													)
										grid.add_widget( Button( text = s , halign = 'center' , font_size = 14 ,
																 size_hint_y = None , size_hint_x = 480  ) )
								"""

								popup = ConsolePopup( title='document context' , content=layout )
								#btn = popup.content.children[1].children[0].children[0]
								#btn.on_press = popup.on_press_context
							finally :
								#App.get_running_app().dbpq_lk.release()
								pass

							popup.open()