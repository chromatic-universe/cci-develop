import time
import json

import tornado.ioloop
import tornado.gen
import tornado.web
import urllib
from tornado.queues import Queue


class queue_client():

			def __init__(self):
				self.queued_items = Queue()


			@tornado.gen.coroutine
			def watch_queue(self):
				while True:
					items = yield self.queued_items.get()
					print items
					# go_do_something_with_items(items)


class queue_handler(tornado.web.RequestHandler) :


			@tornado.gen.coroutine
			def post( self ) :
				"""

				:return:
				"""
				#json_data = json.loads( self.request.data )

				json_data = json.loads( self.request.body )
				yield client.queued_items.put( json_data )
				self.write("queued a new item" )




			def sig_handler( self , sig , frame ) :
					"""

					:param sig:
					:param frame:
					:return:
					"""
					self._logger.warning('...caught signal: %s', sig )
					IOLoop.instance().add_callback( shutdown )



			def shutdown( self ) :
					"""

					:return:
					"""
					self._logger.info(' ...stopping http server...')
					http_server.stop()

					_logger.info( '....will shutdown in %s seconds ...' , max_wait_seconds_before_shutdown )
					tornado.io_loop = IOLoop.instance()

					deadline = time.time() + max_wait_seconds_before_shutdown

					def stop_loop():
						now = time.time()
						if now < deadline and ( tornado.io_loop._callbacks or tornado.io_loop._timeouts ) :
							tornado.io_loop.add_timeout( now + 1 , stop_loop )
							tornado.io_loop.add_timeout( now + 1 , stop_loop )
						else:
							tornado.io_loop.stop()
							self._logger.info( '...shutdown....' )

					stop_loop()



if __name__ == "__main__":

			client = queue_client()

			# Watch the queue for when new items show up
			tornado.ioloop.IOLoop.instance().add_callback(client.watch_queue)

			# Create the web server
			application = tornado.web.Application([
				(r'/', queue_handler),
			], debug=True)

			application.listen( 7081 )
			tornado.ioloop.IOLoop.instance().start()