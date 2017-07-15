//cci_curl_steam.h    chromatic universe   2017  william k. johnson

#pragma once


#include <cci_curl_stream_t.h>
#include <cci_curl_preamble.hpp>

namespace cpp_real_stream
{
	
		//forward declarations
		class cci_curl_stream;

		//aliases
		using curl_strm_t = cci_curl_stream*;


		class  cci_curl_stream
		{
			public :
				
				//ctor 
				cci_curl_stream();				


				//door
				virtual ~cci_curl_stream();


			private :

				//
				

			public : 
				
				//base bool , i.e , non-parameterized-if the url returns
				//get call returns anything ? true : false;
				//get
				bool execute_base_bool_g( const std::string&  url  ,
							  std::ostream* ostr );
			

				
		};

				
}

