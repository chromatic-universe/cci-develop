#!/usr/bin/env python
import ctypes
from flask import Flask, request, send_file
import pyscreenshot as ImageGrab
from StringIO import StringIO
import logging
import pyautogui




log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'


app = Flask(__name__)

# logger
_logger = logging.getLogger( "cci-bimini-server" )
_logger.setLevel( logging.DEBUG )
fh = logging.FileHandler(  'cci-bmini-server.log' + '-debug.log', mode = 'a' )
fh.setLevel( logging.DEBUG )
formatter = logging.Formatter( log_format )
fh.setFormatter( formatter )
_logger.addHandler( fh )


@app.route( '/' )
def index() :

			logger.info( app.name + '...index...'  )
			return app.send_static_file( 'index.html' )



# -----------------------------------------------------------------------
@app.route( '/trinity' )
def desktop() :
		 """

		 :return:
		 """

		 try :

			_logger.info( app.name + 'desktop...'  )
			screen = ImageGrab.grab()
			buf = StringIO()
			screen.save(buf, 'JPEG', quality=75)
			buf.seek(0)
			return send_file(buf, mimetype='image/jpeg')

		 except Exception as e :
			 _logger.error( app.name + '...desktop...'  )



# ------------------------------------------------------------------------
@app.route('/click')
def click() :
		"""

		:return:
		"""
		try:
			x = int(request.args.get('x'))
			y = int(request.args.get('y'))
			_logger.info( app.name + '...remote click....x%d:y%d'  % ( x , y ) )
			currentMouseX, currentMouseY = pyautogui.position()
			_logger.info( app.name + '...local mouse....x%d:y%d'  % ( 	currentMouseX , currentMouseY ) )
			pyautogui.moveTo( x , y )
			pyautogui.click()
		except Exception as e :
			_logger.error( app.name + '...click....'  )
			_logger.error( e.message )
			return 'error'

		return 'done'


# --------------------------------------------------------------------------
if __name__ == '__main__':

	_logger.info( app.name + '...'  )
	app.run( host='0.0.0.0', port=7080, debug=True )
