# trinity_cpp.py    william k johnson copyright chromatic universe 2016


import os
import sys
import json

from pymongo import MongoClient
from bson.objectid import ObjectId


const_file_name = 'instance_id'

# mongo object id brain damage
class json_encoder( json.JSONEncoder ) :

    def default( self , o ) :
        if isinstance( o , ObjectId ) :
            return str( o )
        return json.JSONEncoder.default( self , o )


#----------------------------------------------------------------------------
def retr_instance_atoms( inst ) :
		"""

		:return tuple:
		"""

		try :

			with open( const_file_name , 'r' ) as data :
				return tuple( data.readline().strip().split( ':' ) )

		except Exception as e:
			print e.message
			sys.exit( 1 )


#----------------------------------------------------------------------------
def retr_mongo_metadata() :
		"""

		:return json dumps:
		"""

		try :

			ip , id = retr_instance_atoms( const_file_name )

			mc = MongoClient( ip )

			db = mc['cci_maelstrom']
			cursor = db['auth_http_servers'].find( {"_id" : ObjectId( id ) } )
			for document in cursor :
				j = json_encoder().encode( document )
				print j

		except Exception as e:
			print e.message
			sys.exit( 1 )




# ------------------------------------------------------------------------------
if __name__ == "__main__" :

			retr_mongo_metadata()

			sys.exit( 0 )







