
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
#import sqlite3
import time
import signal
import Queue
import base64
import time


from tornado.concurrent import run_on_executor
from concurrent.futures import ThreadPoolExecutor

from tornado.wsgi import WSGIContainer
from tornado.httpserver import HTTPServer
from tornado.ioloop import IOLoop
from tornado import gen
from tornado.queues import Queue


import kafka

#cci
from application import app , mongo_no_resource_exception , _logger
from streams import tr_mongo_rest , \
					tr_bimini , \
					tr_trinity , \
					tr_utils

max_wait_seconds_before_shutdown  = 3


api = Api( app )

http_server = None


const_per_page = 20


class query_session_form( Form ) :
    session_id = StringField( 'session_id:' )
    submit = SubmitField('Submit')


# --------------------------------------------------------------------------------------------------------
@app.errorhandler( 404 )
def page_not_found( e ) :

    return render_template( 'kc_error.html' , e=e.message ) , 404



# --------------------------------------------------------------------------------------------------------
@app.errorhandler( mongo_no_resource_exception )
def handle_mongo_exception( e ) :
    return render_template( "mongo_404.html", e=e.message )  , 404



# ------------------------------------------------------------------------------
@app.route('/index')
@app.route( "/" )
def index() :
				_logger.info( '...index...' )
				return render_template( "index.html" ,
										device = '"' + tr_utils.local_mac_addr() + '"' )



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
				 sys.exit( 1 )


		except Exception as e:
			_logger.error( '...error in  trinity server...' + e.message )
			sys.exit( 1 )







