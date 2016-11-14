# william k, johnson  2016

import paramiko
import signal
import subprocess as proc
from sshtunnel import SSHTunnelForwarder
from time import sleep
import os
import sys
import threading
import logging
import click

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'


# logger
_logger = logging.getLogger( "cci-mooch" )
_logger.setLevel( logging.DEBUG )
fh = logging.FileHandler(  'cci-mooch-debug.log', mode = 'w' )
fh.setLevel( logging.DEBUG )
ch = logging.StreamHandler(sys.stderr )
ch.setLevel(logging.DEBUG)
formatter = logging.Formatter( log_format )
fh.setFormatter( formatter )
ch.setFormatter(formatter)
_logger.addHandler( fh )
_logger.addHandler( ch )

ping_binary = 'ptunnel'

# --------------------------------------------------------------------------------------
def sig_handler( sig , frame ) :
			"""

			:param sig:
			:param frame:
			:return:
			"""
			_logger.warning('...caught signal: %s', sig )
			sys.exit( sig )




# --------------------------------------------------------------------------------------
def ssh_http_tunnel_proxy_thred( lport , rport , taddr ) :
			"""

			:return:
			"""

			pass




# --------------------------------------------------------------------------------------
def start_ssh_http_tunnel_proxy( local_port = 3128 , remote_port = 8888 , tunnel_addr = '127.0.0.1' ) :
			"""

			:param local_port:
			:param remote_port:
			:param tunnel_addr:
			:return thread handle:
			"""

			thred = threading.Thread( target = self._thread_exec ,kwargs=dict( lport = local_port ,
																			   rport = remote_port ,
																			   taddr = tunnel_addr ) ).start()


			return thred





# --------------------------------------------------------------------------------------
def stream_commmand_output( cmdline ) :
			"""

			:param string cmdline:
			:return iterator :
			"""

			process = proc.Popen( command ,
								  stdout = proc.PIPE ,
								  stderr = proc.STDOUT )

			return iter( process.stdout.readline , b"" )



# --------------------------------------------------------------------------------------
@click.command()
@click.argument( 'ping_server' )
@click.argument( 'local_port' )
@click.argument( 'destination_server' )
@click.argument( 'destination_port' )
@click.option( '--daemon' , default=0 , help='run process as background process' )
def perform( ping_server , local_port , destination_server , destination_port , daemon ) :
			"""

			cci-mooch chromatic universe 2016
			"""

			_logger.info( '...initializing....' )
			# signal handlers
			_logger.info( '...setting system signal handlers....' )
			signal.signal( signal.SIGTERM , sig_handler )
			signal.signal( signal.SIGINT , sig_handler )

			_logger.info( 'ping server: %s , destination server: %s' % ( ping_server , destination_server ))




# --------------------------------------------------------------------------------------
if __name__ == '__main__':




			try :

				perform()

			except OSError as e :
				_logger.error( e.message )







