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
					   ".-O" ,
					   '-v' ,
					   ip
					  ]

				try :
					out = proc.check_output( cmd  )
				except proc.CalledProcessError as e :
					b_ret = False
			except Exception as e :
				b_ret = False
				raise Exception(  'quicl fingerprint...' + e.message )


			return out


