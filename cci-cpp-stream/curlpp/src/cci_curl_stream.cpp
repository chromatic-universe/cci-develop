//cci_curl_stream.cpp   chroamtic universe  2017   william k. johnson



#include <cci_curl_stream.h>

using namespace cpp_real_stream;


//---------------------------------------------------------------------------------------
cci_curl_stream::cci_curl_stream()
{
}

//---------------------------------------------------------------------------------------
cci_curl_stream::~cci_curl_stream()
{
}

//---------------------------------------------------------------------------------------
bool cci_curl_stream::execute_base_bool_g( const std::string& url ,
				           std::ostream* ostr )
{
			
		//ACE_Trace _( ACE_TEXT( "mongo_protocol_store::perform boolean find" ) , __LINE__ );
		//ACE_DEBUG(( LM_INFO , "%D (%P) url=%s...\n" , q.url().c_str() ) );
		
		try
		{
			*ostr  << "request output: "
			       << curlpp::options::Url(  url )
			       << "\n";	

			return true;
		}
		catch( curlpp::RuntimeError &e )
		{
			*ostr << e.what() 
				      << "\n";
		}
		catch( curlpp::LogicError &e )
		{
			*ostr << e.what() 
			      << "\n";
		}
		catch( ... )
		{
			std::cerr << "untyped exception...."
				  << "\n";

		}

			
		return false; 

}
