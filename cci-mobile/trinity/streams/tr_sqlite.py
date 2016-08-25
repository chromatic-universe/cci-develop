# tr_sqlitet.py    william k. johnson 2016


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

import flask
from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response , current_app , jsonify , Blueprint
from flask_pymongo import PyMongo
from flask_restful import Resource, Api

try:  # python 2
    from urllib import urlencode
except ImportError:  # python 3
    from urllib.parse import urlencode


from application import app , _logger


# cci
import tr_utils


# -----------------------------------------------------------------------------
def query_session() :
			_logger.info( '...query_session...' )
			id=request.form['session_id']

			return redirect( url_for( 'session_call_history' ,
									  device = '"' + tr_utils.local_mac_addr() + '"' ,
									  session_id = '"' + id + '"' ) )

app.add_url_rule( '/query_session/' ,
				  'query_session' ,
				  view_func=query_session ,
				  methods=['GET' , 'POST'] )




# ----------------------------------------------------------------------------------------------------
def session_call_reprise(  session_id , max_id , total_count , record_ptr )  :
			"""

			:param session_id:
			:param record_ptr:
			:return:
			"""
			_logger.info( '...session_call_reprise...' )
			con = sqlite3.connect( "/data/media/com.chromaticuniverse.cci_trinity/king_console.sqlite" )
			con.row_factory = sqlite3.Row

			cur = con.cursor()
			cur.execute( "select * from session_call_history where session_name = %s" \
				         " and idx < %d " \
						 "order by timestamp DESC " \
						 "LIMIT %d" % ( session_id , int(max_id) - 15 , 15 ) )
			rows = cur.fetchall()

			return render_template( "list.html",
									rows = rows ,
									session_id = session_id ,
									total_count = total_count ,
									record_ptr = int( record_ptr ) + 15 ,
									max_id = int(max_id) - 15 )

app.add_url_rule( '/session_call_reprise/<session_id>/batch/<max_id>:<total_count>:<record_ptr>' ,
				  'session_call_reprise' ,
				  view_func=session_call_reprise ,
				  methods=['GET'] )





# ----------------------------------------------------------------------------------------------------
def session_call_history(  device , session_id )  :
			   """

			  :return:

			   """

			   _logger.info( '...aession_call_history...' )
			   con = sqlite3.connect( "/data/media/com.chromaticuniverse.cci_trinity/king_console.sqlite" )
			   con.row_factory = sqlite3.Row

			   cur = con.cursor()
			   if session_id is not None :
					cur.execute( 'select count(*) as count , max( session_call_history.idx ) as ' \
								 'max_idx  from sessions  session_call_history '
								 'inner join  sessions on session_call_history.session_name = sessions.session_name '
								 'where sessions.session_name = %s and sessions.device_id = %s'	 % ( session_id , device ) )
					rows = cur.fetchone()
					if rows is not None :
						count = rows[0]
						max_idx = rows[1]
						cur.execute( 'select * from session_call_history  ' \
									 'inner join  sessions on session_call_history.session_name = sessions.session_name '
									 'where sessions.session_name = %s and sessions.device_id = %s ' \
									 'order by session_call_history.timestamp DESC ' \
									 'LIMIT %d' % ( session_id , device , 15 ) )


						rows = cur.fetchall()
						return render_template( "list.html" ,
											rows = rows ,
											session_id = session_id ,
											total_count = count ,
											record_ptr = len( rows ) ,
											max_id = max_idx )

			   else :
					# grab newest session marked as active
					cur.execute( 	'select  max(session_call_history.idx)  as max_id  , session_call_history.session_name ' \
									'from session_call_history ' \
									'inner join  sessions on session_call_history.session_name = sessions.session_name ' \
									'where sessions.status = 1 and sessions.device_id = %s ' \
									'group by session_call_history.session_name ' \
									'order by session_call_history.timestamp desc ' \
									'limit 1'  % device )

					rows = cur.fetchone()
					if rows is not None :
						max_idx = rows[0]
						session_id = rows[1]

						cur.execute(   'select session_call_history.idx  , session_call_history.session_name ,' \
									   'session_call_history.call_segment , ' \
									   'session_call_history.call_moniker , session_call_history.call_params , ' \
									   'session_call_history.timestamp , sessions.device_id from session_call_history '\
									   'inner join  sessions on session_call_history.session_name = sessions.session_name ' \
									   'where session_call_history.session_name = "%s" '  \
									   'order by session_call_history.timestamp desc '  % session_id )

						rows = cur.fetchall()
						return render_template( "list.html" ,
												rows = rows ,
												session_id = '"' + session_id + '"' ,
												total_count = len( rows ) ,
												record_ptr = len( rows ) ,
												max_id = max_idx )

					return render_template( "index.html" ,
										message = 'no current sessions' )

app.add_url_rule( '/session_call_history/<device>' ,
				  'session_call_history' ,
				  defaults={'session_id': None} ,
				  view_func=session_call_history ,
				  methods=['GET'] )
app.add_url_rule( '/session_call_history/<device>/<session_id>' ,
				  'session_call_history' ,
				  view_func=session_call_history ,
				  methods=['GET'] )



