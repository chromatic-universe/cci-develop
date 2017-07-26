//cci_curl_stream.cpp   chroamtic universe  2017   william k. johnson



#include <cci_curl_stream.h>

using namespace cpp_real_stream;
using namespace curlpp::Options;
using json = nlohmann::json;

namespace
{
	
	//------------------------------------------------------------------------------
	class stream_debug
	{
		public:
			int write_debug( curl_infotype , char *data , size_t size )
			{
						
				fprintf( stderr , "cci_curl_stream-debug : " );
				fwrite( data , size , 1 , stderr );
				

				return size;
			}
	};

	std::unique_ptr<stream_debug> strd = std::make_unique<stream_debug>();

	//-------------------------------------------------------------------------------
	void debug_request(  curlpp::Easy& req  )
	{
			req.setOpt( Verbose( true  ));

			using namespace std::placeholders;
			req.setOpt( DebugFunction( std::bind( &stream_debug::write_debug ,
							      strd.get() ,
							     _1 ,
							     _2 ,
							     _3 ) ) );
			
	
	}

	const std::string url_encode_t { "Content-Type: application/x-www-form-urlencoded" };
	const std::string app_json_t   { "Content-Type: application/json" };
}

//---------------------------------------------------------------------------------------
cci_curl_stream::cci_curl_stream() : m_debug { true }
{
}

//-------------------------- )-----------------------------------------------------------
cci_curl_stream::~cci_curl_stream()
{ 
}

//---------------------------------------------------------------------------------------
bool cci_curl_stream::execute_base_bool_g( const std::string& url ,
				           std::ostream* ostr )
{
			
		curlpp::Easy request;				
		if( debug() )	
		{ debug_request( request ); }

		try
		{
			
			request.setOpt (Url( url ) );
			curlpp::options::WriteStream ws( ostr );
	           	request.setOpt( ws );
			request.setOpt( FailOnError( true  ));
			request.perform();	

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
 
//---------------------------------------------------------------------------------------
bool cci_curl_stream::execute_base_bool_p( const std::string& url  ,
			  		   const std::string& post_fields ,
			  		   std::ostream* ostr )
{
		curlpp::Easy request;				
		if( debug() )	
		{ debug_request( request ); }

		ostr->flush();

		try
		{
			
			request.setOpt (Url( url ) );
			//output write stream
			curlpp::options::WriteStream ws( ostr );
			request.setOpt( ws );
			request.setOpt( FailOnError( true  ));

			std::list<std::string> header; 
    			header.push_back( url_encode_t );     
    			request.setOpt( curlpp::options::HttpHeader( header ) ); 

			request.setOpt( curlpp::options::PostFields( post_fields ) );
    			request.setOpt( curlpp::options::PostFieldSize( post_fields.length() ) );

			request.perform();	

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
//}
//atomic insert by locator, returns identifier by reference
//---------------------------------------------------------------------------------------
bool cci_curl_stream::instantiate_atomic_payload( json& moniker ,
						  const json& metadata ,
						  const json& naked_archive_dest ,
						  json resource_locator ,
						  std::ostream* ostr )
{
 		
		curlpp::Easy request;				
		if( debug() )	
		{ debug_request( request ); }


		try
		{
			ostr->flush();
		
			//build json object from stream
			std::ostringstream dostr;
			dostr << metadata
			      << naked_archive_dest
			      << resource_locator;
			//auto jsn = std::make_unique<json>();
			json jsn;
			jsn["metadata"] = metadata;
			jsn["naked_archive_dest"] = naked_archive_dest;
			jsn["resource_locator"] = resource_locator;
		
			request.setOpt (Url( naked_archive_dest.at( "url" ).get<std::string>() ) );
			//output write stream
			curlpp::options::WriteStream ws( ostr );
			request.setOpt( ws );
			request.setOpt( FailOnError( true  ));

			std::list<std::string> header; 
    			header.push_back( app_json_t );     
    			request.setOpt( curlpp::options::HttpHeader( header ) ); 

			request.setOpt( curlpp::options::PostFields( jsn.dump() ) );
    			request.setOpt( curlpp::options::PostFieldSize( jsn.dump().length() ) );

			request.perform();	

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
		catch( std::exception& err )
		{
			*ostr << err.what() 
			      << "\n";
		}
		catch( ... )
		{
			std::cerr << "untyped exception...."
				  << "\n";

		}

		return true;
}
