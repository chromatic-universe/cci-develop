# screen.py     william k. johnson 2016

from kivy.properties import StringProperty, ObjectProperty
from kivy.uix.treeview import TreeViewLabel
from kivy.uix.screenmanager import ScreenManager, \
	                               Screen ,\
	                               RiseInTransition ,\
								   SwapTransition , \
								   FallOutTransition , \
								   SlideTransition


class TreeManagerLabel( TreeViewLabel ) :
	"""

	"""
	font_size = 18

# screens
class CciScreen( Screen ) :
	"""

	"""
	accordion_id = ObjectProperty()



class NetworkScreen( Screen ) :
	"""


	"""
	pass


class TcpScreen( Screen ) :
	"""


	"""
	pass


class FullScreen( Screen ) :
	"""

	"""
	pass


class ViewManagerScreen( Screen ) :
	"""


	"""

	def __init__( self ) :
		"""

		ctor
		"""

		super( ViewManagerScreen , self ).__init__()









class ScreenManagement( ScreenManager ) :
	"""


	"""

	transition = SlideTransition()

