import kivy

import sys
import copy
import logging
import importlib
from time import gmtime, strftime , sleep
import subprocess as proc
import threading
import socket
from kivy.app import App

kivy.require( '1.9.1' )

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'




class ccitrinityApp( App ) :
			"""
			trinity
			"""


			def __init__( self ) :
				"""

				:return:
				"""

				super( ccitrinityApp , self ).__init__()

				# logger
				self._logger = logging.getLogger( "cci trinity" )
				self._logger.setLevel( logging.DEBUG )
				fh = logging.FileHandler(  'trinity' + '-debug.log', mode = 'a' )
				fh.setLevel( logging.DEBUG )
				formatter = logging.Formatter( log_format )
				fh.setFormatter( formatter )
				self._logger.addHandler( fh )
				self._logger.info( self.__class__.__name__ + '...'  )


			def bootstrap_trinity( self ):
						"""

						:return:
						"""

						# another process ont that port?
						#
						try:
							s = socket.socket()
							s.setsockopt( socket.SOL_SOCKET , socket.SO_REUSEADDR , 1 )
							s.bind( ( socket.gethostname()  , 7080 ) )
						except socket.error as e:
							self._logger.error(  '..bootstrap failed...errno:%d...%s' % ( e[0] , e[1] ) )
							sys.exit( 1 )


						try :

								self._logger.info( "bootstrapping cci_trinity....." )
								"""
								cmd = ["python" ,
								  "./cci-trinity.py"
								  ]
								"""
								cmd = [
								  "su" ,
								  "-c" ,
								  "/data/data/com.hipipal.qpyplus/files/bin/qpython.sh" ,
								  "./cci-trinity.pyo"
								  ]


								p = proc.Popen( cmd  )
								self._logger.info( '...process id: %d...' % p.pid )
								sleep( 2 )


						except OSError as e :
							self._logger.error( 'file does not exist?...' + e.message )
							sys.exit( 1 )
						except ValueError as e :
							self._logger.error( 'arguments foobar...' + e.message )
							sys.exit( 1 )
						except Exception as e :
							self._logger.error(  e.message )
							sys.exit( 1 )




			# attributes
			@property
			def logger( self ) :
				return self._logger
			@logger.setter
			def logger( self , log ) :
				self._logger = log




if __name__ == '__main__':


        ct = ccitrinityApp()
        ct.bootstrap_trinity()
        ct.logger.info( "bootstrapped cci_trinity....." )



