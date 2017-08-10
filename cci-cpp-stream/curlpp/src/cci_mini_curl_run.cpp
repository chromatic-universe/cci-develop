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
			auto curl = make_unique<cci_curl_stream>();
			//curl->execute_base_bool_p( "http://localhost:7080/mongo/imap2017/plain_text_auth" ,
                        //                           "user=wiljoh&password=Argentina1" ,
                        //                         &std::cerr );
		        auto ostr = make_unique<std::ostringstream>();
			//json mon;
			//json meta_j = { { "from" , "wiljoh@localhost" } , { "to" , "corny@snaps" } };
			//json naked_j = { { "url" , "http://127.0.0.1:7080/mongo/imap2017/instantiate_atomic_payload" } };
			//json resource_j = { { "resource" , "/opt/imap_spool/staging/201707261829.7a9bee45" } } ;


			//curl->instantiate_atomic_payload( mon ,
			//		                  meta_j ,
			//				  naked_j ,
			//				  resource_j ,
			//				  ostr.get() );
			json mon = { { "context" , "other_users" } };
                        json url = { { "url" , "http://localhost:7080/mongo/imap2017/retr_namespace" } };
			curl->results_by_naked_param( mon , url ,  ostr.get() );
			

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
