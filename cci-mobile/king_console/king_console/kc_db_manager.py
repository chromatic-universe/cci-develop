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
import uuid

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'

sql_cursor_dictionary = {  'sd_insert_session' : 'insert into sessions  (session_name ,'
												 'session_user ,'
												 'context ,'
												 'session_moniker ,'
												 'device_id) '
												 'values ( %s , %s , %s , %s , %s )' ,
							'sd_insert_session_call' :   'insert into session_call_history'
														 '  (session_name ,'
														 'call_segment ,'
														 'call_moniker ,'
														 'call_params) '
														 'values ( %s , %s , %s , %s )'
								}



# -----------------------------------------------------------------------------------
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return proc.check_output( ['cat' , '/sys/class/net/wlan0/address'] ).strip()
		except :
			pass


# -----------------------------------------------------------------------------------
def quoted( s ) :
	return '"' +  s  + '"'


# -----------------------------------------------------------------------------------
def quoted_list_to_tuple( lst ) :
	return tuple( [quoted( x ) for x in lst] )




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
				    # cursor
					self._db_cursor = self._current_db.cursor()



				def __del__( self ) :
					"""

					:return:
					"""

					if self._current_db :
						self._logger.info( '...db manager uninitialized...' )
						self._current_db.close()




				def _execute_sql_update( self , sql_key , params  ) :
					"""

					:param sql_key:
					:param args:
					:param kargs:
					:return:
					"""

					try :

							s = sql_cursor_dictionary[sql_key]
							s = s % quoted_list_to_tuple( params )

							self._db_cursor.execute( s )
							self.db.commit()

							self._logger.info( '...' +  sql_key  + 'executed...'  + str( params ) )

					except sqlite3.IntegrityError as e :
						self._logger.error( 'integrity error in update statement '
							+ e.message )
					except sqlite3.OperationalError as e :
						self._logger.error( 'statement failed: '
							+ e.message )
					except TypeError as e :
						self._logger.error( '...not enough aruments for db update...' )



				def insert_session( self ,
									user ,
									level ,
									moniker ) :
					"""

					:param user:
					:param level:
					:param moniker:
					:return session uid:
					"""

					uid = str( uuid.uuid4() )
					params = [uid , user , level  , moniker ,  local_mac_addr() ]
					self._execute_sql_update( 'sd_insert_session' , params )

					return uid




				def insert_session_call( self ,
										 session_id ,
										 segment ,
										 function ,
										 params ) :
					"""

					:param session_id:
					:param segment:
					:param function:
					:param params:
					:return:
					"""

					params = [ session_id , segment , function , params ]
					self._execute_sql_update( 'sd_insert_session_call' , params )




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
				@property
				def cursor(  self ) :
					return self._db_cursor
				@cursor.setter
				def cursor( self  , cur ) :
					self._db_cursor = cur



# --------------------------------------------------------------------------------------------------------------
if __name__ == '__main__' :

				# logger
				logger = logging.getLogger( "kc_db_manager" )
				logger.setLevel( logging.DEBUG )
				ch = logging.StreamHandler()
				ch.setLevel( logging.DEBUG )
				formatter = logging.Formatter( log_format )
				ch.setFormatter(formatter)
				logger.addHandler(ch)
				logger.info( '...kc_db..manager...' )


				kcdb = kc_db_manager( '../king_console.sqlite'  , logger )
				params = [str( uuid.uuid4() )  , 'wiljoh' , 'level1' , 'latenight review' ,  local_mac_addr() ]

				uid = kcdb.insert_session( 'wiljoh' , 'level1' , 'latenight review'  )
				kcdb.insert_session_call( uid , 'application' , 'init' , '(session_id)' )
