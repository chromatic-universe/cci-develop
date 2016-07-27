
# cci-trinity.py    william k. johnson  2016



from StringIO import StringIO
import logging
from flask import Flask , request , send_file , render_template
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


# ------------------------------------------------------------------------------
@app.route( "/" )
def index():
    		return 'chromatic universe ~ cci-trinity  c. william k. johnson 2016'



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



@app.route('/session_call_history')
def session_call_history() :
			   """

			  :return:

			   """

			   con = sqlite3.connect( "king_console.sqlite" )
			   con.row_factory = sqlite3.Row

			   cur = con.cursor()
			   cur.execute( "select * from session_call_history" )

			   rows = cur.fetchall();


			   return render_template("list.html",rows = rows)

# ------------------------------------------------------------------------------
if __name__ == "__main__" :
			_logger.info( '....cci_trinity...' )
			try :
				app.run( host= '0.0.0.0' , port=7080, debug=True  )
			except Exception as e:
				_logger.error( '...error in  trinity server...' + e.message )




