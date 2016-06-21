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
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
import logging
import importlib

kivy.require( '1.9.1' )

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'

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

            # logger
            self._logger = logging.getLogger( "cci_maelstrom" )
            self._logger.setLevel( logging.DEBUG )
            fh = logging.FileHandler(  'cci_maelstrom.log' + '-debug.log', mode = 'a' )
            fh.setLevel( logging.DEBUG )
            formatter = logging.Formatter( log_format )
            fh.setFormatter( formatter ) 
            self._logger.addHandler( fh )
            self._logger.info( self.__class__.__name__ + '...'  )


        # android mishegas
        def on_pause(self):
            # save data 
            self._logger.info( self.__class__.__name__ + '...'  + 'on_pause' )

            return

        def on_resume(self):
            # something
            self._logger.info( self.__class__.__name__ + '...'  + 'on_resume' )

        # icmp handlers
        def on_ping_ip_input( self ) :
            """
            input ping variable
            :return:
            """

            box = BoxLayout( orientation='vertical' )
            box.add_widget(Label(text='enter ip or addres:'))
            box.add_widget(TextInput(text='www.chromaticuniverse.zyz' ) )
            box.add_widget( Button( text='ok' , id='dismiss') )
            popup = Popup( title='icmp request reply',
                           size_hint=(None, None) ,
                           size=(300,300) ,
                           content= box ,
                           auto_dismiss=False )
            for item in box.children :
                if item.id == 'dismiss' :
                    item.on_press=popup.dismiss
            popup.open()


        def id( key ) :
            """
            interface id element
            :param key:
            :return element:
            """
            return self.root.ids[key]



        def accordion_touch_up( self ) :
            """
            touch down of accordion item
            :para moniker string:
            :return:
            """
            for item in self.root.children :
                try:
                    if not item.collapse :
                        self._logger.info( self.__class__.__name__ + '...' +
                                           item.title + '...accordion_item_touch_down' )
                except :
                    pass


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
            
