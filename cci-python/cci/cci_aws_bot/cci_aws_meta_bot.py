# cci_aws_meta_bot.py willliam k. johnson 2016


import os
import sys
#############
import doctest
import unittest
##############
import requests
import logging
import argparse
##############
from abc import ABCMeta , abstractmethod
##############
import cci_utils.cci_io_tools as io
import cci_utils.cci_constants as const
##############
import boto3


const.ec2 = 'ec2'
# ------------------------------------------------------------------------------
class cci_mini_aws_bot( object ) :
        """
        minimal wrapper for boto3
        """

        def __init__( self ,
                      domain_account=None ) :

            self._logger = io.init_logging( self.__class__.__name__  )
            self._logger.info( self.__class__.__name__ + '...'  )
            self._boto_session = boto3.Session( profile_name = 'defailt' )
            self._ec2_client = None
            self._ec2_metadata = None

            self._domain_account = domain_account


        @property
        def ec2_client( self ) :
            return self._ec2_client
        @ec2_client.setter
        def ec2_client( self , service ) :
            self._ec2_client = service



# ------------------------------------------------------------------------
if __name__ == '__main__' :

        ostr = io.ostream_py()

        try :

           aws = cci_mini_aws_bot()
           aws.ec2_client = boto3.client( const.ec2 )
           print( aws.ec2_client.describe_hosts() )

           # print ( reservations[0]['Group'] )

        except IOError as e :
            ostr << 'IO error ' << e.message << const.endl
        except Exception as e:
            ostr << 'error:' + e.message << const.endl
