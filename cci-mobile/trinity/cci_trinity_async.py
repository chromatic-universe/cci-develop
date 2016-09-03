# cci_trinity_async.py    william k. johnson  2016



import time
import json
import logging
import signal
import os
import importlib

from tornado.ioloop import IOLoop
import tornado.gen
import tornado.web
import urllib
from tornado.queues import Queue
from tornado.ioloop import PeriodicCallback
from tornado.locks import Semaphore


max_wait_seconds_before_shutdown  = 3

# cci
from application_vulture  import app ,\
	                             mongo_no_resource_exception , \
								 _logger
callback_class_dispatch = { 'document' : 'tr_payload_stalker' ,
							'stream'   :  'tr_stream-stalker' }
stream_mod = importlib.import_module( 'streams.tr_stream_manager'  )
stream_mongo_mod = importlib.import_module( 'streams.tr_mongo_rest'  )

# exclusive
policy_semaphore = Semaphore( 1 )
g_periodic_callbacks = dict()



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

			# queue vulture
			client = queue_client()
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
				tornado.ioloop.IOLoop.instance().add_callback(client.watch_queue)


				# Create the web server with async coroutines
				_logger.info( '...initializing http services....' )
				application = tornado.web.Application([	(r'/trinity-vulture/start', queue_handler_start_policy ) ,
														( r'/trinity-vulture/stop' ,  queue_handler_stop_policy ) , ], debug=True)

				_logger.info( '...starting listener on port 7081....' )
				application.listen( 7081 )

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