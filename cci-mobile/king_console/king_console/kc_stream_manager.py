# kc_db_stalker.py     william k. johnson 2016


import os
import sys
#############
import copy
try:
    from cStringIO import StringIO
except:
    from StringIO import StringIO
##############
import logging
import argparse
import socket
import fcntl
import struct
import subprocess as proc
import urllib2
import requests
import sqlite3
import uuid
import threading
from kivy.clock import Clock



import cci_mini_mongo
import sqlite3
# cci
from kc_db_manager import kc_db_manager
from cci_mini_mobile import cci_mobile


document_monikers = ['mongodb' , 'elasticsearch']
stream_monikers = ['kafka' , 'redis' , 'rabbitmq']


# -------------------------------------------------------------------------------------------
class kc_payload_stalker( cci_mobile ) :
				"""
				payload staker
				"""


				def __init__( self ,
							  policy = None ,
							  db_connect_str = None ,
							  document_bootstrap = 'localhost' ,
							  stream_bootstrap =  'localhost' ,
							  document_moniker = 'mongodb' ,
							  stream_moniker = 'kafka' ) :

					"""

					:param policy:
					:param db_manager:
					:return:
					"""

					super( kc_payload_stalker , self ).__init__()

					if db_connect_str is None :
						raise ValueError( '%s cannot proceed , no database specified' % \
										          self.__class__.__name__  )
					if not document_moniker in document_monikers :
						raise ValueError( '%s cannot proceed , document context not supported' % \
										          self.__class__.__name__  )
					if not stream_moniker in stream_monikers :
						raise ValueError( '%s cannot proceed , stream context not supported' % \
										          self.__class__.__name__  )

					self._signal_event = threading.Event()
					self._policy = policy
					self._policies = dict()
					self._db_connect_str = db_connect_str
					self._doc_bootstrap = document_bootstrap
					self._doc_moniker = document_moniker
					self._stream_bootstrap = stream_bootstrap
					self._stream_moniker = stream_moniker
					self._db_manager = None




				def __repr__( self ) :
					 """
					 returns string representation and construction info
					 :rtype : basestring
					 :return:
					 """

					 return "{__class__.__name__}(policy={_policy!r}," \
							"db_manager=(_db_manager})". \
							format( __class__=self.__class__ , **self.__dict__ )




				def __str__( self ) :
					  """
					  returns pretty string
					  :rtype: basestring
					  :return: str
					  """
					  return self.__class__.__name__ +  ' 2016 , william k. johnson'




				def _interpret_policy( self ) :
					  """

					  :return:
					  """
					  pass



				def _retrieve_default_policy( self ) :
					"""

					:return default policy dictioary:
					"""

					pass



				def connect( self ) :
					"""

					:return:
					"""

					pass



				@property
				def db_mgr( self ) :
					return self._db_manager
				@db_mgr.setter
				def db_mgr( self , mgr ) :
					self._db_manager = mgr
				@property
				def policies( self ) :
					return self._policies
				@policies.setter
				def policies( self , poly ) :
					self._policies = poly
				@property
				def doc_bootstrap( self ) :
					return self._doc_bootstrap
				@doc_bootstrap.setter
				def doc_bootstrap( self , strap ) :
					self._doc_bootstrap = strap
				@property
				def str_bootstrap( self ) :
					return self._stream_bootstrap
				@str_bootstrap.setter
				def str_bootstrap( self , strap ) :
					self._stream_bootstrap = strap
				@property
				def doc_moniker( self ) :
					return self._doc_moniker
				@doc_moniker.setter
				def doc_moniker( self , doc) :
					self._doc_moniker = doc
				@property
				def str_moniker( self ) :
					return self._stream_moniker
				@str_moniker.setter
				def str_moniker( self , mon ):
					self._stream_moniker = mon
				@property
				def logger( self ) :
					return self._logger
				@logger.setter
				def logger( self , log ) :
					self._logger = log





# -------------------------------------------------------------------------------------------
def stalker_main() :
				"""

				:return:
				"""

				try :
					stalker = kc_payload_stalker( db_connect_str='/data/media/com.chromaticuniverse. \
																  cci_trinity/king_console.sqlite' )
				except ValueError as e :
					print  'parameter snafu: ' %  e.message
				except Exception as e :
					print e.message






# --------------------------------------------------------------------------------------------
if __name__ == '__main__' :

				stalker_main()








