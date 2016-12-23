# zb_test.py     william k. johnson chromatic universe 2016

# python standard
import os
import sys
import unittest
import subprocess as proc

# zb
from zn_blob_detect import zn_blob_detector , max_dimension




# ---------------------------------------------------------------------------
class test_zb_interferface( unittest.TestCase ) :

			"""
			minimal test suite
			"""

			def setUp( self ) :

				self._source = 'zb_data'
				self._source_not_found = 'zb_data_not_found'
				self._source_illegal_token = 'bad_zb_data_illegal'
				self._source_illegal_lopsided = 'bad_zb_data_lopsided'
				self._source_illegal_col_file = 'bad_zb_data_exceed_col_file'
				self._source_illegal_row_file = 'bad_zb_data_exceed_row_file'

				try :
					znb = zn_blob_detector( target_file = self._source , pre_validate=False )
					cmd = ['uname' , '-a']
					out = proc.check_output( cmd )
					znb.logger.info( out.decode().strip() )
				except :
					pass



			def test_zb_max_dimension_xy_good( self ) :

				"""

				:return:
				"""


				znb = zn_blob_detector( target_file = self._source , pre_validate=True )
				znb.perform()


				self.assertTrue( znb.validated )



			def test_zb_max_dimension_xy_bad( self ) :

				"""

				:return:
				"""


				dim = 2
				znb = zn_blob_detector( target_file = self._source , pre_validate=True , dimension_max = dim )
				znb.perform()



				self.assertFalse( znb.validated )



			def test_remove_whitespace( self ) :

				"""

				:return:
				"""

				whitespace_str = '0 X 0 X 0 X X 0\n'
				dim = 250

				znb = zn_blob_detector( target_file = self._source , pre_validate=True )
				b_ret  , s , dw_len = znb._remove_whitespace( whitespace_str , znb.logger, dim )


				self.assertTrue( b_ret )



			def test_remove_whitespace_len( self ) :

				"""

				:return:
				"""

				whitespace_str = '0 X 0 X 0 X X 0\n'
				l = 8
				dim = 250

				znb = zn_blob_detector( target_file = self._source , pre_validate=True )
				b_ret  , s , dw_len = znb._remove_whitespace( whitespace_str , znb.logger, dim )


				self.assertTrue( l == dw_len )



			def test_source_file_exists( self ) :
				"""

				:return:
				"""


				znb = zn_blob_detector( target_file = self._source , pre_validate=True )


				self.assertTrue( znb.validated )



			def test_source_file_does_not_exist( self ) :
				"""

				:return:
				"""


				znb = zn_blob_detector( target_file = self._source_not_found , pre_validate=True )


				self.assertFalse( znb.validated )


			def test_illegal_input_token( self ) :
				"""

				:return:
				"""


				znb = zn_blob_detector( target_file = self._source_illegal_token , pre_validate=True )


				self.assertFalse( znb.validated )



			def test_illegal_lopsided_matrix( self ) :
				"""

				:return:
				"""


				znb = zn_blob_detector( target_file = self._source_illegal_lopsided , pre_validate=True )


				self.assertFalse( znb.validated )



			def test_illegal_exceed_col_file( self ) :
				"""

				:return:
				"""


				znb = zn_blob_detector( target_file = self._source_illegal_col_file , pre_validate=True )


				self.assertFalse( znb.validated )



			def test_illegal_exceed_row_file( self ) :
				"""

				:return:
				"""


				znb = zn_blob_detector( target_file = self._source_illegal_row_file , pre_validate=True )


				self.assertFalse( znb.validated )







# ---------------------------------------------------------------------------

if __name__ == "__main__":

				if ( sys.version_info < ( 3 , 0) ) :
					print( '...python3 required...' )
					sys.exit( 1 )

				unittest.main()