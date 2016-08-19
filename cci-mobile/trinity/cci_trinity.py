
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


from tornado.wsgi import WSGIContainer
from tornado.httpserver import HTTPServer
from tornado.ioloop import IOLoop

import kafka

#cci
import trinity
from application import app , mongo_no_resource_exception
from streams import tr_mongo_rest

max_wait_seconds_before_shutdown  = 3
log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'



app.config['MONGO_DBNAME'] = 'cci_maelstrom'
app.config['MONGO_URI'] = 'mongodb://cci-aws-3:27017/cci_maelstrom'

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
			return proc.check_output( ['cat' , '/sys/class/net/wlan0/address'] ).strip()
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





@app.route( "/session_call_reprise/<session_id>/batch/<max_id>:<total_count>:<record_ptr>" )
def session_call_reprise(  session_id , max_id , total_count , record_ptr )  :
			"""

			:param session_id:
			:param record_ptr:
			:return:
			"""

			con = sqlite3.connect( "/data/media/com.chromaticuniverse.cci_trinity/king_console.sqlite" )
			con.row_factory = sqlite3.Row

			cur = con.cursor()
			cur.execute( "select * from session_call_history where session_name = %s" \
				         " and idx < %d " \
						 "order by timestamp DESC " \
						 "LIMIT %d" % ( session_id , int(max_id) - 15 , 15 ) )
			rows = cur.fetchall()

			return render_template( "list.html",
									rows = rows ,
									session_id = session_id ,
									total_count = total_count ,
									record_ptr = int( record_ptr ) + 15 ,
									max_id = int(max_id) - 15 )




@app.route( "/session_call_history/<device>" , defaults={'session_id': None})
@app.route( "/session_call_history/<device>/<session_id>" )
def session_call_history(  device , session_id )  :
			   """

			  :return:

			   """


			   con = sqlite3.connect( "/data/media/com.chromaticuniverse.cci_trinity/king_console.sqlite" )
			   con.row_factory = sqlite3.Row

			   cur = con.cursor()
			   if session_id is not None :
					cur.execute( 'select count(*) as count , max( session_call_history.idx ) as ' \
								 'max_idx  from sessions  session_call_history '
								 'inner join  sessions on session_call_history.session_name = sessions.session_name '
								 'where sessions.session_name = %s and sessions.device_id = %s'	 % ( session_id , device ) )
					rows = cur.fetchone()
					if rows is not None :
						count = rows[0]
						max_idx = rows[1]
						cur.execute( 'select * from session_call_history  ' \
									 'inner join  sessions on session_call_history.session_name = sessions.session_name '
									 'where sessions.session_name = %s and sessions.device_id = %s ' \
									 'order by session_call_history.timestamp DESC ' \
									 'LIMIT %d' % ( session_id , device , 15 ) )


						rows = cur.fetchall()
						return render_template( "list.html" ,
											rows = rows ,
											session_id = session_id ,
											total_count = count ,
											record_ptr = len( rows ) ,
											max_id = max_idx )

			   else :
					# grab newest session marked as active
					cur.execute( 	'select  max(session_call_history.idx)  as max_id  , session_call_history.session_name ' \
									'from session_call_history ' \
									'inner join  sessions on session_call_history.session_name = sessions.session_name ' \
									'where sessions.status = 1 and sessions.device_id = %s ' \
									'group by session_call_history.session_name ' \
									'order by session_call_history.timestamp desc ' \
									'limit 1'  % device )

					rows = cur.fetchone()
					if rows is not None :
						max_idx = rows[0]
						session_id = rows[1]

						cur.execute(   'select session_call_history.idx  , session_call_history.session_name ,' \
									   'session_call_history.call_segment , ' \
									   'session_call_history.call_moniker , session_call_history.call_params , ' \
									   'session_call_history.timestamp , sessions.device_id from session_call_history '\
									   'inner join  sessions on session_call_history.session_name = sessions.session_name ' \
									   'where session_call_history.session_name = "%s" '  \
									   'order by session_call_history.timestamp desc '  % session_id )

						rows = cur.fetchall()
						return render_template( "list.html" ,
												rows = rows ,
												session_id = '"' + session_id + '"' ,
												total_count = len( rows ) ,
												record_ptr = len( rows ) ,
												max_id = max_idx )

					return render_template( "index.html" ,
										message = 'no current sessions' )



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




