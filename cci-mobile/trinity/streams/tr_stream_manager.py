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
															'and provider_type = %s '
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
			@abc.abstractproperty
			def supported_monikers( self ) :
				pass


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





# -------------------------------------------------------------------------------------------
class tr_payload_stalker( tr_stalker ) :
				"""
				payload stalker
				"""



				def __init__( self ,
							  policy = None  ,
							  db_connect_str = None ) :

					"""

					:param policy:
					:param db_manager:
					:return:
					"""

					# logging
					id = self.__class__.__name__ + ':' +  policy
					self._logger = tr_utils.init_logging( id  )
					self._logger.info( self.__class__.__name__ + '...'  )

					super( tr_payload_stalker , self ).__init__()

					document_monikers = {
										   'mongodb' : self._on_mongo_document ,
										   'elasticsearch' : self._on_elasticsearch_document
										}

					self._db_connect_str = db_connect_str
					self._current_db = None

					if db_connect_str is None :
						raise ValueError( '%s cannot proceed , no database specified' % \
										          self.__class__.__name__  )



					# default db
					try :
						self._current_db = sqlite3.connect( db_connect_str  )
					except sqlite3.DatabaseError as e :
						self._logger.error( e.message )
						raise



					self._signal_event = threading.Event()
					self._policy = policy
					self._policy_dictionary = None
					self._policy_call = None
					self._supported_monikers = document_monikers


					if self._policy is None :
						self._policy_dictionary = self._retrieve_default_doc_policy()
					print self._policy



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





				def _retrieve_default_doc_policy( self ) :
					"""

					:return default policy dictioary:
					"""


					return self.execute_naked_sql_result_set( self._current_db ,
 													  		  tr_utils.dict_factory ,
													          sql_cursor_dictionary['sql_retrieve_default_policy'] ,
									   						  ['default' , 'document'] ,
															  self._logger )






				# services
				def prepare( self ) :
					"""
					prepare
					"""


					# assert
					if self._policy_dictionary is None :
						raise

					try :
						self._policy_call = self._supported_monikers[self._policy_dictionary['provider'] ]
					except :
						raise ValueError( '%s cannot proceed , invalid provider' % \
										          self.__class__.__name__  )




				def stalk( self ) :
					"""
					stalk
					"""

					perform = self._policy_call
					perform()




				def _on_mongo_document( self )  :
					"""

					:return
					"""

					print 'mongodb'



				def _on_elasticsearch_document( self ) :
					"""

					:return
					"""

					print 'elasticsearch'




				@property
				def policy( self ) :
					return self._policy_dictionary
				@policy.setter
				def policy( self , poly ) :
					self._policy = poly
				@property
				def logger( self ) :
					return self._logger
				@logger.setter
				def logger( self , log ) :
					self._logger = log
				@property
				def supported_monikers( self ) :
					return self._supported_monikers







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








