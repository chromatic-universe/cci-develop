# william k, johnson  chromatic universe 2016

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

log_format = '%(asctime)s.%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'


ping_binary = 'ptunnel'
ptunnel_timeout = 5
tunnel_proxy_event = threading.Event()


# ------------------------------------------------------------------------
def init_logging( moniker = 'current_app' , fmt = log_format ) :

    """
    initialize application logging
    :param logger:
    :param moniker:
    :param fmt:
    :return logger :
    """

    logger = logging.getLogger( moniker )

    # setup logging

    # create logger
    logger.setLevel( logging.DEBUG )
    # create file handler strange file extension
    # tells python logging module to overwrite file
    fh = logging.FileHandler( moniker + '-debug.log', mode = 'w' )
    fh.setLevel( logging.DEBUG )

    # create console handler
    ch = logging.StreamHandler()
    ch.setLevel( logging.DEBUG )

    # create formatter and add it to the handlersuntitled
    formatter = logging.Formatter( fmt )
    fh.setFormatter( formatter )
    ch.setFormatter( formatter )

    # add the handlers to the self._logger
    logger.addHandler( fh )
    logger.addHandler( ch )

    return logger




# --------------------------------------------------------------------------------------
def ssh_http_tunnel_proxy_thred( lport , rport , taddr , key_path ) :
			"""

			:return:
			"""

			pass




# --------------------------------------------------------------------------------------
def start_ssh_http_tunnel_proxy( local_port = 3128 ,
								 remote_port = 8888 ,
								 tunnel_addr = '127.0.0.1' ,
								 key_path = '/home/wiljoh/cci-develop.pem' ) :
			"""

			:param local_port:
			:param remote_port:
			:param tunnel_addr:
			:return thread handle:
			"""

			thred = threading.Thread( target = ssh_http_tunnel_proxy_thred ,kwargs=dict( lport = local_port ,
																						 rport = remote_port ,
																						 taddr = tunnel_addr ,
  																				         key_path = pkey_path ) ).start()


			return thred


# -------------------------------------------------------------------------------------
class cci_tunnel_moocher( object ) :
			"""
			cci tunnel moocher
			"""


			# object model
			def __init__( self ) :

					pass


			# immutable
			# ----------------------------------------------------------------------
			@staticmethod
			def port_vulture( port ) :
					"""

					:param port:
					:return pid:
					"""

					# could be easier , but socket based  discovery
					# methods are sketchy and very implementation
					# specific. we rely on netstat , which is fairly
					# portable , instead
					pid = -1
					try :

						if not os.geteuid() == 0 :
							print  'need to be root to call port vulture...\n'
							sys.exit( 1 )
						cmd = list()
						if os.path.exists( '/system/bin/busybox' ) :
							cmd = [ 'busybox' , 'netstat' , '-tulpn']
						else :
							cmd = ['netstat' , '-tulpn']
						nstat = proc.Popen( cmd , stdout=proc.PIPE )
						cmd = ['grep' , port]
						grep = proc.Popen( cmd , stdin=nstat.stdout , stdout=proc.PIPE )
						nstat.stdout.close()
						output = grep.communicate()[0]
						nstat.wait()

						segments = output.strip().split()
						if len( segments ) :
							if segments[0] == 'tcp' or segments[0] == 'tcp6' :
								# pid will be last segment
								raw_pid = segments[len( segments ) - 1]
								s = raw_pid.split( '/')
								pos =  s[0].find( ' ' )
								if pos != -1 :
									x = s[0][pos:]
									x = s.strip().split()
									pid = str( x )
								else :
									pid = int( s[0] )

							return 	True , pid

						return False , pid

					except ValueError as e :
						print 'error in parameter list %s' % e.message
						return False , -1
					except OSError as e :
						print 'binary does not exist?  %s' % e.message
						return False , -1




			# ----------------------------------------------------------------------
			@staticmethod
			def sig_handler( sig , frame ) :
					"""

					:param sig:
					:param frame:
					:return:
					"""
					_logger.warning('...caught signal: %d', sig )




			# -----------------------------------------------------------------------
			def preamble( self , local_port ) :
					"""

					:param log:
					:return:
					"""

					# need root for raw sockets
					self._logger.info( '...cci-moocher...chromatic universe 2016..initializing....' )
					if not os.geteuid() == 0 :
						self._logger.error(  '....need to be root.....' )
						sys.exit( 1 )
					# local port available?
					b_ret , pid = port_vulture( local_port )
					if not b_ret :
						self._logger.info( '...port %s is open....' % local_port )
					else :
						self._logger.error( '...port %s is already in use by process %d....' % ( local_port , pid ) )
						sys.exit( 1 )

					# signal handlers
					self._logger.info( '...setting system signal handlers....' )
					signal.signal( signal.SIGTERM , sig_handler )
					signal.signal( signal.SIGINT , sig_handler )




			# attributes
			@property
			def logger( self ) :
				return self._logger
			@logger.setter
			def logger( self , log ):
				self._logger = log




# -------------------------------------------------------------------------------------
class cci_http_tunnel_moocher( cci_tunnel_moocher ) :
			"""
			cci http tunnel moocher
			"""


			# object model
			def __init__( self) :
				"""

				:return:
				"""

				super( cci_http_tunnel_moocher , self ).__init__()

				self._logger = init_logging( self.__class__.__name__ )

				self._tunnel_thred = None
				self._ping_addr = None
				self._local_port = None
				self._dest_addr = None
				self._dest_port = None
				self._daemon = False
				self._create_proxy = True
				self._ssh_path = None
				self._ssh_user = None
				self._status_ok = False
				self._ptunnel_event = threading.Event()

				self._logger.info( self.__class__.__name__ + '...'  )




			# ----------------------------------------------------------------------
			@staticmethod
			def sig_handler( sig , frame ) :
					"""

					:param sig:
					:param frame:
					:return:
					"""
					self._logger.warning('...caught signal: %d', sig )

					if self._tunnel_thred :
						_logger.info( '..waiting for ping tunnel...' )
						self._tunnel_thred.join( timeout = 2 )




			# --------------------------------------------------------------------------------------
			def ssh_http_tunnel_thred( self , paddr , lport , daddr , dport ) :
						"""

						:return:
						"""

						try :

							self._logger.info( ' @ssh_http_tunnel_thred' )

							cmd = [ 'ptunnel' ,
									'-p' ,
									paddr ,
									'-lp' ,
									lport ,
									'-da' ,
									daddr ,
									'-dp' ,
									dport
								  ]
							process = proc.Popen( cmd ,
												  stdout = proc.PIPE ,
												  stderr = proc.STDOUT )


							self._logger.info( '...ping tunnel daemonized....' )
							self._logger.info( '...pid %d' % process.pid )
						except Exception as e :
							self._status_ok = False


						self._status_ok = True
						self._ptunnel_event.set()



			# --------------------------------------------------------------------------------------
			def start_ssh_http_tunnel( self ) :
						"""


						:return thread handle:
						"""

						self._logger.info( ' @start_ssh_http_tunnel' )
						if not self._daemon :
							self._logger.info( '...running ping tunnel in foreground....' )
							cmd = [ 'ptunnel' ,
								'-p' ,
								self._ping_addr ,
								'-lp' ,
								self.local_port ,
								'-da' ,
								self._dest_addr ,
								'-dp' ,
								self._dest_port
							  ]

							self._command_exec( cmd )

						else :
							thred = threading.Thread( target = self.ssh_http_tunnel_thred ,kwargs=dict( paddr = self._ping_addr ,
																								        lport = self._local_port ,
																								        daddr = self._dest_addr ,
																								        dport = self._dest_port ) )
							thred.daemon = True
							thred.start()


							return thred

						return None




			# --------------------------------------------------------------------------------------
			def command_exec( self , cmdline ) :
						"""

						:param string cmdline:
						:return iterator :
						"""

						self._logger.info( ' @stream_command_output' )

						process = proc.Popen( cmdline ,
											  stdout = proc.PIPE ,
											  stderr = proc.STDOUT )

						self._logger.info( '...pid %d' % process.pid )
						if http_proxy :
							self._logger.info( '...creating http proxy....' )

						process.wait()



			# --------------------------------------------------------------------------------------
			def perform( self ,
						 ping_server ,
						 local_port ,
						 destination_server ,
						 destination_port ,
						 key_path ,
						 daemon ,
						 create_proxy ,
						 user ) :
						"""

						cci-mooch chromatic universe 2016
						"""

						self._ping_addr = ping_server
						self._local_port = local_port
						self._dest_addr = destination_server
						self._dest_port = destination_port
						self._daemon = daemon
						self._create_proxy = create_proxy
						self._ssh_path = key_path
						self._ssh_user = user
						self._status_ok = False

						cci_tunnel_moocher.preamble(  local_port )

						self._logger.info( '...ping server: %s , destination server: %s' % ( ping_server , destination_server ) )
						self._tunnel_thred =  start_ssh_http_tunnel( ping_server ,
																     local_port ,
																     destination_server ,
																     destination_port )
						if self._tunnel_thred :
							self._ptunnel_event.wait( ptunnel_timeout )
							if not self._status_ok :
								_logger.error( '...could not initialize ptunnel....')
								sys.exit( 1 )
							else :
								self._logger.info( ' @status_ok' )
								if http_proxy :
									self._logger.info( '...creating http proxy....' )

						else :
							if self._daemon :
								# thread creation failed
								self._logger.error( '..thread creation failed...' )
								sys.exit( 1 )



			# attributes
			@property
			def ping_addr( self ) :
				return self._ping_addr
			@ping_addr.setter
			def ping_addr( self  , addr ) :
				self._ping_addr = addr
			@property
			def local_port(sself ) :
				return self._local_port
			@local_port.setter
			def local_port( self , port ) :
				self._local_port = port
			@property
			def dest_addr( self ) :
				return self._dest_addr
			@dest_addr.setter
			def dest_addr( self , addr ) :
				self._dest_addr = addr
			@property
			def dest_port( self ) :
				return self._dest_port
			@dest_port.setter
			def dest_port( self , port ) :
			    self._dest_port = port
			@property
			def daemon( self ) :
				return self._daemon
			@daemon.setter
			def daemon( self , da ):
				self._daemon = da
			@property
			def create_proxy( self ) :
				return self._create_proxy
			@create_proxy.setter
			def create_proxy( self , proxy ) :
				self._create_proxy = proxy
			@property
			def status_ok( self ) :
				return self._status_ok
			@property
			def ssh_path( self ) :
				return self._ssh_path
			@ssh_path.setter
			def ssh_path( self , path ) :
				self._ssh_path = path
			@property
			def ssh_user( self ) :
				return  self._ssh_user
			@ssh_user.setter
			def ssh_user( self  , user ) :
				self._ssh_user = user



# ------------------------------------------------------------------------------------
@click.command()
@click.argument( 'ping_server' )
@click.argument( 'local_port' )
@click.argument( 'destination_server' )
@click.argument( 'destination_port' )
@click.option( '--key_path' ,
			   default='/home/wiljoh/cci-develop.pem' ,
			   help ='full path to ssh private key' )
@click.option( '--daemon' ,
			   default=0 ,
			   help ='run process as background process' )
@click.option( '--create_proxy' ,
			   default=1 ,
			   help ='create http proxy' )
@click.option( '--user' ,
			   default='ubuntu' ,
			   help ='ssh user' )
def local_perform( moocher ) :
			"""

			:param moocher:
			:return:
			"""

			moocher.perform( ping_server ,
							 local_port ,
							 destination_server ,
							 destination_port ,
							 key_path ,
							 daemon ,
							 create_proxy ,
							 user )




# --------------------------------------------------------------------------------------
if __name__ == '__main__':




			try :

				# perform()
				cci = cci_http_tunnel_moocher()
				local_perform( cci )


			except OSError as e :
				_logger.error( e.message )







