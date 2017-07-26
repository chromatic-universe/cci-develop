//cci_mini_curl_run.cpp   chromatic universe 2017    william k. johnson


#include <cci_curl_stream.h>


using namespace cpp_real_stream;
using json = nlohmann::json;


int main( int argc , char** argv )
{
	 
		//library init and de-init	
		curlpp::Cleanup _cleanup;


		try
		{
			auto curl = std::make_unique<cci_curl_stream>();
			//curl->execute_base_bool_p( "http://localhost:7080/mongo/imap2017/plain_text_auth" ,
                        //                           "user=wiljoh&password=Argentina1" ,
                        //                         &std::cerr );
		        auto ostr = std::make_unique<std::ostringstream>();
			json mon;
			json meta_j = { { "from" , "wiljoh" } };
			json naked_j = { { "url" , "http://127.0.0.1:7080/mongo/imap2017/instantiate_atomic_payload" } };
			json resource_j = { { "resource_locator" , "file://opt/imap/spool/staging/foo" } } ;


			curl->instantiate_atomic_payload( mon ,
					                  meta_j ,
							  naked_j ,
							  resource_j ,
							  ostr.get() );

		}
		catch( curlpp::RuntimeError &e )
		{
			std::cerr << e.what() 
				  << "\n";
		}
		catch( curlpp::LogicError &e )
		{
			std::cerr << e.what() 
				  << "\n";
		}
		

		return 0;
}
