//cci_mini_curl_run.cpp   chromatic universe 2017    william k. johnson


#include <cci_curl_stream.h>


using namespace cpp_real_stream;


int main( int argc , char** argv )
{
	 
		//library init and de-init	
		curlpp::Cleanup _cleanup;


		try
		{
			auto curl = std::make_unique<cci_curl_stream>();
			curl->execute_base_bool_p( "http://localhost:7080/mongo/imap2017/plain_text_auth" ,
                                                   "user=wiljoh&password=Argentina1" ,
                                                   &std::cerr );
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
