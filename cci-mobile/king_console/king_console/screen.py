# screen.py     william k. johnson 2016

from kivy.uix.screenmanager import ScreenManager, \
	                               Screen ,\
	                               RiseInTransition ,\
								   SwapTransition , \
								   FallOutTransition , \
								   SlideTransition


# screens
class CciScreen( Screen ) :
	"""
	:return
	"""
	pass


class NetworkScreen( Screen ) :
	"""

	:return
	"""
	pass


class TcpScreen( Screen ) :
	"""

	:return
	"""
	pass


class ViewManagerScreen( Screen ) :
	"""

	:return
	"""

	def __init__( self ) :
		"""

		ctor
		"""

		super( ViewManagerScreen , self ).__init__()









class ScreenManagement( ScreenManager ) :
	"""

	:return
	"""

	transition = SlideTransition()

