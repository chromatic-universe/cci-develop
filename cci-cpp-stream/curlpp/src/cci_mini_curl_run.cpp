//cci_mini_curl_run.cpp   chromatic universe 2017    william k. johnson


#include <cci_curl_stream.h>


using namespace cpp_real_stream;


int main( int argc , char** argv )
{
	 
		//library init and de-init	
		curlpp::Cleanup _cleanup;


		try
		{
			std::cerr << curlpp::options::Url( "http://localhost:7080/mongo/imap2017" )
				  << "\n";	
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
