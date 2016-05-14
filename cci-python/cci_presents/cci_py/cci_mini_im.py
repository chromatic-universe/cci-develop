# cci_mini_im.py william k. johnson 2015 
# minimal publish subscribe wiht redis and web sockets

import os
import logging
import redis
import gevent
import doctest
import unittest
import json
from abc import abstractmethod ,ABCMeta

from flask import Flask, render_template
from flask_sockets import Sockets
import cci_utils.cci_io_tools as io

redis_config =  {
                  'channel' : 'chat' ,
                  'url' : '127.0.0.1:6379'
                }

application = Flask(__name__)
application.debug = True
sockets = Sockets( application )
redis = redis.from_url( redis_config['url'] )


class cci_pub_sub_intf( object ) :

        __metaclass__  = ABCMeta

        """
        publish subscribe abstract base
        """

        def __init__( self ) :
            pass

        def __del__( self) :
            pass

        @abstractmethod
        def _iter_data( self ) :
            pass

        @abstractmethod
        def register( self, client ) :
            pass

        @abstractmethod
        def send( self , client , data ) :
             pass

        @abstractmethod
        def run( self ) :
             pass

        @abstractmethod
        def start( self ) :
             pass



class cci_base_chat_server( cci_pub_sub_intf ) :


        """
        interface for registering and updating websocket clients.
        """

        # --------------------------------------------------------
        def __init__( self ,
                      red = None ,
                      web_sockets = None ,
                      flask_app = None ) :
            """
            init

            :return:
            """
            super( cci_base_chat_server , self).__init__()

            if red is None :
                raise AssertionError( 'no redis instance available...' )

            self._clients = list()
            self._redis = red
            self._pubsub = self._redis.pubsub()

            self._web_sockets = web_sockets
            self._flask_app = flask_app
            self._logger = io.init_logging( self.__class__.__name__ )
            self._pubsub.subscribe( redis_config['channel'] )

            self._logger.info( self.__class__.__name__ + '.....' )

        # --------------------------------------------------------
        def __del__( self ) :
            """

            :return:
            """
            pass

        # --------------------------------------------------------
        def __iter_data( self ):
            """
            iter data generator expr

            :return:
            """
            for message in self._pubsub.listen():
                data = message.get( 'data' )
                if message['type'] == 'message':
                    self._logger.info(u'Sending message: {}'.format(data) )

                    yield data


        # --------------------------------------------------------
        def register( self, client ):
            """
            register a websocket connection for redis updates.

            :param client:
            :return:

            """
            self._clients.append( client )


        # --------------------------------------------------------
        def send(self, client, data):
            """
           send given data to the registered client.
           automatically discards invalid connections.

            :param client:
            :param data:
            :return:

            """
            try:
                client.send( data )
            except Exception:
                self._clients.remove( client )


        # --------------------------------------------------------
        def run( self ):
            """
            listens for new messages in redis, and sends them to clients.

            :return:
           """

            for data in self.__iter_data():
             for client in self._clients:
                 gevent.spawn(self.send   , client, data)


        # --------------------------------------------------------
        def start( self ):
            """
            maintains redis subscription in the background.

            """
            gevent.spawn( self.run )

        @property
        def logger( self ) :
            return self._logger
        @logger.setter
        def logger( self , log ) :
            self._logger = log
        @logger.setter
        def logger( self , log ) :
            self._logger = log
        @property
        def web_sockets( self ) :
            return self._web_sockets
        @web_sockets.setter
        def web_sockets( self , sock ) :
            self._web_sockets = sock
        @property
        def pub_sub( self ) :
            return self._pubsub
        @pub_sub.setter
        def pub_sub( self , pub ) :
            self._pubsub = pub
        @property
        def redis( self ) :
            return self._redis
        @redis.setter
        def redis( self , red ) :
            self._redis = red

# ----------------------------------------------------------
try :
     # web sockets
     cci_chat  = cci_base_chat_server( red = redis  ,
                                  web_sockets = sockets ,
                                  flask_app = application )
     cci_chat.logger.info( "instantiated redis endpoint.....")

     # start
     cci_chat.start()
     cci_chat.logger.info( "started chat server....." )



except ValueError as err :
     print err

# ------------------------------------------------------------
# static

# -------------------------------------------------------------
@application.route( '/' )
def cci_intro():
    return render_template( 'cci_chat.html' )

# -------------------------------------------------------------
@sockets.route( '/submit' )
def inbox( ws ) :
        """
        receives incoming chat messages, inserts them into redis
        :param ws:
        :return:
        """

        while not ws.closed:
            # sleep to prevent *constant* context-switches.
            gevent.sleep(0.1)
            message = ws.receive()

            if message:
                cci_chat.logger.info( u'inserting message: {}'.format(message))
                cci_chat.redis.publish( redis_config['channel'] , message)


# -------------------------------------------------------------
@sockets.route('/receive')
def outbox(ws):
        """
        sends outgoing chat messages, via chat server
        """

        cci_chat.register( ws )

        while not ws.closed:
            # context switch while chat server  is running in the background.
            gevent.sleep( 0.1 )



