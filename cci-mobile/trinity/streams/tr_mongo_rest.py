# tr_mongo_rest.py    william k. johnson 2016


import os
import sys
from StringIO import StringIO
import logging
from math import ceil
from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response , jsonify
from flask_restful import Resource, Api
import subprocess as proc
import sqlite3
import time
import signal
import Queue


from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response
from flask_pymongo import PyMongo
from flask_restful import Resource, Api

from flask_pymongo import PyMongo


from application import app
app.config['MONGO_DBNAME'] = 'cci_maelstrom'
app.config['MONGO_URI'] = 'mongodb://cci-aws-3:27017/cci_maelstrom'
mongo = PyMongo( app )


# --------------------------------------------------------------------------------------------------------
def enum_devices() :
			"""

			:return:
			"""
			output = []
			try :
				db =  mongo.db.auth_devices
				for device in db.find() :
					output.append({'moniker' : device['moniker'] ,
								   'description' : device['description'] ,
								   'active' : device['active'] ,
								   'device_id' : device['device_id'] ,
								   'enlisted' : device['enlisted'] ,
								   'last_kown_remote_ip' : device['last_known_remote_ip'] ,
								   'engaged' : device['engaged'] ,
								   'canononical_user' : device['canonical_user'] ,
								   'scope' : device['scope'] ,
								   'segment' : device['segment']
					})
			except Exception as e :
				 pass
			return jsonify({'result' : output})
app.add_url_rule( '/mongo/enum_devices' , 'enum_devices' , view_func=enum_devices , methods=['GET'] )






# --------------------------------------------------------------------------------------------------------
def retr_device( device_id ) :
			"""

			:param device_id:
			:return:
			"""


			output = []
			try :
				db =  mongo.db.auth_devices
				device = db.find_one( { 'device_id' : device_id } )
				output =  {'moniker' : device['moniker'] ,
						   'description' : device['description'] ,
						   'active' : device['active'] ,
						   'device_id' : device['device_id'] ,
						   'enlisted' : device['enlisted'] ,
						   'last_kown_remote_ip' : device['last_known_remote_ip'] ,
						   'engaged' : device['engaged'] ,
						   'canononical_user' : device['canonical_user'] ,
						   'scope' : device['scope'] ,
						   'segment' : device['segment']
						  }

			except Exception as e :
				 print e.message
			return jsonify({'result' : output})
app.add_url_rule( '/mongo/retr_device/<device_id>' , 'retr_device' , view_func=retr_device , methods=['GET'] )
