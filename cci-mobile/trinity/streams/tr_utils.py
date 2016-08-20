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
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return base64.b64encode( proc.check_output( ['cat' ,
														 '/sys/class/net/wlan0/address'] ).strip() )
		except :
			pass

