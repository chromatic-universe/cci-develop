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



			def _post_function_call( self , func , params ) :
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
										  cols = 1 )

						action_bar = Builder.load_string( self._retr_resource( 'dlg_action_bar' ) )
						layout.add_widget( action_bar )
						scroll = ScrollView()
						grid = GridLayout( cols=1 , orientation = 'horizontal' , size_hint_y = None , size=(400 , 800 ) )
						event = threading.Event()