import sqlite3

# kivy
import kivy
from kivy.utils import platform
from kivy.uix.accordion import Accordion, AccordionItem
from kivy.uix.carousel import Carousel
from kivy.config import Config
from kivy.uix.label import Label
from kivy.app import App
from kivy.uix import image
from kivy.core.window import Window
from kivy.uix.actionbar import ActionButton , ActionBar
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
from kivy.utils import platform
from kivy.lang import Builder
from kivy.base import EventLoop
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
import datetime
import subprocess as proc
import threading
import requests
import base64
import urllib2
from functools import partial
from kivy.utils import platform
import sqlite3
import Queue
import uuid
import json

if platform == 'android' :
	from jnius import autoclass


# cci
from king_console import resource_factory \
	                     as resources , \
                         screen

# ------------------------------------------------------------------------------------
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





# ------------------------------------------------------------------------------------
class CustomDropDown( DropDown ):
    pass



# ------------------------------------------------------------------------------------
class kingconsoleApp( App ) :
                """
                arzamas
                """


                def __init__( self ) :
                    """

                    :return:
                    """

                    super( kingconsoleApp , self ).__init__()

                    self.settings_cls =  SettingsWithSpinner


                    # logger
                    self._logger = logging.getLogger( "king console" )
                    self._logger.setLevel( logging.DEBUG )
                    fh = logging.FileHandler(  'king-console.log' + '-debug.log', mode = 'a' )
                    fh.setLevel( logging.DEBUG )
                    formatter = logging.Formatter( resources.log_format )
                    fh.setFormatter( formatter )
                    self._logger.addHandler( fh )
                    self._logger.info( self.__class__.__name__ + '...'  )





                def build( self ) :
                    """

                    :return:
                    """

                    return self.root




                def _selected_accordion_item( self ) :
                    """

                    :return accordion item selected:
                    """
                    acc = self.root.current_screen.ids.cci_accordion
                    for item in acc.children :
                        try:
                            if not item.collapse :
                                return item
                        except :
                            pass






                # attributes
                @property
                def logger( self ) :
                    return self._logger
                @logger.setter
                def logger( self , log ) :
                    self._logger = log



# ------------------------------------------------------------------------------------
if __name__ == '__main__':

		Config.set( 'graphics', 'width', '480' )
		Config.set( 'graphics', 'height', '800' )
		Config.set( 'input', 'mouse', 'mouse,disable_multitouch' )


		#from kivy.core.window import Window

		Window.size = ( 480 , 800 )

		kc = kingconsoleApp()
		kc.run()
		kc.logger.info( "main...app running....." )
            
