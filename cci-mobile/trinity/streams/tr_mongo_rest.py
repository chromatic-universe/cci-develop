# tr_mongo_rest.py    william k. johnson 2016


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
import json
from bson import json_util

import flask
from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response , current_app , jsonify , Blueprint
from flask_pymongo import PyMongo
from flask_restful import Resource, Api
from flask_pymongo import PyMongo
try:  # python 2
    from urllib import urlencode
except ImportError:  # python 3
    from urllib.parse import urlencode


from application import app , mongo_no_resource_exception

app.config['MONGO_DBNAME'] = 'cci_maelstrom'
app.config['MONGO_URI'] = 'mongodb://cci-aws-3:27017/cci_maelstrom'
mongo = PyMongo( app )




# --------------------------------------------------------------------------------------------------------
def cci_api():
			"""
			GET to generate a list of endpoints and their docstrings
			:return this document
			"""

			try :
				urls = dict([(r.rule, current_app.view_functions.get(r.endpoint).func_doc)
							 for r in current_app.url_map.iter_rules()
							 if not r.rule.startswith('/static') and r.rule.startswith( '/mongo' )])
			except Exception as e :
				raise mongo_no_resource_exception( e.message )

			return render_template( 'api.html' , urls=urls )




app.add_url_rule( '/mongo/cci_api' ,
				  'cci_api' ,
				  view_func=cci_api ,
				  methods=['GET'] )




# --------------------------------------------------------------------------------------------------------
def enum_devices() :
			"""	GET enumerate all devices:return : jsonified payload of devices"""
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
				 print e.message
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
				raise mongo_no_resource_exception( 'no tokenized device found')
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
				raise mongo_no_resource_exception( 'no authorized apps found' )
			for app in db.find() :
				output.append( { 'moniker' : app['moniker'] ,
							     'description' : app['description'] ,
								 'url' : app['url'] } )

			return jsonify( {'result' : output} )

app.add_url_rule( '/mongo/retr_auth_apps' ,
				  'retr_auth_apps' ,
				  view_func=retr_auth_apps ,
				  methods=['GET'] )




# --------------------------------------------------------------------------------------------------------
def update_device_status( device_id , status ) :
			"""
			PUT update device status
			:param device_id : string
			:param status : csv <active,last_ip,last_remote_ip>  true,192.168.0.1,64.0.1.19
			:return : jsonified payload of devices
			"""
			output = []
			active , last , last_remote = status.split( ',' )

			db =  mongo.db.auth_devices

			print device_id


			result = mongo.db.auth_devices.update_one (
									{"device_id": device_id } ,
										{
											"$set":
											{
												"active" : active ,
												"last_known_ip" : last ,
												"last_known_remote_ip" : last_remote
											},
											"$currentDate": { "last_active" : True }

										} )

			print result
			if result.matched_count == 0 :
				raise mongo_no_resource_exception( 'could not update device document' )

			return jsonify({'result' : 'ok'})

app.add_url_rule( '/mongo/update_device_status/<device_id>/<status>',
				  'update_device_status' ,
				  view_func=update_device_status
				   )




# --------------------------------------------------------------------------------------------------------
def insert_atomic_payload() :
			"""
			POST insert json payload
			:param payload:
			:return:
			"""

			output = []
			db = mongo.db.runtime_payload_atoms
			insert_data = json.loads( request.data )

			ack = db.insert( insert_data )
			if not ack :
				raise mongo_no_resource_exception( 'db payload insert failed' )

			return jsonify({'result' : 'ok'})



app.add_url_rule( '/mongo/insert_atomic_payload',
				  'insert_atomic_payload' ,
				  view_func=insert_atomic_payload ,
				  methods = ['POST']

				   )



# --------------------------------------------------------------------------------------------------------
def insert_beaucoup_payload() :
			"""
			POST insert many json payload , serialization hijinks involved , could affect performance
			:param payload:
			:return:
			"""

			db = mongo.db.runtime_payload_atoms
			if request.method == 'POST' :
				# split the string to a list , each entry is a dictionary
				dictionary_string_list = request.data.split( ',' )
				#make a list of actual dictionaries using json loads
				dictionary_list = list()
				for item  in dictionary_string_list :
					dictionary_list.append( json.loads( item ) )

				# bulk insert . mogndb will stage atoms internally
				ack = db.insert_many( dictionary_list )
				if not ack :
					raise mongo_no_resource_exception( 'db payload beaucoup insert failed' )
				return jsonify({'result' : 'ok'})

			return jsonify({'result' : 'bad post'})

app.add_url_rule( '/mongo/insert_beaucoup_payload',
				  ' insert_beaucoup_payload' ,
				  view_func= insert_beaucoup_payload ,
				  methods = ['POST']

				   )





# --------------------------------------------------------------------------------------------------------
def dry_atomic_payload_insert() :
			"""

			:return:
			"""
			t =  datetime.datetime.utcnow()
			data ={
					"timestamp" : "2016-08-19 18:11:41.111229" ,
					"app_moniker" : "cci_maelstrom",
					"app_segment" : "network",
					"segment_atom" : "ping_ip_input",
					"segment_atom_params" : "(ip=192.168.0.133)",
					"app_context" : "level1",
					"app_session" : "c62035ff-bcde-4ed2-bd6b-ab3072784dc",
					"segment_tag" : "0",
					"segment_atom_tag" : "1",
					"segment_atom_payload" : "the original corny snaps",
					"payload_id" : "c62035ff-bcde-4ed2-bd6b-ab3072784dcb",
					"description" : "atomic runtime device payload",
					"url" : "http://www.chromaticuniverse.xyz",
					"app_tags" : [
						"payload",
						"streams",
						"network",
						"icmp"
					],
					"canonical_owner" : "supreme_panjandrum",
					"scope" : "diaspora",
					"enlisted" : "2016-07-26 23:14:23"
				}
			r = requests.post( 'http://localhost:7080/mongo/insert_atomic_payload', data = json.dumps(data) )
			print r




if __name__ == '__main__' :

			dry_atomic_payload_insert()
