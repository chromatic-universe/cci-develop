//cci_curl_stream_t.h   chromatic universe 2017    william k. johnson


#pragma once


#include <memory>
#include <set>
#include <map>
#include <list>
#include <tuple>
#include <algorithm>
#include <type_traits>
//c runtime
#include <ctime>
#include <cstdint>
#include <cassert>
#include <sys/types.h>
#include <unistd.h>

//curlpp
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

//cci
#include "cci_time_utils.h"



namespace cpp_real_stream

{
		
		//forward declarations
		template <
				typename T
		         >
                class cci_curl_preamble; 

}

