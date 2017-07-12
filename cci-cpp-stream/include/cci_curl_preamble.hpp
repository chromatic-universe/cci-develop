//cci_curl_stream.cpp   chromatic universe 2017    william k. johnson


#include <cci_curl_stream.h>


namespace cpp_real_stream
{
	
	
		//forward
				
	

		//services
		template <
				typename T
		         >
                class cci_curl_preamble 
		{
		
			public :

				//ctors
				cci_curl_preamble() : m_url_str{ "" } ,
						      m_b_valid{ false }

				{}

				explicit cci_curl_preamble( const std::string& url_str ) try : m_url_str{ url_str } ,
											       m_b_valid{ false }
				{
				}		
				catch( std::exception& err )
				{
					std::cerr << err.what() 
						  << "\n";	
				}
				catch ( curlpp::RuntimeError & err )
				{
					std::cerr << err.what() 
						  << "\n";
				}


				//dtor
				virtual ~cci_curl_preamble()
				{}

				
				//no copy
				cci_curl_preamble( const cci_curl_preamble& ) = delete;
				//no assign
				const cci_curl_preamble& operator= ( const cci_curl_preamble& ) = delete;
				//use unary bool compare
				bool operator!() const { return !m_b_valid; }



			private :

					//attributes
					std::string   		m_url_str;
					bool 			m_b_valid;
					T 			context;
				
			public :
			
					//accessors-mutators
					std::string url() const noexcept { return m_url_str; }
					

					//mutators
					void valid( bool vl ) { m_b_valid = vl; }


					//services
					
				
		};
			
		
}



