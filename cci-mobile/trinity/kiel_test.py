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
from kiel import clients



@tornado.gen.coroutine
def consume():
    c = clients.SingleConsumer(brokers=["cci-aws-1:9092"])

    yield c.connect()

    while True:
        msgs = yield c.consume("king-console-cci-maelstrom")
        for msg in msgs:
        	print( msg )


def run():

    tornado.ioloop.IOLoop.instance().add_callback(consume )


    try:
         tornado.ioloop.IOLoop.instance().start()
    except KeyboardInterrupt:
         tornado.ioloop.IOloop.instance().stop()



# --------------------------------------------------------------------------------------
if __name__ == "__main__":

        run()
