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
def quick_wireless_sniff() :
			"""

			:return:
			"""
			try :

				ret = sniff(iface="wlan0",prn=lambda x:x.sprintf("{Dot11Beacon:%Dot11.addr3%\t%Dot11Beacon.info%\t%PrismHeader.channel%\tDot11Beacon.cap%}"))

			except Exception as e :
				print e.message




# ------------------------------------------------------------------------------------
if __name__ == '__main__' :

			quick_wireless_sniff()




