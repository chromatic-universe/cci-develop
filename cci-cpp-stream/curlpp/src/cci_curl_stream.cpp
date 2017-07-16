//cci_curl_stream.cpp   chroamtic universe  2017   william k. johnson



#include <cci_curl_stream.h>

using namespace cpp_real_stream;
using namespace curlpp::Options;

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
