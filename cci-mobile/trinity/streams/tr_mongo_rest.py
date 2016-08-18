# tr_mongo_rest.py    william k. johnson 2016


import os
import sys
from StringIO import StringIO
import logging
from math import ceil
from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response , jsonify , Blueprint
from flask_restful import Resource, Api
import subprocess as proc
import sqlite3
import time
import signal
import Queue
import doctest


from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response , current_app
from flask_pymongo import PyMongo
from flask_restful import Resource, Api

from flask_pymongo import PyMongo


from application import app , mongo_no_resource_ecxception

app.config['MONGO_DBNAME'] = 'cci_maelstrom'
app.config['MONGO_URI'] = 'mongodb://cci-aws-3:27017/cci_maelstrom'
mongo = PyMongo( app )

dev = Blueprint( 'dev', __name__, template_folder='templates' )



# --------------------------------------------------------------------------------------------------------
def api():
    """
    GET to generate a list of endpoints and their docstrings
    :return this document
    """
    urls = dict([(r.rule, current_app.view_functions.get(r.endpoint).func_doc)
                 for r in current_app.url_map.iter_rules()
                 if not r.rule.startswith('/static') and r.rule.startswith( '/mongo' )])
    return render_template( 'api.html' , urls=urls )
app.add_url_rule( '/mongo/api' ,
				  'api' ,
				  view_func=api ,
				  methods=['GET'] )




# --------------------------------------------------------------------------------------------------------
def enum_devices() :
			"""
			GET enumerate all devices
			:return : jsonified payload of devices
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
app.add_url_rule( '/mongo/enum_devices' ,
				  'enum_devices' ,
				  view_func=enum_devices ,
				  methods=['GET'] )



# --------------------------------------------------------------------------------------------------------
def retr_device( device_id ) :
			"""
			GET 	retrieve one device or 404 by id( mac address )
			:param : device_id
			:return : jsonified device payload
			:rtype: json
			"""


			output = []

			db =  mongo.db.auth_devices
			device = db.find( { 'device_id' : device_id } )
			if device.count() == 0 :
				raise mongo_no_resource_ecxception( 'no tokenized device found')
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

			return jsonify({'result' : output})
app.add_url_rule( '/mongo/retr_device/<device_id>' ,
				  'retr_device' ,
				  view_func=retr_device ,
				  methods=['GET'] )



# --------------------------------------------------------------------------------------------------------
def device_active( device_id ) :
			"""
			GET 	is device tagged active?
			:param device_id: string
			:return: : jsonified device payload
			:rtype: json
			"""
			output = []

			db =  mongo.db.auth_devices
			device = db.find_one_or_404( { 'device_id' : device_id } )
			output = { 'active' : device['active'] }


			return jsonify({'result' : output})
app.add_url_rule( '/mongo/device_active/<device_id>' ,
				  'device_active' ,
				  view_func=device_active ,
				  methods=['GET'] )



# --------------------------------------------------------------------------------------------------------
def retr_segment_devices( segment ) :
			"""
			GET 	retrieve devices by segment identifier
			:param segment: string
			:return: : jsonified device payload
			:rtype: json
			"""


			output = []
			try :
				db =  mongo.db.auth_devices
				for device in db.find( { 'segment' : segment } ) :
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
				 print e.message
			return jsonify({'result' : output})

app.add_url_rule( '/mongo/retr_segment_devices/<segment>' ,
				  'retr_segment_devices' ,
				  view_func=retr_segment_devices ,
				  methods=['GET'] )




# --------------------------------------------------------------------------------------------------------
def retr_devices_by_app( app ) :
			"""
			GET 	retrieve devices by application spec
			:param application moniker:
			:return: : jsonified device payload
			:rtype: json
			"""


			output = []
			try :
				db =  mongo.db.auth_devices
				for device in db.find( { 'app_tags' : app  } ) :
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
				 print e.message
			return jsonify({'result' : output})

app.add_url_rule( '/mongo/retr_devices_by_app/<app>' ,
				  'retr_devices_by_app' ,
				  view_func=retr_devices_by_app ,
				  methods=['GET'] )




# --------------------------------------------------------------------------------------------------------
def retr_auth_apps() :
			"""
			GET 	retrieve payload of authorized applications
			:param application moniker:
			:return: : jsonified device payload
			:rtype: json
			"""

			output = []
			db = mongo.db.auth_apps

			cur = db.find()
			if cur.count() == 0 :
				raise mongo_no_resource_ecxception( 'no authorized apps found' )
			for app in db.find() :
				output.append( { 'moniker' : app['moniker'] ,
							     'description' : app['description'] ,
								 'url' : app['url'] } )

			return jsonify( {'result' : output} )

app.add_url_rule( '/mongo/retr_auth_apps' ,
				  'retr_auth_apps' ,
				  view_func=retr_auth_apps ,
				  methods=['GET'] )
