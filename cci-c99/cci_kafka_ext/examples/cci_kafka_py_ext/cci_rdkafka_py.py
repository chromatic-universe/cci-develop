# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.11
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_cci_rdkafka_py', [dirname(__file__)])
        except ImportError:
            import _cci_rdkafka_py
            return _cci_rdkafka_py
        if fp is not None:
            try:
                _mod = imp.load_module('_cci_rdkafka_py', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _cci_rdkafka_py = swig_import_helper()
    del swig_import_helper
else:
    import _cci_rdkafka_py
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


OUTPUT_HEXDUMP = _cci_rdkafka_py.OUTPUT_HEXDUMP
OUTPUT_RAW = _cci_rdkafka_py.OUTPUT_RAW
class kafka_context(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, kafka_context, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, kafka_context, name)
    __repr__ = _swig_repr
    __swig_setmethods__["kafka_ptr"] = _cci_rdkafka_py.kafka_context_kafka_ptr_set
    __swig_getmethods__["kafka_ptr"] = _cci_rdkafka_py.kafka_context_kafka_ptr_get
    if _newclass:kafka_ptr = _swig_property(_cci_rdkafka_py.kafka_context_kafka_ptr_get, _cci_rdkafka_py.kafka_context_kafka_ptr_set)
    __swig_setmethods__["conf_ptr"] = _cci_rdkafka_py.kafka_context_conf_ptr_set
    __swig_getmethods__["conf_ptr"] = _cci_rdkafka_py.kafka_context_conf_ptr_get
    if _newclass:conf_ptr = _swig_property(_cci_rdkafka_py.kafka_context_conf_ptr_get, _cci_rdkafka_py.kafka_context_conf_ptr_set)
    __swig_setmethods__["conf_topic_ptr"] = _cci_rdkafka_py.kafka_context_conf_topic_ptr_set
    __swig_getmethods__["conf_topic_ptr"] = _cci_rdkafka_py.kafka_context_conf_topic_ptr_get
    if _newclass:conf_topic_ptr = _swig_property(_cci_rdkafka_py.kafka_context_conf_topic_ptr_get, _cci_rdkafka_py.kafka_context_conf_topic_ptr_set)
    __swig_setmethods__["topic_ptr"] = _cci_rdkafka_py.kafka_context_topic_ptr_set
    __swig_getmethods__["topic_ptr"] = _cci_rdkafka_py.kafka_context_topic_ptr_get
    if _newclass:topic_ptr = _swig_property(_cci_rdkafka_py.kafka_context_topic_ptr_get, _cci_rdkafka_py.kafka_context_topic_ptr_set)
    __swig_setmethods__["metadata_ptr"] = _cci_rdkafka_py.kafka_context_metadata_ptr_set
    __swig_getmethods__["metadata_ptr"] = _cci_rdkafka_py.kafka_context_metadata_ptr_get
    if _newclass:metadata_ptr = _swig_property(_cci_rdkafka_py.kafka_context_metadata_ptr_get, _cci_rdkafka_py.kafka_context_metadata_ptr_set)
    __swig_setmethods__["brokers"] = _cci_rdkafka_py.kafka_context_brokers_set
    __swig_getmethods__["brokers"] = _cci_rdkafka_py.kafka_context_brokers_get
    if _newclass:brokers = _swig_property(_cci_rdkafka_py.kafka_context_brokers_get, _cci_rdkafka_py.kafka_context_brokers_set)
    __swig_setmethods__["topic_str"] = _cci_rdkafka_py.kafka_context_topic_str_set
    __swig_getmethods__["topic_str"] = _cci_rdkafka_py.kafka_context_topic_str_get
    if _newclass:topic_str = _swig_property(_cci_rdkafka_py.kafka_context_topic_str_get, _cci_rdkafka_py.kafka_context_topic_str_set)
    __swig_setmethods__["group_id"] = _cci_rdkafka_py.kafka_context_group_id_set
    __swig_getmethods__["group_id"] = _cci_rdkafka_py.kafka_context_group_id_get
    if _newclass:group_id = _swig_property(_cci_rdkafka_py.kafka_context_group_id_get, _cci_rdkafka_py.kafka_context_group_id_set)
    __swig_setmethods__["partitions_ptr"] = _cci_rdkafka_py.kafka_context_partitions_ptr_set
    __swig_getmethods__["partitions_ptr"] = _cci_rdkafka_py.kafka_context_partitions_ptr_get
    if _newclass:partitions_ptr = _swig_property(_cci_rdkafka_py.kafka_context_partitions_ptr_get, _cci_rdkafka_py.kafka_context_partitions_ptr_set)
    __swig_setmethods__["mode"] = _cci_rdkafka_py.kafka_context_mode_set
    __swig_getmethods__["mode"] = _cci_rdkafka_py.kafka_context_mode_get
    if _newclass:mode = _swig_property(_cci_rdkafka_py.kafka_context_mode_get, _cci_rdkafka_py.kafka_context_mode_set)
    __swig_setmethods__["partition"] = _cci_rdkafka_py.kafka_context_partition_set
    __swig_getmethods__["partition"] = _cci_rdkafka_py.kafka_context_partition_get
    if _newclass:partition = _swig_property(_cci_rdkafka_py.kafka_context_partition_get, _cci_rdkafka_py.kafka_context_partition_set)
    __swig_setmethods__["debug_flags"] = _cci_rdkafka_py.kafka_context_debug_flags_set
    __swig_getmethods__["debug_flags"] = _cci_rdkafka_py.kafka_context_debug_flags_get
    if _newclass:debug_flags = _swig_property(_cci_rdkafka_py.kafka_context_debug_flags_get, _cci_rdkafka_py.kafka_context_debug_flags_set)
    __swig_setmethods__["dump_config"] = _cci_rdkafka_py.kafka_context_dump_config_set
    __swig_getmethods__["dump_config"] = _cci_rdkafka_py.kafka_context_dump_config_get
    if _newclass:dump_config = _swig_property(_cci_rdkafka_py.kafka_context_dump_config_get, _cci_rdkafka_py.kafka_context_dump_config_set)
    __swig_setmethods__["is_running"] = _cci_rdkafka_py.kafka_context_is_running_set
    __swig_getmethods__["is_running"] = _cci_rdkafka_py.kafka_context_is_running_get
    if _newclass:is_running = _swig_property(_cci_rdkafka_py.kafka_context_is_running_get, _cci_rdkafka_py.kafka_context_is_running_set)
    __swig_setmethods__["exit_eof"] = _cci_rdkafka_py.kafka_context_exit_eof_set
    __swig_getmethods__["exit_eof"] = _cci_rdkafka_py.kafka_context_exit_eof_get
    if _newclass:exit_eof = _swig_property(_cci_rdkafka_py.kafka_context_exit_eof_get, _cci_rdkafka_py.kafka_context_exit_eof_set)
    __swig_setmethods__["wait_eof"] = _cci_rdkafka_py.kafka_context_wait_eof_set
    __swig_getmethods__["wait_eof"] = _cci_rdkafka_py.kafka_context_wait_eof_get
    if _newclass:wait_eof = _swig_property(_cci_rdkafka_py.kafka_context_wait_eof_get, _cci_rdkafka_py.kafka_context_wait_eof_set)
    __swig_setmethods__["start_offset"] = _cci_rdkafka_py.kafka_context_start_offset_set
    __swig_getmethods__["start_offset"] = _cci_rdkafka_py.kafka_context_start_offset_get
    if _newclass:start_offset = _swig_property(_cci_rdkafka_py.kafka_context_start_offset_get, _cci_rdkafka_py.kafka_context_start_offset_set)
    __swig_setmethods__["argc"] = _cci_rdkafka_py.kafka_context_argc_set
    __swig_getmethods__["argc"] = _cci_rdkafka_py.kafka_context_argc_get
    if _newclass:argc = _swig_property(_cci_rdkafka_py.kafka_context_argc_get, _cci_rdkafka_py.kafka_context_argc_set)
    __swig_setmethods__["argv"] = _cci_rdkafka_py.kafka_context_argv_set
    __swig_getmethods__["argv"] = _cci_rdkafka_py.kafka_context_argv_get
    if _newclass:argv = _swig_property(_cci_rdkafka_py.kafka_context_argv_get, _cci_rdkafka_py.kafka_context_argv_set)
    __swig_setmethods__["result"] = _cci_rdkafka_py.kafka_context_result_set
    __swig_getmethods__["result"] = _cci_rdkafka_py.kafka_context_result_get
    if _newclass:result = _swig_property(_cci_rdkafka_py.kafka_context_result_get, _cci_rdkafka_py.kafka_context_result_set)
    __swig_setmethods__["cci_production_preamble"] = _cci_rdkafka_py.kafka_context_cci_production_preamble_set
    __swig_getmethods__["cci_production_preamble"] = _cci_rdkafka_py.kafka_context_cci_production_preamble_get
    if _newclass:cci_production_preamble = _swig_property(_cci_rdkafka_py.kafka_context_cci_production_preamble_get, _cci_rdkafka_py.kafka_context_cci_production_preamble_set)
    __swig_setmethods__["cci_consumer_preamble"] = _cci_rdkafka_py.kafka_context_cci_consumer_preamble_set
    __swig_getmethods__["cci_consumer_preamble"] = _cci_rdkafka_py.kafka_context_cci_consumer_preamble_get
    if _newclass:cci_consumer_preamble = _swig_property(_cci_rdkafka_py.kafka_context_cci_consumer_preamble_get, _cci_rdkafka_py.kafka_context_cci_consumer_preamble_set)
    __swig_setmethods__["cci_mini_run"] = _cci_rdkafka_py.kafka_context_cci_mini_run_set
    __swig_getmethods__["cci_mini_run"] = _cci_rdkafka_py.kafka_context_cci_mini_run_get
    if _newclass:cci_mini_run = _swig_property(_cci_rdkafka_py.kafka_context_cci_mini_run_get, _cci_rdkafka_py.kafka_context_cci_mini_run_set)
    __swig_setmethods__["cci_release_context"] = _cci_rdkafka_py.kafka_context_cci_release_context_set
    __swig_getmethods__["cci_release_context"] = _cci_rdkafka_py.kafka_context_cci_release_context_get
    if _newclass:cci_release_context = _swig_property(_cci_rdkafka_py.kafka_context_cci_release_context_get, _cci_rdkafka_py.kafka_context_cci_release_context_set)
    __swig_setmethods__["cci_stop_signal"] = _cci_rdkafka_py.kafka_context_cci_stop_signal_set
    __swig_getmethods__["cci_stop_signal"] = _cci_rdkafka_py.kafka_context_cci_stop_signal_get
    if _newclass:cci_stop_signal = _swig_property(_cci_rdkafka_py.kafka_context_cci_stop_signal_get, _cci_rdkafka_py.kafka_context_cci_stop_signal_set)
    __swig_setmethods__["cci_usr1_signal"] = _cci_rdkafka_py.kafka_context_cci_usr1_signal_set
    __swig_getmethods__["cci_usr1_signal"] = _cci_rdkafka_py.kafka_context_cci_usr1_signal_get
    if _newclass:cci_usr1_signal = _swig_property(_cci_rdkafka_py.kafka_context_cci_usr1_signal_get, _cci_rdkafka_py.kafka_context_cci_usr1_signal_set)
    __swig_setmethods__["cci_logger"] = _cci_rdkafka_py.kafka_context_cci_logger_set
    __swig_getmethods__["cci_logger"] = _cci_rdkafka_py.kafka_context_cci_logger_get
    if _newclass:cci_logger = _swig_property(_cci_rdkafka_py.kafka_context_cci_logger_get, _cci_rdkafka_py.kafka_context_cci_logger_set)
    __swig_setmethods__["cci_hex_dump"] = _cci_rdkafka_py.kafka_context_cci_hex_dump_set
    __swig_getmethods__["cci_hex_dump"] = _cci_rdkafka_py.kafka_context_cci_hex_dump_get
    if _newclass:cci_hex_dump = _swig_property(_cci_rdkafka_py.kafka_context_cci_hex_dump_get, _cci_rdkafka_py.kafka_context_cci_hex_dump_set)
    __swig_setmethods__["cci_topic_metadata"] = _cci_rdkafka_py.kafka_context_cci_topic_metadata_set
    __swig_getmethods__["cci_topic_metadata"] = _cci_rdkafka_py.kafka_context_cci_topic_metadata_get
    if _newclass:cci_topic_metadata = _swig_property(_cci_rdkafka_py.kafka_context_cci_topic_metadata_get, _cci_rdkafka_py.kafka_context_cci_topic_metadata_set)
    __swig_setmethods__["cci_msg_consume"] = _cci_rdkafka_py.kafka_context_cci_msg_consume_set
    __swig_getmethods__["cci_msg_consume"] = _cci_rdkafka_py.kafka_context_cci_msg_consume_get
    if _newclass:cci_msg_consume = _swig_property(_cci_rdkafka_py.kafka_context_cci_msg_consume_get, _cci_rdkafka_py.kafka_context_cci_msg_consume_set)
    __swig_setmethods__["cci_msg_delivered"] = _cci_rdkafka_py.kafka_context_cci_msg_delivered_set
    __swig_getmethods__["cci_msg_delivered"] = _cci_rdkafka_py.kafka_context_cci_msg_delivered_get
    if _newclass:cci_msg_delivered = _swig_property(_cci_rdkafka_py.kafka_context_cci_msg_delivered_get, _cci_rdkafka_py.kafka_context_cci_msg_delivered_set)
    __swig_setmethods__["cci_partition_rebalance"] = _cci_rdkafka_py.kafka_context_cci_partition_rebalance_set
    __swig_getmethods__["cci_partition_rebalance"] = _cci_rdkafka_py.kafka_context_cci_partition_rebalance_get
    if _newclass:cci_partition_rebalance = _swig_property(_cci_rdkafka_py.kafka_context_cci_partition_rebalance_get, _cci_rdkafka_py.kafka_context_cci_partition_rebalance_set)
    def __init__(self): 
        this = _cci_rdkafka_py.new_kafka_context()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _cci_rdkafka_py.delete_kafka_context
    __del__ = lambda self : None;
kafka_context_swigregister = _cci_rdkafka_py.kafka_context_swigregister
kafka_context_swigregister(kafka_context)
cvar = _cci_rdkafka_py.cvar


def cci_kf_logger(*args):
  return _cci_rdkafka_py.cci_kf_logger(*args)
cci_kf_logger = _cci_rdkafka_py.cci_kf_logger

def cci_kf_msg_delivered(*args):
  return _cci_rdkafka_py.cci_kf_msg_delivered(*args)
cci_kf_msg_delivered = _cci_rdkafka_py.cci_kf_msg_delivered

def cci_kf_msg_consume(*args):
  return _cci_rdkafka_py.cci_kf_msg_consume(*args)
cci_kf_msg_consume = _cci_rdkafka_py.cci_kf_msg_consume

def cci_kf_production_preamble(*args):
  return _cci_rdkafka_py.cci_kf_production_preamble(*args)
cci_kf_production_preamble = _cci_rdkafka_py.cci_kf_production_preamble

def cci_kf_consumer_preamble(*args):
  return _cci_rdkafka_py.cci_kf_consumer_preamble(*args)
cci_kf_consumer_preamble = _cci_rdkafka_py.cci_kf_consumer_preamble

def cci_kf_hex_dump(*args):
  return _cci_rdkafka_py.cci_kf_hex_dump(*args)
cci_kf_hex_dump = _cci_rdkafka_py.cci_kf_hex_dump

def cci_kf_metadata_print(*args):
  return _cci_rdkafka_py.cci_kf_metadata_print(*args)
cci_kf_metadata_print = _cci_rdkafka_py.cci_kf_metadata_print

def cci_kf_mini_run(*args):
  return _cci_rdkafka_py.cci_kf_mini_run(*args)
cci_kf_mini_run = _cci_rdkafka_py.cci_kf_mini_run

def cci_release_context(*args):
  return _cci_rdkafka_py.cci_release_context(*args)
cci_release_context = _cci_rdkafka_py.cci_release_context

def cci_stop_signal(*args):
  return _cci_rdkafka_py.cci_stop_signal(*args)
cci_stop_signal = _cci_rdkafka_py.cci_stop_signal

def cci_usr1_signal(*args):
  return _cci_rdkafka_py.cci_usr1_signal(*args)
cci_usr1_signal = _cci_rdkafka_py.cci_usr1_signal

def cci_kf_rebalance_cb(*args):
  return _cci_rdkafka_py.cci_kf_rebalance_cb(*args)
cci_kf_rebalance_cb = _cci_rdkafka_py.cci_kf_rebalance_cb

def ex_parte_producer(*args):
  return _cci_rdkafka_py.ex_parte_producer(*args)
ex_parte_producer = _cci_rdkafka_py.ex_parte_producer

def ex_parte_consumer(*args):
  return _cci_rdkafka_py.ex_parte_consumer(*args)
ex_parte_consumer = _cci_rdkafka_py.ex_parte_consumer

def ex_parte_atomic_production(*args):
  return _cci_rdkafka_py.ex_parte_atomic_production(*args)
ex_parte_atomic_production = _cci_rdkafka_py.ex_parte_atomic_production

def configuration_dump(*args):
  return _cci_rdkafka_py.configuration_dump(*args)
configuration_dump = _cci_rdkafka_py.configuration_dump

def cci_kf_retr_topics(*args):
  return _cci_rdkafka_py.cci_kf_retr_topics(*args)
cci_kf_retr_topics = _cci_rdkafka_py.cci_kf_retr_topics

def print_args(*args):
  return _cci_rdkafka_py.print_args(*args)
print_args = _cci_rdkafka_py.print_args
# This file is compatible with both classic and new-style classes.


