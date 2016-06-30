# screen.py     william k. johnson 2016

from kivy.uix.screenmanager import ScreenManager, \
	                               Screen ,\
	                               RiseInTransition ,\
								   SwapTransition , \
								   FallOutTransition , \
								   SlideTransition


# screens
class CciScreen( Screen ):
    pass


class NetworkScreen( Screen ):
    pass


class TcpScreen( Screen ):
    pass


class ScreenManagement( ScreenManager ) :
	transition = SlideTransition()

