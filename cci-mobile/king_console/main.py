# kivy
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
from kivy.uix.treeview import TreeView , TreeViewLabel , TreeViewNode
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.config import ConfigParser
from kivy.uix.progressbar import ProgressBar
from kivy.clock import Clock
from kivy.core.window import Window
from kivy.lang import Builder
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
import logging
import importlib
from time import gmtime, strftime , sleep
import subprocess as proc

#cci
from king_console import resource_factory \
	                     as resources , \
						 screen


kivy.require( '1.9.1' )

# dynamic
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



class kingconsoleApp( App ) :
		"""
		maelstrom
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
			self._ret_text = str()
			#view manager
			self._view_manager = None
#
			self._console_local , \
			self._console_real  = self._console_host_name = self._Local_net_info()
			self._console_count = 1

		# helpers
		@staticmethod
		def _retr_resource( resource_id ) :
			"""

			:param resource_id:
			:return ui resource:
			"""

			return resources.const_resource_ids[resource_id]


		# settings
		def build_settings( self , settings ) :
			"""

			:param settings:
			:return:
			"""
			settings.add_json_panel( 'king-consolecontexts',
									  self.config ,
									  data=resources.settings_json )
			settings.add_json_panel( 'king-consoleenvironment',
									  self.config ,
									  data=resources.settings_env_json )
			settings.add_json_panel( 'king-consolestream data',
									 self.config ,
									 data=resources.settings_stream_json )
			self.use_kivy_settings = False


		def build_config( self , config ) :
			"""

			:param config:
			:return:
			"""
			config.setdefaults( 'stream',  {
											'packet_timeout': 3 ,
											'show_stream': 1 ,
											} )
			config.setdefaults( 'network-icmp', {
											'packet_timeout': 1 ,
											'show_stream': 1 ,
											'default_address' : 'www.chromaticuniverse.xyz'
											} )


		def _retr_proc_atom( self , proc_str = None ) :
			"""

			:return proc atom:
			"""

			pass


		def _Local_net_info( self ) :
			"""

			:return:
			"""
			out = str()
			out2 = str()

			try :

					cmd = ["su" ,
						   "-c" ,
						   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
						   "./king_console/ping.pyo" ,
						   "-x"
						  ]
					try :
						out = proc.check_output( cmd  )
						if out :
							pos = out.find( '<ip_info>' )
							if pos :
								out = out[:pos]
							out , out2 = out.split( ':' )
							self.logger.info( ifconfig )
					except proc.CalledProcessError as e :
						self._logger.error( e.message )
						b_ret = False
			except Exception as e :
				b_ret = False
				self._logger.error( e.message )

			return out , out2


		def on_config_change(self, config, section, key, value):
			"""

			:param config:
			:param section:
			:param key:
			:param value:
			:return:
			"""
			self._logger.info("main.py: app.on_config_change: {0}, {1}, {2}, {3}".format(
				config, section, key, value))

			"""
			if section == "section1":
				if key == "key1":
					self.root.ids.label. = value
				elif key == 'font_size':
					self.root.ids.label.font_size = float(value)
				elif key == 'default_user':
					self.root.ids.label.default_user = value
			"""

		# android mishegas
		def on_pause(self):
			# save data
			self._logger.info( self.__class__.__name__ + '...'  + 'on_pause' )

			return True


		def on_resume( self ):
			# something
			self._logger.info( self.__class__.__name__ + '...'  + 'on_resume' )

			pass


		def on_start(self) :
			"""

			:return:
			"""
			self.root.current_screen.ids.console_local_id.text = self._console_local
			self.root.current_screen.ids.console_real_id.text = self._console_real
			self.root.current_screen.ids.console_host_name.text = self._console_ifconfig


		# icmp handlers
		def on_ping_ip_input( self ) :
			"""
			input ping variable
			:return:
			"""

			out = str()
			b_ret = True
			self._logger.info( self.__class__.__name__ + '...on_ping_ip_input'  )

			self._move_to_accordion_item( self.root.current_screen.ids.cci_accordion ,
										  self.root.current_screen.ids.ip_input )
			ip = self.root.current_screen.ids.ip_input.text
			try :

				cmd = ["su" ,
					   "-c" ,
					   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
					   "./king_console/ping.pyo" ,
					   "-s" ,
					   ip
					  ]

				try :
					out = proc.check_output( cmd  )
					self._logger.info( out )
				except proc.CalledProcessError as e :
					b_ret = False
			except Exception as e :
				b_ret = False
				self._logger.error( e.message )

			carousel = self.root.current_screen.ids.maelstrom_carousel_id

			boiler = 'maelstrom[icmp]->ping: ' + \
					  ' ' + self.root.current_screen.ids.ip_input.text
			boiler += '\n'
			boiler += out
			self._logger.info( self.__class__.__name__ + '...boiler='  + boiler)

			pos = boiler.find( '#[QPython]' )
			if pos :
				boiler = boiler[:pos]

			layout = GridLayout( cols = 1 ,
								 padding = [0 , 5 , 0 ,5]
								  )

			layout.add_widget( Label( text = 'icmp ping console #'+ str( self._console_count ),
									color = [ 1, 0 , 0 , 1] ,
									font_size = 16 ,
									size_hint_y = 0.1 ) )



			scrolly = Builder.load_string( self._retr_resource( 'text_scroller' ) )
			tx = scrolly.children[0]
			tx.text = boiler
			layout.add_widget( scrolly )

			layout.add_widget( Label( text = strftime("%Y-%m-%d %H:%M:%S", gmtime()) ,
									font_size = 16  ,
									size_hint_y = 0.2 ,
									color = [ 1, 0 , 0 , 1] ) )



			carousel.add_widget( layout )

			carousel.index = len( carousel.slides ) - 1
			self._console_count += 1


		def _selected_accordion_item( self ) :
			"""

			:return accordion item selected:
			"""
			for item in self.root.current_screen.ids.cci_accordion.children :
				try:
					if not item.collapse :
						return item
				except :
					pass


		def accordion_touch_up( self ) :
			"""
			:return:
			"""
			for item in self.root.current_screen.children :
				try:
					if not item.collapse :
						self._logger.info( self.__class__.__name__ + '...' +
										   item.title + '...accordion_item_touch_down' )
				except :
					pass


		def _move_to_accordion_item( self , acc , tag = None ) :
			"""
			workaround for android nesting bug
			:param acc:
			:return:
			"""

			for child in acc.children :
				if child.title == 'king console' :
					child.collapse = False
					child.canvas.ask_update()

			self.root.current_screen.ids.ping_btn.text = "execute"


		def _open_extended_window( self ) :
			"""

			:return:
			"""

			item = self._selected_accordion_item()
			self.root.current = 'screen_' + item.title


		def _manip_extended_window( self ) :
			"""

			:return:
			"""

			self.root.current = 'screen_cci'


		def _on_view_manager( self ) :
			"""

			:return:
			"""

			if not self._view_manager :
				self._view_manager = screen.ViewManagerScreen()
				self._view_manager.name = 'screen_view_manager'
				self._view_manager.id = 'view_manager_screen'

				layout = GridLayout( orientation='horizontal' , cols=1 )
				# action bar
				ab = Builder.load_string( self._retr_resource( 'action_bar' ) )

				layout.add_widget( ab )

				# scroll
				sv = ScrollView()

				# tree view
				tv = TreeView( root_options=dict( text = 'king console') )
				n1 = tv.add_node(TreeViewLabel(text='king console main'))
				n2 = tv.add_node(TreeViewLabel(text='level 1'), n1)
				tv.add_node(TreeViewLabel(text='tcp'), n2)
				tv.add_node(TreeViewLabel(text='network'), n2)
				tv.add_node(TreeViewLabel(text='application'), n2)
				tv.add_node(TreeViewLabel(text='datalink'), n2)
				tv.add_node(TreeViewLabel(text='streams'), n2)
				tv.add_node(TreeViewLabel(text='level 2'), n1)
				tv.add_node(TreeViewLabel(text='level 3'), n1)
				sv.add_widget( tv )

				layout.add_widget( sv )
				self._view_manager.add_widget( layout )
				self.root.add_widget( self._view_manager )

			self.root.current = self._view_manager.name


		# attributes
		@property
		def logger( self ) :
			return self._logger
		@logger.setter
		def logger( self , log ) :
			self._logger = log

        

      

if __name__ == '__main__':


        kc = kingconsoleApp()
        kc.run()
        kc.logger.info( "main...app running....." )
            
