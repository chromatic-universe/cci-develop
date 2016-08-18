

import sqlite3

# kivy
import kivy
from kivy.utils import platform
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
from kivy.uix.image import Image
from kivy.config import ConfigParser
from kivy.uix.progressbar import ProgressBar
from kivy.clock import Clock , mainthread
from kivy.core.window import Window
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
import subprocess as proc
import threading
import requests
import urllib2
from functools import partial
from kivy.utils import platform
from jnius import autoclass
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
from king_console.kc_stream 	import kc_mongo_config , \
								       kc_kafka_config
from king_console.kc_wireless import *

import paramiko


kivy.require(  '1.9.1'  )

#todo
dlabel = \
"""
Label:
	text_size: self.size
	valign: 'middle'
	halign: 'center'
"""

update_content = \
"""
GridLayout:
	orientation: 'horizontal'
	cols: 1
	Label:
		text: '...updating...'
	ProgressBar:
		max:1000
		value: 250
"""

# -----------------------------------------------------------------------------------
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return proc.check_output( ['cat' , '/sys/class/net/wlan0/address'] ).strip().lower()
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
			self._full_screen_lst = list()
			self._full_item = None

			if self._check_connectivity() :
				self._console_local , \
				self._console_real , \
				self._console_ifconfig , \
				self._console_iwlist =  self._Local_net_info()
			else :
				self._console_local = 'None'
				self._console_real = 'None'
				self._console_ifconfig = 'None'
				self._console_iwlist  = 'None'
				self._logger.error( '...no connectivity...' )

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
			self._is_full_screen = False
			self._is_dirty_payload = False
			self._dlg_param = None
			self._diaspora = True


			Window.on_rotate = self._on_rotate


		def build( self ) :
			"""

			:return:
			"""

			return self.root




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
						 id ,
						 self._console_ifconfig] ) )
			self.dbq.put( package )
			self._session_id = uid

			if self._check_connectivity() :
				# document repository
				try :
					mongo = kc_mongo_config( bootstrap ='cci-aws-3' ,
											 log = self._logger ,
											 device_id = local_mac_addr() ,
											 last_ip = self._console_local ,
											 last_real_ip = self._console_real )
					mongo._update_device_session( True )
				except Exception as e :
					self._logger.error( e.message )
			else :
				self._logger.error( '...could not update session remote info...no connectivity...' )





		def _close_session( self ) :
			"""

			:return:
			"""


			# we don't use db queue in main thread
			package = ( ( 'update_session_status'  ,
						[0 , self._session_id] ) )
			self.dbq.put( package )
			# document repository
			if self._check_connectivity() :
				mongo = kc_mongo_config( bootstrap ='cci-aws-3' ,
										 log = self._logger ,
										 device_id = local_mac_addr() ,
										 last_ip = self._console_local ,
										 last_real_ip = self._console_real)
				mongo._update_device_session( False )
			else :
				self._logger.error( '...could not update session remote info...no connectivity...' )



			pass


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
			iw = str()

			try :

					cmd = ["su" ,
						   "-c" ,
						   "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh"  ,
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
							iw =  essid_scan()


					except proc.CalledProcessError as e :
						self._logger.error( e.message )
						b_ret = False
			except Exception as e :
				b_ret = False
				self._logger.error( e.message )

			return out , out2 , ifconfig , iw



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


			return True



		def on_resume( self ):
			# something


			pass



		@mainthread
		def _show_exit( self ) :
			"""

			:return:
			"""
			layout = Label( text = '...closing streams...standby...' )
			pop = Popup( title='break down' ,
						           content=layout , size=( 400 , 300 ) )
			pop.open()



		def on_stop( self ) :
			"""

			:return:
			"""

			layout = Label( text = '...closing streams...standby...' )
			pop = Popup( title='break down' ,
						           content=layout , size=( 400 , 300 ) )
			pop.open()

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

			db = kc_db_manager( '/data/media/com.chromaticuniverse.cci_trinity/king_console.sqlite' , self._logger )
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





		def _check_connectivity( self ) :
					"""

					:return:
					"""


					if platform == 'android':
						try:
							Activity = autoclass( 'android.app.Activity' )
							PythonActivity = autoclass( 'org.renpy.android.PythonActivity' )
							activity = PythonActivity.mActivity
							ConnectivityManager = autoclass( 'android.net.ConnectivityManager')

							con_mgr = activity.getSystemService( Activity.CONNECTIVITY_SERVICE )

							conn = con_mgr.getNetworkInfo( ConnectivityManager.TYPE_WIFI ).isConnectedOrConnecting()
							if conn :
								return True
							else:
								conn = con_mgr.getNetworkInfo( ConnectivityManager.TYPE_MOBILE ).isConnectedOrConnecting()
								if conn:
									return True
								else:
									return False
						except Exception as e :
							self._logger.error( 'check connectivity failed....' +  e.message )
							return False
					else :
							"""
							try:
								# google , use ip so no dns lookup
								response=urllib2.urlopen( 'http://209.85.232.106' ,timeout=3 )
								return True
							except urllib2.URLError as err :
								pass
							return False
						    """
							return True





		def _handle_payload_update( self , touch  ) :
			"""

			:return:
			"""

			self._dlg_param.dismiss()




		def on_start( self ) :
			"""

			:return:
			"""

			self._logger.info( '...on_start...' )

			try :
				from eve import Eve
				app = Eve()
				self._logger.info( '...imported..eve' )
			except Exception as e :
				self._logger.error( e.message )




			layout = GridLayout( cols = 1 , orientation = 'horizontal' )
			layout.add_widget( Image( source = 'king-console32bw.png' , size_hint_y = .50 ))
			lbl = Builder.load_string( dlabel )
			lbl.text = 'you have non-exported payloads cached locally , export now?'
			layout.add_widget( lbl )
			btns = BoxLayout( orientation = 'horizontal' )
			yes_btn = Button(text='ok', background_color = [0,0,0,0]  )
			no_btn = Button(text='no' , background_color = [0,0,0,0] )
			btns.add_widget( yes_btn )
			btns.add_widget( no_btn )
			layout.add_widget( btns  )
			content = layout
			self._dlg_param = Popup( title='document disposition' ,
						           content=content, auto_dismiss=False , size_hint=(None, None), size=( 400 , 300 ))

			# bind the on_press event of the button to the dismiss function
			yes_btn.bind(on_press=self._handle_payload_update )
			#yes_btn.bind(on_press=self._handle_payload_update( pop=popup ) )
			no_btn.bind(on_press=self._dlg_param.dismiss )

			self._dlg_param.open()
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
			self.root.current_screen.ids.console_interfaces.text = self._console_ifconfig + '\n\n' + self._console_iwlist
			self._cur_console_buffer = self.root.current_screen.ids.console_interfaces.text

			EventLoop.window.bind( on_keyboard = self._hook_keyboard )



		def _hook_keyboard( self , window, key , *largs ) :
				"""

				:param window:
				:param key:
				:param largs:
				:return:
				"""

				if key ==   27  :
					if self.root.current == 'screen_cci' :
						self.stop()
					else :
						self.root.current = 'screen_cci'
						return True

				return False






		def _screen_exists( self , scr = None ) :
			"""

			:return:
			"""
			for screen in self.root.screens :
				if screen.name == scr :
					return True , screen
			return False , None




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




		def _manip_extended_window( self , widg = None ) :
			"""

			:return:
			"""

			self.root.current = 'screen_cci'
			if widg is not None :
				self.root.remove_widget( widg )





		def _on_full_screen( self ) :
			"""

			:return:
			"""


			acc = self.root.current_screen.ids.cci_accordion
			cci = None
			if not self._is_full_screen :
				self._full_screen_lst = list()
				for item in acc.children :
					self._full_screen_lst.append( item )
					if item.title == 'cci-maelstrom' :
						cci = item
				self._full_screen_lst.remove( cci )
				for item in self._full_screen_lst :
					acc.remove_widget( item )
				self._is_full_screen = True
			else :
				cci = acc.children[0]
				acc.remove_widget( cci )
				self._full_screen_lst.reverse()
				for item in self._full_screen_lst :
					acc.add_widget( item )
				acc.add_widget( cci )
				self._is_full_screen = False




		def _on_document_context( self  , context ) :
				"""

				:return:
				"""

				if context == 'mongo' :
					mongo = kc_mongo_config( bootstrap ='cci-aws-3' ,
											 log = self._logger ,
											 device_id = local_mac_addr() )
					mongo.show_config()
				elif context == 'kafka-publisher' :

					kafka = kc_kafka_config( bootstrap = 'cci_aws_1' ,
											 log = self._logger )
					kafka.show_config()




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
		@property
		def session( self ) :
			return self._session_id
		@session.setter
		def session( self , sess ) :
			self._session_id = sess


        

      

if __name__ == '__main__':


        kc = kingconsoleApp()
        kc.run()
        kc.logger.info( "main...app running....." )
            
