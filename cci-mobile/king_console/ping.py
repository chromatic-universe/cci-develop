from scapy.all import *
import logging

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'

# ------------------------------------------------------------------------------------
if __name__ == '__main__' :

	log = logging.getLogger( "cci_maelstrom_command" )
	log.setLevel( logging.DEBUG )
	fh = logging.FileHandler(  'cci_maelstrom_command.log'  , mode = 'a' )
	fh.setLevel( logging.DEBUG )
	formatter = logging.Formatter( log_format )
	fh.setFormatter( formatter )
	log.addHandler( fh )

	ip = IP()
	ip.dst = '192.168.0.135'

	ping = ICMP()
	ping_request = ( ip/ping )

	ping_reply = sr1( ping_request , timeout = 1 )
	print  '<request>'
	print ping_request.display()

	if ping_reply :
		log.info( ping_reply.summary() )
		print '<reply>'
		print ping_reply.display()
		print 'ping suceeded....'
	else :
		log.error( 'ping failed....' )
		print 'ping_failed'

cd