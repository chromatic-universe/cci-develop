# cci_trinity_async.py    william k. johnson  2016



import time
import json
import logging
import signal
import socket
import os
import subprocess as proc
import threading
import importlib

from tornado.ioloop import IOLoop
import tornado.gen
import tornado.web
import urllib
import sys
import json
from time import sleep
import requests
from tornado.queues import Queue
from tornado.ioloop import PeriodicCallback
from tornado.locks import Semaphore
from tornado.process import Subprocess , CalledProcessError
from kafka import KafkaProducer

max_wait_seconds_before_shutdown  = 3


# cci
from application_vulture  import app ,\
	                             mongo_no_resource_exception , \
								 _logger
from streams import tr_utils , \
				    tr_sqlite

lname = 'king-console-cci-maelstrom'
callback_class_dispatch = { 'document' : 'tr_payload_stalker' ,
							'stream'   :  'tr_stream-stalker' }
stream_mod = importlib.import_module( 'streams.tr_stream_manager'  )
stream_mongo_mod = importlib.import_module( 'streams.tr_mongo_rest'  )

# exclusive
policy_semaphore = Semaphore( 1 )
g_periodic_callbacks = dict()
probe_thred = None
http_tunnel_pid = None
default_stream_proxy_port = 7082
default_document_proxy_port = 7083
const_tunnel_process = 'cci-trinity-tunnel'
stream_bootstrap = None

kp = None



# --------------------------------------------------------------------------------------
class queue_client() :

			def __init__(self):
				self.queued_items = Queue()


			@tornado.gen.coroutine
			def watch_queue(self):

				try :

					while True:
						items = yield self.queued_items.get()
						if items['moniker'] in g_periodic_callbacks :
							_logger.info( '..%s policy %s already in effect' % ( items['provider_type'] ,
																				 items['moniker']  ) )
							continue
						pc = PeriodicCallback( lambda: policy_callback( items['provider_type'] ,
																		items['moniker'] ,
																		items['db_bootstrap']) , int( items['interval'] ) * 1000 )
						_logger.info( '..started periodic callback with params%s' % json.dumps( items ) )
						pc.start()
						with ( yield policy_semaphore.acquire() ) :
							id = '%s-%s' % ( items['moniker'] , items['provider_type'] )
							g_periodic_callbacks[id] = pc

				except Exception as e :
					_logger.error( 'watch_queue: %s' % e.message )
				finally :
					policy_semaphore.release()



# --------------------------------------------------------------------------------------
class queue_session_client() :

			def __init__(self):
				self.queued_items = Queue()


			@tornado.gen.coroutine
			def watch_session_queue(self) :
				r = None
				try :
					while True:
						items = yield self.queued_items.get()
						r = requests.post('http://localhost:7080/mongo/update_device_status',
										  data =  json.dumps( items  ) )
				except Exception as e :
					_logger.error( 'session_watch_queue: %s' % e.message )




# --------------------------------------------------------------------------------------
class queue_stream_client() :

			def __init__(self):
				self.queued_items = Queue()


			@tornado.gen.coroutine
			def watch_stream_queue(self) :
				try :

					while True:
						items = yield self.queued_items.get()
						print items
						kp.send( lname , json.dumps( items ) )
				except Exception as e :
					_logger.error( 'watch_stream_queue: %s' % e.message )




# --------------------------------------------------------------------------------------
class stream_queue_handler_post_msg( tornado.web.RequestHandler ) :


			@tornado.gen.coroutine
			def post( self ) :
				"""

				:return:
				"""

				try :

					json_data = json.loads( self.request.body )
					print json_data
					yield stream_client.queued_items.put( json_data )

				except Exception as e :
					_logger.error( 'stream_queue_handler_post_msg: %s' % e.message )




# --------------------------------------------------------------------------------------
class session_queue_handler_session_update( tornado.web.RequestHandler ) :


			@tornado.gen.coroutine
			def post( self ) :
				"""

				:return:
				"""

				try :

					json_data = json.loads( self.request.body )

					print json_data
					yield session_client.queued_items.put( json_data )
					_logger.info( 'session queued a new item: %s' % self.request.body )
					self.write( 'queued a new item: %s' % self.request.body )
				except Exception as e :
					_logger.error( 'session_queue_handler_update_session: %s' % e.message )





# --------------------------------------------------------------------------------------
class queue_handler_start_policy( tornado.web.RequestHandler ) :


			@tornado.gen.coroutine
			def post( self ) :
				"""

				:return:
				"""

				try :

					json_data = json.loads( self.request.body )
					print json_data
					yield client.queued_items.put( json_data )
					_logger.info( 'queued a new item: %s' % self.request.body )
					self.write( 'queued a new item: %s' % self.request.body )
				except Exception as e :
					_logger.error( 'queue_handler_start_policy: %s' % e.message )





# --------------------------------------------------------------------------------------
class queue_handler_stop_policy( tornado.web.RequestHandler ) :


			@tornado.gen.coroutine
			def post( self ) :
				"""

				:return:
				"""


				json_data = json.loads( self.request.body )
				moniker = json_data['moniker']
				id = '%s-%s' % ( json_data['moniker'] , json_data['provider_type'] )
				if id in g_periodic_callbacks :
					g_periodic_callbacks[id].stop()
					_logger.info( '...stopped...: %s' % id )
					self.write( '...stopped...: %s' % id  )
				else :
					_logger.warning( '...could not stop...policy not started: %s' % id )
					self.write( '...could not stop...policy not started: %s' % moniker )




# --------------------------------------------------------------------------------------
class cci_sibling_probe( tornado.web.RequestHandler )  :
			"""
			:return sibling device id
			"""


			pass




# --------------------------------------------------------------------------------------
def probe_siblings_thred() :
			"""

			:return:
			"""

			ip = tr_utils.retr_local_ip_info()

			sleep( 3 )



# --------------------------------------------------------------------------------------
def sig_handler( sig , frame ) :
			"""

			:param sig:
			:param frame:
			:return:
			"""
			_logger.warning('...caught signal: %s', sig )
			tornado.ioloop.IOLoop.instance().add_callback( shutdown )





# --------------------------------------------------------------------------------------
def shutdown() :
			"""
			:return:
			"""


			_logger.info( '....will shutdown in %s seconds ...' , max_wait_seconds_before_shutdown )
			io_loop = IOLoop.instance()

			deadline = time.time() + max_wait_seconds_before_shutdown

			for key , value in g_periodic_callbacks.iteritems() :
				if value.is_running() :
					_logger.info( '...shutting down policy %s ' %  key )
					value.stop()


			def stop_loop():
				now = time.time()
				if now < deadline and ( io_loop._callbacks or io_loop._timeouts ) :
					io_loop.add_timeout( now + 0.5 , stop_loop )
					io_loop.add_timeout( now + 0.5 , stop_loop )
				else:
					io_loop.stop()



			stop_loop()
			_logger.info( '...shutdown....' )




# -----------------------------------------------------------------------------------------
def policy_callback( provider_type , moniker , db  ) :
			"""

			:param items : json
			:return:
			"""


			live_stalker = None
			try :
				print 'instantiating %s policy->%s  db=%s' % ( provider_type ,
															   moniker  ,
															   db  )
				stalker = getattr( stream_mod , callback_class_dispatch['document'] )
				live_stalker = stalker( db_connect_str = db )
				live_stalker.prepare()
				live_stalker.stalk()
			except Exception as e :
				print e.message
			finally :
				# explicit delete; callbacks are reentrant and objects
				# do not go out of scope
				del live_stalker





# --------------------------------------------------------------------------------------
if __name__ == "__main__":


			# params
			j = json.loads( tr_sqlite.retrieve_config_atom( 'trinity-stream-toggle' )['map'] )
			if j['status'] == 'on' :
				stream_bootstrap = json.loads( tr_sqlite.retrieve_config_atom( 'trinity-kafka-bootstrap' )['map'] )
				_logger.info( '...starting stream tunneler ....' )
				try :
					s = str( stream_bootstrap['bootstrap_servers'] )
					kp = KafkaProducer( bootstrap_servers = ['52.38.98.223'] )
					_logger.info( '...streaming bootstrap initialized...'  )
				except Exception as e :
					_logger.error( '...broken streaming..%s' % e.message )
				#jr_mongo = json.loads( tr_sqlite.retrieve_config_atom( 'trinity-mongo-bootstrap' )['map']  )

			# queue vulture
			client = queue_client()
			session_client = queue_session_client()
			stream_client = queue_stream_client()
			is_running = False

			pid = None
			try :
				 with open( 'pid_vulture' , 'r' ) as pidfile :
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
				# Watch the queue for when new items show up
				_logger.info( '...initializing queue vulture....' )
				tornado.ioloop.IOLoop.instance().add_callback( client.watch_queue )
				tornado.ioloop.IOLoop.instance().add_callback( session_client.watch_session_queue )
				tornado.ioloop.IOLoop.instance().add_callback( stream_client.watch_stream_queue )

				# Create the web server with async coroutines
				_logger.info( '...initializing http services....' )
				application = tornado.web.Application([	(r'/trinity-vulture/start', queue_handler_start_policy ) ,
														( r'/trinity-vulture/stop' ,  queue_handler_stop_policy ) ,
														( r'/trinity-vulture/post_stream_msg' ,  stream_queue_handler_post_msg ) ,
														( r'/trinity-vulture/session_update' ,  session_queue_handler_session_update ) ,
														( r'/trinity-vulture/sibling' ,  cci_sibling_probe ) , ], debug=True)

				_logger.info( '...starting listener on port 7081....' )
				application.listen( 7081 )

				# start siblings probe
				probe_thred = threading.Thread( target = probe_siblings_thred ).start()
				# start http tunnel for local passthrough(all traffic is tnneled , even local)


				# signal handlers
				_logger.info( '...setting system signal handlers....' )
				signal.signal( signal.SIGTERM , sig_handler )
				signal.signal( signal.SIGINT , sig_handler )

				 # write pid
				with open( 'pid_vulture' , 'w' ) as pidfile :
					 pidfile.write( str( os.getpid() ) + '\n'  )


				_logger.info( '...starting main io loop ....' )

				tornado.ioloop.IOLoop.instance().start()
			else :
				_logger.info( '...server already running... pid %s....'  % pid )
				sys.exit( 1 )