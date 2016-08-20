
# cci-trinity.py    william k. johnson  2016


import os
import sys
from StringIO import StringIO
import logging

from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response

from flask_restful import Resource, Api
from wtforms import Form, TextField, TextAreaField, validators, StringField, SubmitField
import subprocess as proc
import sqlite3
import time
import signal
import Queue
import base64

from tornado.wsgi import WSGIContainer
from tornado.httpserver import HTTPServer
from tornado.ioloop import IOLoop

import kafka

#cci
import trinity
from application import app , mongo_no_resource_exception
from streams import tr_mongo_rest , \
				    tr_sqlite

max_wait_seconds_before_shutdown  = 3
log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'

api = Api( app )

http_server = None

# logger
_logger = logging.getLogger( "cci-trinity-server" )
_logger.setLevel( logging.DEBUG )
fh = logging.FileHandler(  'cci-trinity-server.log' + '-debug.log', mode = 'a' )
fh.setLevel( logging.DEBUG )
formatter = logging.Formatter( log_format )
fh.setFormatter( formatter )
_logger.addHandler( fh )


const_per_page = 20


class query_session_form( Form ) :
    session_id = StringField( 'session_id:' )
    submit = SubmitField('Submit')


# -----------------------------------------------------------------------------------
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return base64.b64encode( proc.check_output( ['cat' ,
														 '/sys/class/net/wlan0/address'] ).strip() )
		except :
			pass




# --------------------------------------------------------------------------------------------------------
@app.errorhandler( mongo_no_resource_exception )
def handle_mongo_exception( e ) :
    return render_template( "mongo_404.html", e=e.message )  , 404



# ------------------------------------------------------------------------------
@app.route('/index')
@app.route( "/" )
def index() :

				return render_template( "index.html" ,
										device = '"' + local_mac_addr() + '"' )




# -----------------------------------------------------------------------------
@app.route('/query_session/', methods=('GET', 'POST') )
def query_session() :

			id=request.form['session_id']

			return redirect( url_for( 'session_call_history' ,
									  device = '"' + local_mac_addr() + '"' ,
									  session_id = '"' + id + '"' ) )




# -----------------------------------------------------------------------------
@app.route('/show_mongo_api', methods=('GET', 'POST') )
def mongo_api() :


			return redirect( url_for( 'cci_api' ) )




# ------------------------------------------------------------------------------
@app.route( "/trinity" )
def cci_trinity():

			out = 'cci_trinity capture screen...'
			io = StringIO()
			try :

				b_ret , out = trinity.capture_screen( _logger )
				if not b_ret :
					_logger.error( out )
				else :
					io.write( out )
					io.seek( 0 )


			except Exception as e :
				out =  'error in cci_trinity.....'  + e.message
				_logger.error( out )
				return

			return send_file( io , mimetype='image/png' )





# ------------------------------------------------------------------------
@app.route('/click')
def click() :
			"""

			:return:
			"""

			return trinity.capture_clicks( log = _logger ,
										   request = request )


# ------------------------------------------------------------------------
@app.route('/key')
def key() :
			"""

			:return:
			"""

			return trinity.capture_keys( log = _logger ,
										 request = request )




def sig_handler( sig , frame ) :
		"""

		:param sig:
		:param frame:
		:return:
		"""
		_logger.warning('...caught signal: %s', sig )
		IOLoop.instance().add_callback( shutdown )


def shutdown() :
		"""

		:return:
		"""
		_logger.info(' ...stopping http server...')
		http_server.stop()

		_logger.info( '....will shutdown in %s seconds ...' , max_wait_seconds_before_shutdown )
		io_loop = IOLoop.instance()

		deadline = time.time() + max_wait_seconds_before_shutdown

		def stop_loop():
			now = time.time()
			if now < deadline and (io_loop._callbacks or io_loop._timeouts ) :
				io_loop.add_timeout( now + 1 , stop_loop )
				io_loop.add_timeout( now + 1 , stop_loop )
			else:
				io_loop.stop()
				_logger.info( '...shutdown....' )

		stop_loop()




# ------------------------------------------------------------------------------
if __name__ == "__main__"  :

		try :

				k = kafka.SimpleClient( 'cci-aws-1' )
				_logger.info( ''.join( k.topics ) )
				_logger.info( 'opened kafka client...' )


		except Exception as e :
			_logger.error( e.message )

		_logger.info( '....cci_trinity...'  )
		is_running = False
		try :
			 pid = None
			 try :
				 with open( 'pid' , 'r' ) as pidfile :
					pid = pidfile.read().strip()
			 except :
				 pass

			 # check if process is running
			 if pid :
				 try :
					# throws exception if process doesn't exist
					os.kill( int( pid ) , 0 )
					is_running = True
				 except :
					# pid not running
					pass

			 if not is_running :
				 # tornado wsgi server , flask application
				 http_server = HTTPServer( WSGIContainer( app ) )
				 http_server.listen( 7080 )

				 # signal handlers
				 signal.signal( signal.SIGTERM, sig_handler )
				 signal.signal( signal.SIGINT, sig_handler )

				 # write pid
				 with open( 'pid' , 'w' ) as pidfile :
					 pidfile.write( str( os.getpid() ) + '\n'  )
				 # start server
				 IOLoop.instance().start()

			 else :
				 _logger.info( '...server already running... pid %s....'  % pid )
				 sys,exit( 1 )


		except Exception as e:
			_logger.error( '...error in  trinity server...' + e.message )
			sys.exit( 1 )




