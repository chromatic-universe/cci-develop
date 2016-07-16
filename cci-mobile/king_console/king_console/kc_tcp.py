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


##############
'''disable ipv6 console annoyance'''
logging.getLogger( "scapy.runtime" ).setLevel(logging.ERROR)
from scapy.all import *


# ---------------------------------------------------------------------------------------------
def syn_ack_scan( ip=None , port=80 ) :
			"""

			:param ip:
			:param port_range:
			:return:
			"""

			reply = None
			try :

				reply = sr1( IP( dst = ip )/ TCP( dport = int( port ) ,flags = 'S') , timeout=5 )
				if reply :
					print reply.display()

			except Exception  as e :
				print e.message
				sys.exit( 1 )

			return reply


# ------------------------------------------------------------------------------------
if __name__ == '__main__' :


			parser = argparse.ArgumentParser()
			parser.add_argument('-s', action='store', dest='syn_ip',
						help='single syn ip  value')
			parser.add_argument('-p', action='store', dest='syn_port',
						help='syn ack')

			args = parser.parse_args()

			if args.syn_ip and args.syn_port :

				syn_ack_scan( args.syn_ip , args.syn_port )

				sys.exit( 0 )



