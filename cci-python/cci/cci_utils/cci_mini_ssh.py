# cci_ssh.py willliam k. johnson 2016


import os
import sys
#############
import doctest
import unittest
from sets import Set
from abc import abstractmethod , ABCMeta
import copy
try:
    from cStringIO import StringIO
except:
    from StringIO import StringIO
##############
import requests
import logging
import argparse
import subprocess as proc

##############
import cci_utils.cci_io_tools as io
from cci_stream_inf import cci_stream_intf
import cci_utils.cci_constants as const

##############
import paramiko

class cci_ssh_util( object ) :

            __metaclass__ =  ABCMeta

            """
            minimal wrapper for paramiko and cryot
            """

            def __init__( self ,
                          key_file=None ,
                          target_server = None ) :
                """

                :param key_file:
                :param target_server:
                :return:
                """

                self._logger = io.init_logging( self.__class__.__name__  )
                self._logger.info( self.__class__.__name__ + '...'  )
                self._key_file = key_file ,
                self._target_server = target_server
                self._lines = []
                self._buffer = str()
                self._connection_live = False
                #paramiko client


            # object model
            def __repr__( self ) :
                 """
                 returns string representation and construction info
                 :rtype : basestring
                 :return:
                 """
                 return "{__class__.__name__}(key_file={_key_file!r},target_server={_target_serverr})". \
                        format( __class__=self.__class__ , **self.__dict__ )

            def __str__( self ) :
                  """
                  returns pretty string
                  :rtype: basestring
                  :return: str
                  """
                  return 'cci_mini_ssh , 2016 , william k. johnson'


            def __bool__( self ) :
                  """
                  :rtype bool
                  :return:
                  """
                  return self._connection_live

            # attributes
            @property
            def private_key( self ) :
                return self._key_file
            @private_key.setter
            def private_key( self , key ) :
                self.private_key = key
            @property
            def logger( self ) :
                return self._logger
            @logger.setter
            def logger( self , log ) :
                self._logger= log
            @property
            def lines( self ) :
                return self._lines
            @lines.setter
            def lines( self , li ) :
                self._lines = li
            @property
            def buffer( self ) :
                return self._buffer
            @buffer.setter
            def buffer( self ,buf ) :
                self._buffer = buf
            @property
            def live( self ) :
                return self._connection_live
            @live.setter
            def live( self ,lv ) :
                self._connection_live = lv

            # services
            def raw_key( self ) :

                 """
                 key from file

                 return: data
                 """

                 data = []
                 with open( self._key_file ) as file :
                    data = file.read()

                 return data

class cci_ssh_kafka( cci_ssh_util ) :

            """
            kafka ssh
            """
            def __init__( self ,
                          key_file=None ,
                          target_server = None ) :

                super( cci_ssh_kafka , self ).__init__( key_file ,
                                                        target_server )



# ------------------------------------------------------------------------
if __name__ == '__main__' :


            ostr = io.ostream_py()

            try :

                cci_ssh = cci_ssh_kafka()

            except IOError as e :
                ostr << 'IO error ' << e.message << const.endl
            except Exception as e:
                ostr << 'error:' + e.message << const.endl