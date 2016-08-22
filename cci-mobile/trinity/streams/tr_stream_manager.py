# tr_stream_manager.py     william k. johnson 2016


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
import json
import sqlite3
import uuid
import threading
import abc


# dbs
import sqlite3

#cci
import tr_utils




sql_cursor_dictionary = {  'sql_retrieve_default_policy' :  'select * from payload_policy '
														    'where moniker = %s '
															'and active = 1'

						}



# ------------------------------------------------------------------------
class tr_stalker( object )  :
			"""
			staler
			"""

			__metaclass__ = abc.ABCMeta

			'''object model'''
			def __init__( self  ) :

				# logging
				self._logger = tr_utils.init_logging( self.__class__.__name__  )
				self._logger.info( self.__class__.__name__ + '...'  )

				# command line
				self._args_parser = argparse.ArgumentParser( description= self.__class__.__name__   + ' william k. johnson 2015 ' ,
										  epilog='...minimal utilities...')
				self._args_parser._optionals.title = 'flag arguments'



			'''attributes'''
			@property
			def args_parser( self ) :
				return self._args_parser
			@args_parser.setter
			def args_parser( self , args ) :
				self._args_parser = args



			'''services'''
			@abc.abstractmethod
			def prepare( self ) :
				"""
				connect queue
				"""

				pass


			@abc.abstractmethod
			def stalk( self ) :
				"""
				stalk
				"""

				pass




# ------------------------------------------------------------------------
class tr_stream_stalker( tr_stalker )  :
			"""
			stream stalker
			"""


			def  __init__( self , db_connect_str = None)  :

				super( tr_stream_stalker , self ).__init__()

				self._db_connect_str = db_connect_str
				self._current_db = None

				# default db
				try :
					self._current_db = sqlite3.connect( db_connect_str  )
				except sqlite3.DatabaseError as e :
					self.logger.error( e.message )
					raise




			@staticmethod
			def execute_naked_sql_result_set(  current_db ,
											   row_factory ,
											   sql_statement ,
											   params ,
											   log) :
				"""

				:param current_db:
				:param row_factory:
				:param sql_statement:
				:param params:
				:param log:
				:return:
				"""


				payload = list()
				try :

					s = sql_statement
					s = s % tr_utils.quoted_list_to_tuple( params )

					rs = ( None , None )

					current_db.row_factory = row_factory
					cursor = current_db.cursor()
					cursor.execute( s )
					while True :
						rs = cursor.fetchone()
						if rs is None :
							break
						payload.append( rs )


					log.info( '...' +  sql_statement  + ' executed...'  + str( params ) )

				except sqlite3.OperationalError as e :
					log.error( 'statement failed: '
						+ e.message )
				except TypeError as e :
					log.error( '...not enough aruments for db query...' )

				return payload



			'''services'''
			def prepare( self ) :
				"""
				connect queue
				"""

				pass



			def stalk( self ) :
				"""
				stalk
				"""

				pass





# -------------------------------------------------------------------------------------------
class tr_payload_stalker( tr_stream_stalker ) :
				"""
				payload stalker
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

					super( tr_payload_stalker , self ).__init__( db_connect_str=db_connect_str )

					document_monikers = {
										   'mongodb' : self._on_mongo_document ,
										   'elasticsearch' : self._on_elasticsearch_document
										}
					stream_monikers =   {
											'kafka' : self._on_kafka_stream  ,
											'redis' : self._on_redis_stream ,
											'rabbitmq' : self._on_rabbitmq_stream
										}


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
					self._doc_bootstrap = document_bootstrap
					self._doc_moniker = document_moniker
					self._stream_bootstrap = stream_bootstrap
					self._stream_moniker = stream_moniker


					if self._policies is None :
						self._policies = self._retrieve_default_doc_policy()
					print self._policies



				def __repr__( self ) :
					 """
					 returns string representation and construction info
					 :rtype : basestring
					 :return:
					 """

					 return "{__class__.__name__}(policies={_policies!r}," \
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



				def _retrieve_default_doc_policy( self ) :
					"""

					:return default policy dictioary:
					"""


					return self.execute_naked_sql_result_set( self._current_db ,
 													  		  tr_utils.dict_factory ,
													          sql_cursor_dictionary['sql_retrieve_default_policy'] ,
									   						  ['default'] ,
															  self._logger )





				'''services'''
				def prepare( self ) :
					"""
					connect queue
					"""

					pass



				def stalk( self ) :
					"""
					stalk
					"""

					pass





				def _on_mongo_document( self )  :
					"""

					:return
					"""

					pass



				def _on_elasticsearch_document( self ) :
					"""

					:return
					"""

					pass



				def _on_kafka_stream( self ) :
					"""

					:return
					"""

					pass



				def _on_redis_stream( self ) :
					"""

					:return
					"""

					pass



				def _on_rabbitmq_stream( self ) :
					"""

					:return
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
					stalker = tr_payload_stalker( db_connect_str='/data/media/com.chromaticuniverse.' \
																  'cci_trinity/king_console.sqlite' )
				except ValueError as e :
					print  'parameter snafu: %s' %  e.message
				except Exception as e :
					print e.message






# --------------------------------------------------------------------------------------------
if __name__ == '__main__' :

				stalker_main()








