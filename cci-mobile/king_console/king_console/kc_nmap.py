# kc_tcp.py   william k. johnson 2016


log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'

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


firewalk_params = { 'max_retries' : 'firewalk.max-retries=%d' ,
					'probe_timeout' : 'firewalk.probe-timeout=%d' ,
					'recv_timeout' : 'firewalk.recv-timeout=%d' ,
					'max_ports' : 'firewalk.max-probed-ports=%d' }



# ---------------------------------------------------------------------------------------------
def quick_fingerprint( ip = None ) :
			"""

			:param ip:
			:return:
			"""

			if ip is None :
				raise Exception( 'no ip supplied' )

			out = str()
			boiler = str()
			b_ret = True
			try :


				cmd = ["su" ,
					   "-c" ,
					   "/system/bin/nmap" ,
					   "-O" ,
					   '-v' ,
					   ip
					  ]

				try :
					out = proc.check_output( cmd  )
				except proc.CalledProcessError as e :
					b_ret = False
			except Exception as e :
				b_ret = False
				raise Exception(  'quick fingerprint...' + e.message )


			return b_ret , out



# ---------------------------------------------------------------------------------------------
def fat_fingerprint( ip = None ) :
			"""

			:param ip:
			:return:
			"""

			if ip is None :
				raise Exception( 'no ip supplied' )

			out = str()
			boiler = str()
			b_ret = True
			try :


				cmd = ["su" ,
					   "-c" ,
					   "/system/bin/nmap" ,
					   "-p0" ,
					   '-v' ,
					   '-A' ,
					   '-T4' ,
					   ip
					  ]

				try :
					out = proc.check_output( cmd  )
				except proc.CalledProcessError as e :
					b_ret = False
			except Exception as e :
				b_ret = False
				raise Exception(  'quick fingerprint...' + e.message )


			return b_ret , out



# ---------------------------------------------------------------------------------------------
def ping_ip_subnet( ip = None ) :
			"""

			:param ip:
			:return:
			"""

			if ip is None :
				raise Exception( 'no ip supplied' )

			out = str()
			boiler = str()
			b_ret = True
			try :


				cmd = ["su" ,
					   "-c" ,
					   "/system/bin/nmap" ,
					   "-n" ,
					   '-sP',
					   ip
					  ]

				try :
					out = proc.check_output( cmd  )
				except proc.CalledProcessError as e :
					b_ret = False
					out = e.message
			except Exception as e :
				b_ret = False
				raise Exception(  'quick fingerprint...' + e.message )


			return b_ret , out




# ---------------------------------------------------------------------------------------------
def mongo_extended_metadata( ip = None ) :
			"""

			:param ip:
			:return exntended info:
			"""


			if ip is None :
				raise ValueError( 'no ip supplied' )


			cmd = [
				    "su" ,
					"-c" ,
					"/system/bin/nmap" ,
					"-p" ,
					"27017" ,
			        "--script",
					"mongodb-info" ,
					ip
				 ]
			return spawn_nmap_output(  cmd , 'mongo_extended_metadata' )




# ---------------------------------------------------------------------------------------------
def firewalk( ip = None ,
			  max_retries = 1 ,
			  probe_timeout = 400 ,
			  recv_timeout = 400 ,
			  max_ports = 7 )  :
			"""
			:param ip:
			:param max_retries:
			:param probe_timeout:
			:param nax_ports:
			:return:
			"""


			if ip is None :
				raise ValueError( 'no ip supplied' )

			out = str()
			boiler = str()
			b_ret = True

			s = '--script-args=' + firewalk_params['max_retries'] % max_retries  + ','\
			                     + firewalk_params['probe_timeout'] % probe_timeout  + ','  \
								 + firewalk_params['recv_timeout'] % recv_timeout  + ','  \
			                     + firewalk_params['max_ports'] % max_ports
			cmd = ['nmap' ,
				   '--script=firewalk' ,
				   '--traceroute' ,
				   s ,
				   ip
				   ]


			return spawn_nmap_output(  cmd , 'firewalk' )




# ---------------------------------------------------------------------------------------------
def spawn_nmap_output( cmdline = None , moniker = 'nmap' ) :
			"""

			:param cmdline:
			:return output:
			"""

			if cmdline is None :
				raise Exception( '..spawn_nmap_output...no cmdline supplied' )

			out = str()
			boiler = str()
			b_ret = True
			try :

				try :
					out = proc.check_output( cmdline  )
				except proc.CalledProcessError as e :
					b_ret = False
					out = e.message
			except Exception as e :
				b_ret = False
				raise Exception(  moniker + ' '  + e.message )


			return b_ret , out




# ------------------------------------------------------------------------------------
if __name__ == '__main__' :

			#b_ret , out = mongo_extended_metadata( 'cci-aws-3'  )

			b_ret , out = firewalk( ip = 'cci-aws-1' , max_ports = 7 )

			print out