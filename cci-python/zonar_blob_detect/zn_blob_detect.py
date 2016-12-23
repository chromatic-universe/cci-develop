# william k, johnson  chromatic universe 2016


import os
import sys
import logging
import argparse



# constant
const_log_format = '%(asctime)s.%(name)s:%(thread)d:%(levelname)s:%(process)d:%(message)s'
zn_atoms = { 'X' : 0 , 'O' : 0 }
zn_tokens = ['x' , 'o']

max_dimension = 250


# ------------------------------------------------------------------------
def init_logging( moniker = 'zonar_blob_detect' , fmt = const_log_format ) :

			"""
			initialize application logging
			:param logger:
			:param moniker:
			:param fmt:
			:return logger :
			"""

			logger = logging.getLogger( moniker )

			# setup logging

			# create logger
			logger.setLevel( logging.DEBUG )
			# create file handler strange file extension
			# tells python logging module to overwrite file
			fh = logging.FileHandler( moniker + '-debug.log', mode = 'w' )
			fh.setLevel( logging.DEBUG )

			# create console handler
			ch = logging.StreamHandler()
			ch.setLevel( logging.DEBUG )

			# create formatter and add it to the handlersuntitled
			formatter = logging.Formatter( fmt )
			fh.setFormatter( formatter )
			ch.setFormatter( formatter )

			# add the handlers to the self._logger
			logger.addHandler( fh )
			logger.addHandler( ch )

			return logger




# ------------------------------------------------------------------------------
class zn_blob_detector( object ) :


			# object model
			def __init__( self ,
                      	  target_file = None ,
                      	  pre_validate = False ,
						  dimension_max = max_dimension ) :
				"""
				init

				:param target_server: string
				:param pre_validate: bool
				:return:
				"""


				# logging
				self._logger = init_logging( self.__class__.__name__ )
				self._logger.info( self.__class__.__name__ + '...william k. johnson...c. zonar 2016')
				self._target = target_file
				self._validate = pre_validate
				self._dim_x = 0
				self._dim_y = 0
				self._validated = False
				self._dimension_max = dimension_max
				self._current_blob_count = 0

				self._rows = None
				self._cols = None
				self._matrix = None
				self._visitor_matrix = None
				self._blob_dictionary = dict()
				self._show_atom_as_blob = False

				if pre_validate :
					self.validate( self._target )



			def __repr__( self ) :
				 """
				 returns string representation and construction info
				 :rtype : basestring
				 :return:
				 """
				 return "{__class__.__name__}(target_file={_target!r},validate={_validate!r} ," \
						"dimension_max={_dimension_max!r})". \
						format( __class__=self.__class__ , **self.__dict__ )



			def __str__( self ) :
				  """
				  returns pretty string
				  :rtype: basestring
				  :return: str
				  """
				  return 'zn_blob_detector , 2016 , william k. johnson'



			# attributes
			@property
			def target_file( self ) :
				return self._target
			@target_file.setter
			def target_file( self , target ) :
				self._target = target
			@property
			def pre_validate( self ) :
				return self._validate
			@pre_validate.setter
			def pre_validate( self , val ) :
				self._validate = val
			@property
			def validated( self ) :
				return self._validated
			@property
			def logger( self ) :
				return self._logger
			@logger.setter
			def logger( self , log ) :
				self._logger = log
			@property
			def logger( self ) :
				return self._logger
			@logger.setter
			def logger( self , log ) :
				self._logger = log


			# helpers
			@staticmethod
			def _remove_whitespace( source , log , dim ) :
				"""

				:param source:
				:return s : string:
				"""


				s = source.lower()
				s = s.translate( s.maketrans( {' ' : None} ) )

				# out of bounds x
				if len( s ) >  dim :
					log.error( '...column count out bounds....' )
					return False , s , len( s.strip() )

				return True , s , len( s.strip() )


			# services
			def perform( self ) :
				"""

				:return:
				"""

				self._logger.info( '...perform...' )
				if not self._validated :
					self._logger.info( '...performing validation on source=>%s...' % self._target )
					self._validated , self._dim_x , self._dim_y = self.validate( self._target )
					if self._validated :
						self._logger.info( '...source=>%s is a blob detector file...' % self._target )
					else :
						self._logger.error(  '...source=>%s is a not a blob detector file...aborting' % self._target )
						return

				self._logger.info( '...performing detection on source=>%s...' % self._target  )
				self._current_blob_count = 0
				self._zn_bfs( 'x' )
				self._current_blob_count = 0
				self._zn_bfs( 'o' )



			def validate( self , validation_file  ) :
				"""
				validate and prepare

				:param validation_file: string
				:return: boolean
				"""

				self._logger.info( '...validate and prepare...' )
				# we have a small file by dim constant , so read it all into memory
				lines = None
				dim_x = 0
				b_ret = False
				s = str()

				self._validated = False
				self._rows = None
				self._cols = None
				self._matrix = None
				self._visitor_matrix = None
				row = 0
				col = 0

				try :
					with open( validation_file , 'r'  ) as vf :
						lines = vf.readlines()
						# out of bounds y
						if len( lines ) > max_dimension :
							self._logger.error( '...row count out of bounds....' )
							return self._validated , dim_x , len( lines )
						if self._rows is None :
							self._rows = len( lines )
						for line in lines :
							# remove whitespace
							b_ret , s , x_dim = zn_blob_detector._remove_whitespace( line , self._logger , self._dimension_max  )
							if self._cols is None :
								self._cols = len( s.strip( '\n' ) )
							if not b_ret :
								self._logger.error( '...column count out of bounds....' )
								return self._validated , dim_x , len( lines )
							#out of bounds x
							if dim_x != 0 :
								if dim_x != x_dim :
									# unbalanced
									self._logger.error( '...column count out of bounds....' )
									return self._validated , dim_x , len( lines )
							dim_x = x_dim
							# populate matrix
							if self._matrix is None :
								self._matrix = [[0 for x in range( self._cols )] for y in range( self._rows )]
								self._visitor_matrix = [[0 for x in range( self._cols )] for y in range( self._rows )]
							l = s.strip( '\n' )
							for idx , token in enumerate( l ) :
								if token not in zn_tokens :
									# illegal token
									self._logger.error( '...illegal token => "%s" at line %d...aborting....' % ( token , ( row + 1 ) ) )
									return self._validated , dim_x , len( lines )
								self._matrix[row][idx] = token

							row += 1


					self._validated = True
					# matrix validated and initialized
				except FileNotFoundError :
					self._logger.error( '...file not found...')
					return self._validated , dim_x , 0
				except Exception as e :
					self._logger.error( e.message )
					return self._validated , dim_x , 0


				return self._validated , dim_x , len( lines )


			# protected
			def _visited( self ,
						 i ,
						 j ,
						 matrix ,
						 v_matrix ,
			             row_count ,
						 col_count ,
						 token ) :
				"""

				:param i:
				:param j:
				:param matrix:
				:param v_matrix:
				:param row_count:
				:param col_count:
				:param token:
				:return
				"""

				counter_token = ''
				if token == 'x' :
					counter_token = 'o'
				else :
					counter_token = 'x'

				if i < 0 or j < 0 :
					return

				if i >= row_count or j >= col_count :
					return

                # already visited
				if v_matrix[i][j] is True :
					return

				# not a token
				if matrix[i][j] == counter_token :
					return

				v_matrix[i][j] = True
				self._current_blob_count += 1


				# tag adjacent cells
				self._visited ( i+1, j , matrix, v_matrix , row_count, col_count , token )
				self._visited ( i-1 , j , matrix, v_matrix , row_count, col_count , token )
				self._visited ( i, j+1 , matrix, v_matrix , row_count , col_count , token )
				self._visited ( i, j-1 , matrix,  v_matrix, row_count, col_count , token )




			def _zn_bfs( self , token ) :
				"""

				bfs

				:return
				"""

				self._logger.info( '...zn_bfs...' + token + '...' )
				count = 0
				for i in range( 0 , self._rows ) :
					for j in range( 0 , self._cols ) :
						if self._matrix[i][j] == token and self._visitor_matrix[i][j] == False :
							self._visited ( i , j , self._matrix , self._visitor_matrix , self._rows , self._cols , token )
							if self._current_blob_count > zn_atoms[token.upper()] :
								zn_atoms[token.upper()] = self._current_blob_count
							self._current_blob_count = 0







# ------------------------------------------------------------------------------
def process( target ) :
			"""

			:param target:
			:return:
			"""


			znb = None
			try :
				znb = zn_blob_detector( target_file=target , pre_validate=True )
				znb.logger.info( '...process...' )
				znb.perform()
			except Exception as e :
				znb.logger.error( e.message )
			else :
				znb.logger.info( zn_atoms )
			finally :
				znb.logger.info( '...fini...' )


# --------------------------------------------------------------------------------------
if __name__ == '__main__':

			if ( sys.version_info < ( 3 , 0) ) :
				print( '...python3 required...' )
				sys.exit( 1 )
			parser = argparse.ArgumentParser( description = 'zonar blob detector.' )
			parser.add_argument( 'blob_file' , help='input file of blob data' )
			args = parser.parse_args()

			# process
			process( args.blob_file )




