# trutils.py    william k. johnson 2016


import os
import sys
from StringIO import StringIO
import logging
from math import ceil

import subprocess as proc
import sqlite3
import time
import signal
import Queue
import requests
import datetime
import base64
import json
from bson import json_util



# -----------------------------------------------------------------------------------
def dict_factory( cursor, row)  :
    d = {}
    for idx , col in enumerate( cursor . description ) :
        d[col[0]] = row[idx]
    return d



# -----------------------------------------------------------------------------------
def quoted( s ) :
	return '"' +  s  + '"'



# -----------------------------------------------------------------------------------
def quoted_list_to_tuple( lst ) :
	return tuple( [quoted( x ) for x in lst] )


# -----------------------------------------------------------------------------------
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return base64.b64encode( proc.check_output( ['cat' ,
														 '/sys/class/net/wlan0/address'] ).strip() )
		except :
			pass

