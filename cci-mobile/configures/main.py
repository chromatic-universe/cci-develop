from kivy.lang import Builder
from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.properties import StringProperty, ObjectProperty
from kivy.core.window import Window
from kivy.uix.accordion import Accordion, AccordionItem

kv = '''
#:kivy 1.9.1
#:import rgb kivy.utils.get_color_from_hex


<ConsoleAccordion>:

	_orientation: 'vertical'
    # My size "Listner" -call every root width or height change-
    orientation_handler: self.check_orientation(root.width, root.height)

	AccordionItem:
		title: 'application'
		Label:
			text: root.btn_text
			font_size: sp(20)
	AccordionItem:
		title: 'tcp'
		Accordion
			orientation: root._inner_orientation
			AccordionItem:
				title: 'syn ack'
				Label:
					text: root.btn_text
					font_size: sp(20)
			AccordionItem:
				title: 'mini_port_scan'
				Label:
					text: root.btn_text
					font_size: sp(20)
	AccordionItem:
		title: 'network'
		Accordion:
			orientation: root._inner_orientation
			AccordionItem:
				title: 'ping'
			AccordionItem:
				title: 'ping subnet'

	AccordionItem:
		title: 'datalink'
		id: acc_item_datalink
		Accordion:
			orientation: root._inner_orientation
			AccordionItem:
				title: 'arp'
			AccordionItem:
				title: 'arp scan'
	AccordionItem:
		title: 'stream'
		Accordion:
			orientation: root._inner_orientation
			AccordionItem:
				title: 'local'
			AccordionItem:
				title: 'publish~subscribe'
	AccordionItem:
        title: 'king console'
'''


class ConsoleAccordion( Accordion ) :

		btn_text = StringProperty('')
		_orientation = StringProperty('vertical')
		_inner_orientation = StringProperty( 'horizontal' )
		orientation_handler = ObjectProperty(None)

		def __init__( self, *args, **kwargs):
			super( ConsoleAccordion , self ).__init__( *args, **kwargs)

			# get the original orientation
			self._orientation = 'horizontal' if Window.width > Window.height else 'vertical'
			# inform user
			self.btn_text = self._orientation
			self.orientation = self._orientation
			self._inner_orientation =  'vertical' if self.orientation == 'horizontal' else 'horizontal'


		def check_orientation(self, width, height):

			orientation = 'vertical' if height > width else 'horizontal'
			if orientation != self._orientation:
				self._orientation = orientation
				self.orientation_cb(orientation)



		def orientation_cb(self, orientation):
			self.btn_text = orientation
			self.orientation = 'horizontal' if Window.width > Window.height else 'vertical'
			self._inner_orientation =  'vertical' if self._orientation == 'horizontal' else 'horizontal'


class ConsoleApp( App ) :

		# android mishegas
		def on_pause(self):
			# save data


			return True


		def on_resume( self ):
			# something

			pass


		def build(self):

			return ConsoleAccordion()





Builder.load_string( kv )


if __name__ == '__main__' :

    ConsoleApp().run()