//cci_kafka_t.h            chromatic_universe  2017  willian k. johnson

#pragma once




//kafka
#include <librdkafka/rdkafkacpp.h>
//c++ std
#include <chrono>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>
#include <type_traits>
//c runtime
#include <ctime>
#include <cstdint>
#include <cassert>
#include <sys/types.h>
#include <unistd.h>
//cci
#include "cci_time_utils.h"
#include "cci_stream_generic.h"

//cmommand line
#include <tclap/CmdLine.h>


namespace rdkafka = RdKafka;
namespace tclap = TCLAP;

namespace cpp_real_stream
{
	//forward declarations
        class kf_callback_mogrifier;
	template<typename T> class event_callback_policy;
        template <
			typename T ,     
			template<class> class event_callback_policy,
			template<class> class consumer_callback_policy ,
                        template<class> class delivery_callback_policy
		 >	
        class cci_kafka_preamble; 
        class delivery_report_cb;
        enum class kafka_callback : char;



        //aliases
	using cci_kafka_broker = std::tuple<std::string,int,int>;
        using broker_ptr = std::unique_ptr<cci_kafka_broker>;
        using kafka_brokers = std::vector<broker_ptr>;
        using brokers_ptr = kafka_brokers*;
        using rd_consumer_ptr = rdkafka::Consumer*;
        using rd_producer_ptr = rdkafka::Producer*;
        using topic_ptr = rdkafka::Topic*;
        using callback_dictionary = std::map<kafka_callback,std::string>;
        using switch_arg = tclap::SwitchArg;
        using value_arg = tclap::ValueArg<std::string>;
        using cmd_line = tclap::CmdLine;

	class placeholder
	{
		public :
			
			placeholder()
			{}

	};

	//enumerations
	enum class broker_fields : char
        {
            bf_destination ,
            bf_port ,
            bf_partition
        };
	
        enum class kafka_callback : char
        {
            kc_sock ,
            kc_open ,
            kc_event ,
            kc_consumer ,
	    kc_delivery
        };



	

}
