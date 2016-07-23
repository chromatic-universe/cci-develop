# cci-trinity.py    william k. johnson  2016

import os
import subprocess as proc
import platform
import StringIO
import sys

import Queue



click_queue = Queue.Queue()

# ---------------------------------------------------------------------
def process_linux_clicks( log=None  ) :
			"""

			:param log:
			:param q:
			:return:
			"""


			log.info( '...process_linux._clicks...'  )


			import pyautogui
			try:
				log.info( '...pyuautoggui'  )
				while not click_queue.empty() :
					x , y = click_queue.get()
					log.info( '..remote click....x%d:y%d'  % ( x , y  ) )
					currentMouseX, currentMouseY = pyautogui.position()
					log.info( '.local mouse....x%d:y%d'  % ( 	currentMouseX , currentMouseY ) )
					pyautogui.moveTo( x , y )
					pyautogui.click()
			except Exception as e :
				log.error( '...click....'  )
				log.error( e.message )
				return 'error'

			return 'done'




# ---------------------------------------------------------------------
def process_android_clicks( log=None  ) :
			"""

			:param log:
			:return:
			"""


			log.info( '...process_android._clicks...'  )

			try:

				while not click_queue.empty() :
					x , y = click_queue.get()
					log.info( '..remote click....x%d:y%d'  % ( x , y  ) )
					cmd = [ '/system/bin/orng' ,
							'-t' ,
							'/dev/input/event3' ,
							str( x )  ,
							str( y ) ]
					out = proc.check_output( cmd )
					log.info( out )

			except proc.CalledProcessError as e :
				log.error( e.message )
			except Exception as e :
				log.error( '...click....'  )
				log.error( e.message )
				return 'error'

			return 'done'





# ---------------------------------------------------------------------
def capture_screen( log=None ) :
			"""
			:param path to saved image:
			:return

			"""


			b_ret = False
			buf = StringIO.StringIO()
			out = str()

			try :
					pos = sys.platform.find( 'linux4' )
					if pos == -1 :
						andr = False
					else :
						andr = True
					if andr is True :
						process_android_clicks( log )
						out = proc.check_output( ['/system/bin/screencap' ,
									              '-p' ] )
						b_ret = True
					else :
						# linux
						import pyscreenshot as ImageGrab

						process_linux_clicks( log )
						screen = ImageGrab.grab()
						buf = StringIO.StringIO()
						screen.save( buf , 'PNG', quality=75)
						buf.seek( 0 )

						b_ret = True

						return b_ret , buf.getvalue()

			except proc.CalledProcessError as e :
				    # this throws if the function call was
					# made and failed. If the binary was
					# not found we get a naked system exception ,
					# handled next
					log.error( e.message  )
					return b_ret , e.message
			except Exception as e :
					log.error( e.message  )
					out = e.message
			finally :
					if buf :
						buf.close()

			return b_ret , out




# ---------------------------------------------------------------------
def capture_clicks( log=None  , request = None ) :
			"""

			:param log:
			:return:
			"""

			log.info( '...capture_clicks....' )
			x = int( request.args.get('x') )
			y = int( request.args.get('y') )
			clk = ( x , y )

			click_queue.put( clk )

			return 'done'


# ------------------------------------------------------------------------------
if __name__ == "__main__" :

			capture_screen()