# tr_kafka_ext_stream.py   william k. johnson 2016

# py standard
import os
import sys
import logging
import signal


# cci
import cci_rdkafka_py as rdkafka
import _cci_rdkafka_py

log_format = '%(asctime)s.%(msecs)s:%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'


# logger
logger = logging.getLogger( "cci_kafka_ext" )
logger.setLevel( logging.DEBUG )
# create file handler strange file extension
fh = logging.FileHandler(  'cci_kafka_ext.log' , mode = 'w' )
fh.setLevel( logging.DEBUG )

# create console handler
ch = logging.StreamHandler()
ch.setLevel( logging.DEBUG )

# create formatter and add it to the handlersuntitled
formatter = logging.Formatter( log_format )
fh.setFormatter( formatter )
ch.setFormatter( formatter )

# add the handlers to the self._logger
logger.addHandler( fh )
logger.addHandler( ch )

gkc = None


def deactivate( sig ) :

		if gkc :
			logger.warning('...deactivating rdkafka...' )
			# kill fgetc
			sys.stdin.close()
			# halt kafka
			kc.is_running = 0



def sig_handler( sig , frame ) :
		"""

		:param sig:
		:param frame:
		:return:
		"""
		logger.warning('...caught signal: %s', sig )

		deactivate( sig )



# ------------------------------------------------------------------------------
if __name__ == "__main__"  :


		# signal handlers
		signal.signal( signal.SIGTERM, sig_handler )
		signal.signal( signal.SIGINT, sig_handler )

		try :

			logger.info( '...cci_kafka_ext...rdkafka c api interface..' )
			kc = rdkafka.kafka_context()
			kc.topic_str = 'king-console-cci-maelstrom'
			logger.info( '...topic is %s' % kc.topic_str )

			kc.brokers = 'cci-aws-1:9092'
			logger.info( '...brokers => %s' % kc.brokers )

			kc.group_id = 'cci-group'
			logger.info( '...group => %s' % kc.group_id )

			kc.partitions_ptr = None
			# RD_KAFKA_PARTITION_UA ,
			kc.partition = 0
			kc.debug_flags = None
			kc.dump_config = 1
			kc.is_running = 0
			kc.exit_eof = 0
			kc.wait_eof = 0
			# kc.start_offset = 0
			kc.mode = 0
			kc.argc = len( sys.argv )


			gkc = kc

			# handlers
			#logger.info( '...ex_parte_producer...' )
			#rdkafka.ex_parte_producer( kc )

			logger.info( '...ex_parte_consumer...' )
			rdkafka.ex_parte_consumer( kc )



		except Exception as e :
			logger.error( e.message )
