

import sqlite3

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
from kivy.uix.dropdown import DropDown
from kivy.uix.popup import Popup
from kivy.uix.treeview import TreeView , TreeViewLabel , TreeViewNode
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.bubble import Bubble
from kivy.config import ConfigParser
from kivy.uix.progressbar import ProgressBar
from kivy.clock import Clock , mainthread
from kivy.core.window import Window
from kivy.lang import Builder
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
import subprocess as proc
import threading
import requests

import sqlite3
import Queue
import uuid

#cci
from king_console import resource_factory \
	                     as resources , \
						 screen
from king_console.kc_thread_manager \
				  import kc_thread_manager
from king_console.kc_db_manager import kc_db_manager


kivy.require( '1.9.1' )




# -----------------------------------------------------------------------------------
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return proc.check_output( ['cat' , '/sys/class/net/wlan0/address'] ).strip()
		except :
			pass



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


class CustomDropDown( DropDown ):
    pass



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
			self._full_screen = None
			self._full_screen_txt = str()
			self._full_item = None
#
			self._console_local , \
			self._console_real , \
			self._console_ifconfig = self._console_host_name = self._Local_net_info()
			self._session_id = None

			self._current_ip = self._console_ifconfig
			self._console_count = 1
			self._console_constructed = list()
			self._cur_console_buffer = str()
			self._thrd = kc_thread_manager( self._logger )
			self.stop_event = threading.Event()
			self._db_call_queue = Queue.Queue()
			self._db_payload_queue = Queue.Queue()
			self._db_payload_lk = threading.RLock()


			Window.on_rotate = self._on_rotate

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
			settings.add_json_panel( 'king-console contexts',
									  self.config ,
									  data=resources.settings_json )
			settings.add_json_panel( 'king-console environment',
									  self.config ,
									  data=resources.settings_env_json )
			settings.add_json_panel( 'king-console streams',
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



		def _create_session( self ) :
			"""

			:return:
			"""

			# we don't use db queue in main thread
			uid = str( uuid.uuid4() )
			package = ( ( 'insert_session'  ,
						[uid ,
						 'wiljoh' ,
						 'level1' ,
						 'king console' ,
						  local_mac_addr()] ) )
			self.dbq.put( package )
			id = '(session_id=%s)' % uid
			package = ( ( 'insert_session_call'  ,
						[uid ,
						 'application' ,
						 'init' ,
						 id] ) )
			self.dbq.put( package )
			self._session_id = uid



		def _close_session( self ) :
			"""

			:return:
			"""

			# we don't use db queue in main thread
			package = ( ( 'update_session_status'  ,
						[0 , self._session_id] ) )
			self.dbq.put( package )




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
			ifconfig = str()

			try :

					cmd = ["su" ,
						   "-c" ,
						   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
						   "./king_console/kc_ping.pyo" ,
						   "-x"
						  ]
					try :
						out = proc.check_output( cmd  )
						if out :
							pos = out.find( '<ip_info>' )
							if pos :
								out = out[:pos]
							out , out2 = out.split( ':' )
							cmd = ['busybox' , 'ifconfig']
							ifconfig = proc.check_output( cmd  )
							self.logger.info( ifconfig )
					except proc.CalledProcessError as e :
						self._logger.error( e.message )
						b_ret = False
			except Exception as e :
				b_ret = False
				self._logger.error( e.message )

			return out , out2 , ifconfig



		def _on_rotate( self , rotation ) :
			"""

			:param rotation:
			:return:
			"""

			pass



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


		def on_stop( self ) :
			"""

			:return:
			"""

			# mark session as closed
			self._close_session()

			#stop threads
			for moniker,atom in self._thrd.thrds.iteritems() :
				atom['stop_alert'].set()
				if atom['instance'] :
					atom['instance'].join()
			#wait for all threads to exit.




		def _db_queue_thred( self ) :
			"""

			:return:
			"""

			db = kc_db_manager( './king_console.sqlite' , self._logger )
			while not self._thrd.thrds['db_queue_thred']['stop_alert'].isSet() :
				while not self.dbq.empty() :
					db.db_lk.acquire()
					package  = self.dbq.get()
					# call
					try :
						db._call_map[package[0]] ( package[1] )
					except Exception as e :
						# a query?
						try :
							db._query_call_map[package[0]] ( package[1] )
						except Exception as e:
							self._logger.error( '..in db function call...' + e.message )
					finally :
						db.db_lk.release()

					sleep( 0.25 )



		def on_start( self ) :
			"""

			:return:
			"""

			self._create_session()

			# db queue thread
			thred = threading.Thread( target = self._db_queue_thred )
			moniker = 'db_queue_thred'
			if thred :
					thread_atom = { 'thread_id' : str( thred.ident ) ,
									'stop_alert'  : threading.Event() ,
									'instance' : thred
								  }
					App.get_running_app()._thrd.thrds[moniker] = thread_atom
			thred.start()


			self.root.current_screen.ids.console_local_id.text = self._console_local
			self.root.current_screen.ids.console_real_id.text = self._console_real
			self.root.current_screen.ids.console_interfaces.text = self._console_ifconfig
			self._cur_console_buffer = self.root.current_screen.ids.console_interfaces.text





		def _selected_accordion_item( self ) :
			"""

			:return accordion item selected:
			"""
			acc = self.root.current_screen.ids.cci_accordion
			for item in acc.children :
				try:
					if not item.collapse :
						"""
						if not item.title in self._console_constructed :
							res = item.title + '_acc_item'
							ai = Builder.load_string( self._retr_resource( res ) )
							item.add_widget( ai )
							self._console_constructed.append( item.title )
						"""
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




		def move_to_accordion_item( self , acc , tag = None ) :
			"""
			workaround for android nesting bug
			:param acc:
			:return:
			"""

			for child in acc.children :
				if child.title == 'cci-maelstrom' :
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


		def _on_full_screen( self ) :
			"""

			:return:
			"""


			if not self._full_screen :


				self._full_screen = screen.FullScreen()
				self._full_screen.name = 'full_screen'
				self._full_screen.id = 'screen_full'

				layout = GridLayout( orientation='horizontal' , cols=1 , id = 'full_grid')
				# action bar
				ab = Builder.load_string( self._retr_resource( 'action_bar' ) )
				layout.add_widget( ab )
				tb = Builder.load_string( self._retr_resource( 'text_scroller' ) )
				tb.id = 'full_scroll'
				tb.children[0].id = 'full_scroll_txt'
				carousel = self.root.current_screen.ids.maelstrom_carousel_id.current_slide
				tx = self._cur_console_buffer
				tb.children[0].text = tx
				self._full_screen_txt = tb.children[0]
				layout.add_widget( tb )
				self._full_screen.add_widget( layout )
				self.root.add_widget( self._full_screen )
				self.root.current = 'full_screen'

			else :

				carousel = self.root.current_screen.ids.maelstrom_carousel_id.current_slide
				try :
					self._full_screen_txt.text = carousel.children[1].children[0].text
				except :
					self._full_screen_txt.text = carousel.children[0].children[0].text
				self.root.current = 'full_screen'



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
				tv = TreeView( root_options=dict( text = 'king console' , font_size = 18 ) )
				n1 = tv.add_node(screen.TreeManagerLabel(text='king console main'))
				n2 = tv.add_node(screen.TreeManagerLabel(text='level 1'), n1)
				tv.add_node(screen.TreeManagerLabel(text='tcp'), n2)
				tv.add_node(screen.TreeManagerLabel(text='network'), n2)
				tv.add_node(screen.TreeManagerLabel(text='application'), n2)
				tv.add_node(screen.TreeManagerLabel(text='datalink'), n2)
				tv.add_node(screen.TreeManagerLabel(text='streams'), n2)
				tv.add_node(screen.TreeManagerLabel(text='level 2'), n1)
				tv.add_node(screen.TreeManagerLabel(text='level 3'), n1)
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
		@property
		def dbq( self ) :
			return self._db_call_queue
		@dbq.setter
		def dbq( self , q ) :
			self._db_call_queue = q
		@property
		def dbpq( self ) :
			return self._db_payload_queue
		@dbpq.setter
		def dbpq( self , q ) :
			self._db_payload_queue = q
		@property
		def dbpq_lk( self ) :
			return self._db_payload_lk
		@dbpq_lk.setter
		def dbpq_lk( self , lk ) :
			self._db_payload_lk = lk


        

      

if __name__ == '__main__':


        kc = kingconsoleApp()
        kc.run()
        kc.logger.info( "main...app running....." )
            
