from flask import Flask
import logging


app = Flask( __name__ , template_folder='./templates')
log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'


# logger
_logger = logging.getLogger( "cci-trinity-server-vulture" )
_logger.setLevel( logging.DEBUG )
fh = logging.FileHandler(  'cci-trinity-vulture.log' + '-debug.log', mode = 'a' )
fh.setLevel( logging.DEBUG )
formatter = logging.Formatter( log_format )
# console
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)
# formatter
ch.setFormatter(formatter)
fh.setFormatter( formatter )
_logger.addHandler( fh )
_logger.addHandler( ch )




class mongo_no_resource_exception( Exception ):
    pass
