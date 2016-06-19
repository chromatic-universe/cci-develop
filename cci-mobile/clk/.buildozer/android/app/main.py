# main.py     william k, johnson 2016

#import doctest

import kivy
from kivy.app import App
from kivy.clock import Clock
from kivy.core.text import LabelBase
from kivy.core.window import Window
from kivy.utils import get_color_from_hex

from time import strftime

kivy.require( '1.9.1' )

# ----------------------------------------------------------------------
class ClockApp( App ) :
        """
r        rudimentary stopwatch utility
        """

        def __init__( self ) :
            """

            :return:
            """

            super( ClockApp , self ).__init__()

            self._sw_started = False
            self._sw_seconds = 0

        def on_start(self) :
            """

            :return:
            """

            Clock.schedule_interval( self.update , 0 )

        def update( self, nap ) :
            """

            :param nap:
            :return:
            """

            if self._sw_started:
                self._sw_seconds += nap

            self.root.ids.time.text = strftime('[b]%H[/b]:%M:%S')

            m, s = divmod( self._sw_seconds, 60)
            self.root.ids.stopwatch.text = ('%02d:%02d.[size=40]%02d[/size]' %
                                          (int(m), int(s), int(s * 100 % 100)))

        def start_stop( self ) :
            """

            :return:
            """

            self.root.ids.start_stop.text = 'Start' if self._sw_started else 'Stop'
            self._sw_started = not self._sw_started


        def reset(self) :
            """

            :return:
            """

            if self._sw_started:
                self.root.ids.start_stop.text = 'Start'
                self._sw_started = False

            self._sw_seconds = 0



# ----------------------------------------------------------------------
if __name__ == '__main__' :

            Window.clearcolor = get_color_from_hex( '#101216' )
            LabelBase.register(name='Roboto',
                       fn_regular='Roboto-Thin.ttf',
                       fn_bold='Roboto-Medium.ttf')
            ClockApp().run()



