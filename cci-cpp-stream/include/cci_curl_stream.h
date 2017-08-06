//cci_curl_steam.h    chromatic universe   2017  william k. johnson

#pragma once


#include <cci_curl_stream_t.h>
#include <cci_curl_preamble.hpp>
#include <json.hpp>


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

				bool 		m_debug;


			protected :
			
				//helpers
				virtual void base_post( curlpp::Easy& req ,
						        const string_list& headers ,
						        const std::string& post_fields ,
                                                        std::ostream* ostr );
				

			public : 
				
				//accessors=inspectors
				virtual bool debug() const noexcept { return m_debug; }
				//mutators
				virtual void debug( const bool dbg ) { m_debug = dbg; }
				
				//base bool , i.e , non-parameterized-if the url returns
				//get call returns anything  no error ? true : false;
				//get
				//effective as ping				
				virtual bool execute_base_bool_g( const std::string&  url  ,
							  std::ostream* ostr );
				//base bool woth post fields
				//key pairs keu=value
			        //get call returns anything  no error ? true : false;
				//post
				virtual bool execute_base_bool_p( const std::string& url  ,
							  const std::string& post_fields ,
							  std::ostream* ostr );
				//atomic insertion -json; all string fields will have be serialized back to json
				//in 200 http , moniker will be populated
				//post
				virtual bool instantiate_atomic_payload( //user siginificant reference , returned by callee , "nil by default" 
									 nlohmann::json& moniker ,
									 //meta info , maybe rfc2822 header
									 const nlohmann::json& metadata ,	
									 //url destination - not checking of validity , 							 
									 const nlohmann::json& naked_archive_dest ,
									 //payload location - if this is 'nil'(default)
									 // , the location is contained in the url 
									 nlohmann::json resource_locator  = {{ "resource_locator" , "nil" }}  ,
									 std::ostream* ostr = nullptr );
				//json result set; 
				//naked param. i.e.,url post payload
				//in unvalidated json form.
				//post
				virtual bool results_by_naked_param( 	//naked param json 
									const nlohmann::json& naked_param ,	
									const nlohmann::json& url ,	
									std::ostream* ostr = nullptr );

			

				
		};

				
}

