import kivy
from kivy.uix.accordion import Accordion, AccordionItem
from kivy.uix.carousel import Carousel
from kivy.uix.label import Label
from kivy.app import App
from kivy.uix import image
from kivy.core.window import Window

#from scapy.all import *

kivy.require( '1.9.1' )

class maelstromApp( App ) :
        """
        maelstrom
        """

        """def build(self):
            root = Accordion( orientation = 'vertical' )
            for x in range(5):
                item = AccordionItem(title='chromatic universe %d' % x)
                item.add_widget(Label(text='Very big content\n' * 10))
                root.add_widget(item)
            return root"""

        def __init__( self ) :
            """

            :return:
            """

            super( maelstromApp , self ).__init__()

            

            with open( 'carousel_id' ,  'w' ) as the_file :
                the_file.write( '0' )

        def on_pause(self):
            # save data 
            return True

        def on_resume(self):
            # something
            pass


      

if __name__ == '__main__':

         maelstromApp().run()
