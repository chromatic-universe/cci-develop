
# cci-trinity.py    william k. johnson  2016



from StringIO import StringIO
import logging
from math import ceil
from flask import Flask , request , send_file , render_template
from flask import redirect
import subprocess as proc
import sqlite3


#cci
import trinity

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'

app = Flask(__name__)


# logger
_logger = logging.getLogger( "cci-trinity-server" )
_logger.setLevel( logging.DEBUG )
fh = logging.FileHandler(  'cci-trinity-server.log' + '-debug.log', mode = 'a' )
fh.setLevel( logging.DEBUG )
formatter = logging.Formatter( log_format )
fh.setFormatter( formatter )
_logger.addHandler( fh )


const_per_page = 20


# -----------------------------------------------------------------------------------
def local_mac_addr() :
		"""

		:return mac string:
		"""

		try :
			return proc.check_output( ['cat' , '/sys/class/net/wlan0/address'] ).strip()
		except :
			pass


# ------------------------------------------------------------------------------
@app.route('/index')
@app.route( "/" )
def index():

    		return render_template( "index.html" ,
									device = '"' + local_mac_addr() + '"' )



# ------------------------------------------------------------------------------
@app.route( "/trinity" )
def cci_trinity():

			out = 'cci_trinity capture screen...'
			io = StringIO()
			try :

				b_ret , out = trinity.capture_screen( _logger )
				if not b_ret :
					_logger.error( out )
				else :
					io.write( out )
					io.seek( 0 )


			except Exception as e :
				out =  'error in cci_trinity.....'  + e.message
				_logger.error( out )
				return

			return send_file( io , mimetype='image/png' )





# ------------------------------------------------------------------------
@app.route('/click')
def click() :
			"""

			:return:
			"""

			return trinity.capture_clicks( log = _logger ,
										   request = request )




@app.route( "/session_call_reprise/<session_id>/batch/<max_id>:<total_count>:<record_ptr>" )
def session_call_reprise(  session_id , max_id , total_count , record_ptr )  :
			"""

			:param session_id:
			:param record_ptr:
			:return:
			"""

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




@app.route( "/session_call_history/<device>" , defaults={'session_id': None})
@app.route( "/session_call_history/<device>/<session_id>" )
def session_call_history(  device , session_id )  :
			   """

			  :return:

			   """


			   con = sqlite3.connect( "/data/media/com.chromaticuniverse.cci_trinity/king_console.sqlite" )
			   con.row_factory = sqlite3.Row

			   cur = con.cursor()
			   if session_id is not None :
					cur.execute( 'select count(*) as count , max( session_call_history.idx ) as ' \
								 'max_idx  from sessions  session_call_history '
								 'inner join  sessions on session_call_history.session_name = sessions.session_name '
								 'where sessions.session_name = %s and sessions.device_id = %s'	 % ( session_id , device ) )
					rows = cur.fetchone()
					count = rows[0]
					max_idx = rows[1]
					cur.execute( 'select * from session_call_history  ' \
						         'inner join  sessions on session_call_history.session_name = sessions.session_name '
								 'where sessions.session_name = %s and sessions.device_id = %s ' \
								 'order by session_call_history.timestamp DESC ' \
								 'LIMIT %d' % ( session_id , device , 15 ) )


					rows = cur.fetchall()

			   else :
					cur.execute( 'select count(session_call_history.idx) as count , max( session_call_history.idx ) as max_idx from session_call_history '
								 'inner join  sessions on session_call_history.session_name = sessions.session_name ' \
								 'where sessions.status = 1 and sessions.device_id = %s '  % device )

			   		rows = cur.fetchone()
					count = rows[0]
					max_idx = rows[1]
					cur.execute(   'select session_call_history.idx  , session_call_history.session_name ,' \
								   'session_call_history.call_segment , ' \
								   'session_call_history.call_moniker , session_call_history.call_params , ' \
								   'session_call_history.timestamp , sessions.device_id from session_call_history '\
								   'inner join  sessions on session_call_history.session_name = sessions.session_name ' \
								   'where sessions.status = 1 and sessions.device_id = %s ' \
								   'order by session_call_history.timestamp desc ' \
								   'limit 15' % device )
					rows = cur.fetchall()
			   return render_template( "list.html" ,
									    rows = rows ,
									    session_id = 'current' ,
										total_count = count ,
										record_ptr = len( rows ) ,
										max_id = max_idx )








# ------------------------------------------------------------------------------
if __name__ == "__main__" :
			_logger.info( '....cci_trinity...' )
			try :
				app.run( host= '0.0.0.0' , port=7080, debug=True  )
			except Exception as e:
				_logger.error( '...error in  trinity server...' + e.message )




