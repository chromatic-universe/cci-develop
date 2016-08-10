# tr_kafka.py    william k. johnson 2016


import os
import sys
from StringIO import StringIO
import logging
from math import ceil
from flask import Flask , request , send_file , render_template , url_for
from flask import redirect , Response
from flask_restful import Resource, Api
import subprocess as proc
import sqlite3
import time
import signal
import Queue

import kafka



# -----------------------------------------------------------------------------------
class tr_kafka_stream( object ) :

				"""
				tr_kafka_stream
				"""

				def __init__( self ,
							  default_bootstrep ,
							  logger = None )  :

						"""

						:param default_db:
						:param logger:
						:return:
						"""


						if logger is None :
							raise Exception( 'no logging instance specified...' )
						self.logger = logger

						self.logger.info( '...kf_kafka_stream initialized...' )



				def __del__(self) :
						"""

						:return:
						"""

						pass




# -----------------------------------------------------------------------------------
class kafka_metadata( Resource ) :
				"""
				metadata
				"""

				def get ( self , todo_id ):
					return {todo_id: todos[todo_id]}

				def put(self, todo_id):
					todos[todo_id] = request.form['data']
					return {todo_id: todos[todo_id]}

				api.add_resource(TodoSimple, '/<string:todo_id>')
