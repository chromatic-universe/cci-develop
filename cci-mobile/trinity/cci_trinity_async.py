# cci_trinity_async.py    william k. johnson  2016



import time
import json
import logging
import signal
import os

from tornado.ioloop import IOLoop
import tornado.gen
import tornado.web
import urllib
from tornado.queues import Queue
from tornado.ioloop import PeriodicCallback

max_wait_seconds_before_shutdown  = 3
log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'

from application_vulture  import app ,\
	                             mongo_no_resource_exception , \
								 _logger
from streams import tr_mongo_rest


g_periodic_calbacks = dict()

# --------------------------------------------------------------------------------------
class queue_client() :

			def __init__(self):
				self.queued_items = Queue()


			@tornado.gen.coroutine
			def watch_queue(self):
				while True:
					items = yield self.queued_items.get()
					if items['moniker'] in g_periodic_calbacks :
						_logger.info( '..policy %s already in effect' % items['moniker'] )
						continue
					pc = PeriodicCallback( lambda: pc_callback( items['moniker'] ) , 5000  )
					_logger.info( '..started periodic callback with params%s' % json.dumps( items ) )
					pc.start()
					g_periodic_calbacks[items['moniker']] = pc




# --------------------------------------------------------------------------------------
class queue_handler_start_policy( tornado.web.RequestHandler ) :


			@tornado.gen.coroutine
			def post( self ) :
				"""

				:return:
				"""
				#json_data = json.loads( self.request.data )

				json_data = json.loads( self.request.body )
				yield client.queued_items.put( json_data )
				_logger.info( 'queued a new item: %s' % self.request.body )





# --------------------------------------------------------------------------------------
class queue_handler_stop_policy( tornado.web.RequestHandler ) :


			@tornado.gen.coroutine
			def post( self ) :
				"""

				:return:
				"""


				json_data = json.loads( self.request.body )
				moniker = json_data['moniker']

				if moniker in g_periodic_calbacks :
					g_periodic_calbacks[moniker].stop()
					_logger.info( '...stopped...: %s' % moniker )
				else :
					_logger.info( '...could not stop...not started: %s' % moniker )






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

		for key , value in g_periodic_calbacks.iteritems() :
			if value.is_running() :
				_logger.info( '...shutting down policy %s ' %  key )
				value.stop()


		def stop_loop():
			now = time.time()
			if now < deadline and ( io_loop._callbacks or io_loop._timeouts ) :
				io_loop.add_timeout( now + 1 , stop_loop )
				io_loop.add_timeout( now + 1 , stop_loop )
			else:
				io_loop.stop()
				_logger.info( '...shutdown....' )

		stop_loop()

def pc_callback( moniker ) :
	print 'the original corny snaps for %s!' % moniker



# --------------------------------------------------------------------------------------
if __name__ == "__main__":

			# mongo
			client = queue_client()

			# logger



			# Watch the queue for when new items show up
			_logger.info( '...initializing queue vulture....' )
			tornado.ioloop.IOLoop.instance().add_callback(client.watch_queue)


			# Create the web server with async coroutines
			_logger.info( '...initializing htto services....' )
			application = tornado.web.Application([	(r'/trinity-vulture/start', queue_handler_start_policy ) ,
													( r'/trinity-vulture/stop' ,  queue_handler_stop_policy ) , ], debug=True)

			_logger.info( '...starting listner on port 7081....' )
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
