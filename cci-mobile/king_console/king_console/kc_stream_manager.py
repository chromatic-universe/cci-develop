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



class kc_payload_stalker( cci_mobile ) :
				"""
				payload staker
				"""


				def __init__( self ,
							  policy = None ,
							  db_manager = None  ) :

					"""

					:param policy:
					:param db_manager:
					:return:
					"""

					super( kc_payload_stalker , self ).__init__()

					if db_manager is None :
						raise ValueError( '%s cannot proceed , db manager not instantiated' % \
										          self.__class__.__name__  )
					self._signal_event = threading.Event()
					self._policy = policy
					self._policies = dict()
					self._db_manager = db_manager




				def __repr__( self ) :
					 """
					 returns string representation and construction info
					 :rtype : basestring
					 :return:
					 """

					 return "{__class__.__name__}(policy={_policy!r}," \
							"db_manager=(_db_manager})". \
							format( __class__=self.__class__ , **self.__dict__ )








