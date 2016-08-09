import sys
from sseclient import SSEClient


messages = SSEClient('http://localhost:7080/stream')
try :
	for msg in messages:
		print 'this server msg #%s' % msg
		if int( msg.data ) > 15 :
			sys.exit( 0 )
except :
	pass

