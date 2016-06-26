import kivy
from kivy.uix.accordion import Accordion, AccordionItem
from kivy.uix.carousel import Carousel
from kivy.uix.label import Label
from kivy.app import App
from kivy.uix import image
from kivy.core.window import Window



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


        def on_pause(self):
            # save data 
            return True

        def on_resume(self):
            # something
            pass





if __name__ == '__main__':

         urnackApp().run()
