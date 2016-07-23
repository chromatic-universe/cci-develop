# kc_dbmanager.py william k. johnson 2016


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


# -----------------------------------------------------------------------------------
class kc_db_manager( object ) :

			"""
			kc_db_manager
			"""

			def __init__( self ,
						  default_db ,
						  logger = None )  :

				"""

				:param default_db:
				:param logger:
				:return:
				"""


				if logger is None :
					raise Exception( 'no logging instance specified...' )
				self._logger = logger
				self._logger.info( '...db manager initialized...' )

				# default db
				try :
					self._current_db = sqlite3.connect( default_db  )
				except sqlite3.DatabaseError as e :
					self._logger.error( e.message )



			def __del__( self ) :
				"""

				:return:
				"""

				if self._current_db :
					self._current_db.close()



			@property
			def log( self ) :
				return self._logger
			@log.setter
			def log( self , lg ) :
				self._logger = lg
			@property
			def db( self ) :
				return self._current_db
			@db.setter
			def db( self  , daba ) :
				self._current_db = data

