 //cci_curl_stream.cpp   chroamtic universe  2017   william k. johnson



#include <cci_curl_stream.h>
#include <cstdlib>
#include <mutex>

using namespace cpp_real_stream;
using namespace curlpp::Options;
using json = nlohmann::json;

namespace
{

	const std::string url_encode_t { "Content-Type: application/x-www-form-urlencoded" };
	const std::string app_json_t   { "Content-Type: application/json" };

   	std::future<std::string> invoke_async_post( const std::string& url ,
                                                const std::string& params );
    std::future<std::string> invoke_async_post_ssl(  const std::string& url ,
                                                     const std::string& params ,
                                                     bool verify_host = true );



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

	std::unique_ptr<stream_debug> strd = make_unique<stream_debug>();

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

	//-------------------------------------------------------------------------------
	void enum_async_info( std::ostream& ostr  , curlpp::Multi mult , curlpp::Easy& easy )
	{
		//transfer status
		curlpp::Multi::Msgs msgs = mult.info();
		for( auto atom : msgs )
		{
			if( atom.second.msg == CURLMSG_DONE )
			{
				if( atom.first == &easy  )
				{
					ostr << "...request completed with status of "
                         << atom.second.code
					     << "\n";
					break;
				}
			}
		}
	}

	//---------------------------------------------------------------------------------------
	std::future<std::string> invoke_async_post( const std::string& url ,
                                                const std::string& params )
	{
			    return std::async( std::launch::async ,
				[&] ( const std::string& url , const std::string& params ) mutable
				{
				      std::ostringstream response;

				      std::list<std::string> header;
				      header.push_back( app_json_t );

				      curlpp::Easy r;
				      r.setOpt( curlpp::options::Url( url ) );
				      r.setOpt( curlpp::options::HttpHeader( header ) );
                      r.setOpt( FailOnError( true  ));
				      r.setOpt( curlpp::options::PostFields( params ) );
				      r.setOpt( curlpp::options::PostFieldSize( params.length() ) );
				      r.setOpt( curlpp::options::Timeout( 60L ) );
				      r.setOpt( curlpp::options::ConnectTimeout( 10L ) );

				      r.setOpt( curlpp::options::WriteStream( &response ) );

				      r.perform();

				      return response.str();

				} , url , params );
	}

    //---------------------------------------------------------------------------------------
	std::future<std::string> invoke_async_post_ssl ( const std::string& url ,
                                                     const std::string& params ,
                                                     const bool verify_host ,
                                                     const std::string& dsn )
	{
		            std::cerr << "...ss;!...\n";
			    return std::async( std::launch::async ,
				[&] ( const std::string& url , const std::string& params ) mutable
				{
				      std::ostringstream response;
				      std::list<std::string> header;
				      header.push_back( app_json_t );
                      unsigned verify;
                      verify_host == true ? verify = 2L : verify = 0L;

				      curlpp::Easy r;
				      r.setOpt( curlpp::options::Url( url ) );
				      r.setOpt( curlpp::options::HttpHeader( header ) );
                      r.setOpt( FailOnError( true  ));
				      r.setOpt( curlpp::options::PostFields( params ) );
				      r.setOpt( curlpp::options::PostFieldSize( params.length() ) );
				      r.setOpt( curlpp::options::Timeout( 60L ) );
				      r.setOpt( curlpp::options::ConnectTimeout( 10L ) );
                      r.setOpt( curlpp::options::SslVerifyHost( 0 ) );
                      //r.setOpt( curlpp::options::CaInfo ( dsn ) );
                      r.setOpt( curlpp::options::SslVerifyPeer( 0 ) );

				      r.setOpt( curlpp::options::WriteStream( &response ) );

				      r.perform();

				      return response.str();

				} , url , params );
	}



}

//---------------------------------------------------------------------------------------
cci_curl_stream::cci_curl_stream() : m_debug { true } ,
                                     m_https { false  } ,
                                     m_verify_host { false  } ,
                                     m_endpoint_dsn { "" }
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

		//ostr->flush();

		try
		{

			request.setOpt (Url( url ) );
			curlpp::options::WriteStream ws( ostr );
	                request.setOpt( ws );
			request.setOpt( FailOnError( true  ));
            if( m_https == true )
            {
                      request.setOpt( curlpp::options::SslVerifyPeer( 0 ) );
                      request.setOpt( curlpp::options::SslVerifyHost( 0 ) );
            }

            //{ request.setOpt( curlpp::options::CaInfo ( endpoint_dsn() ) ); }

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
            if( m_https == true )
            {
                      request.setOpt( curlpp::options::SslVerifyPeer( 0 ) );
                      request.setOpt( curlpp::options::SslVerifyHost( 0 ) );
            }
            //{ request.setOpt( curlpp::options::CaInfo ( endpoint_dsn() ) ); }


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
            if( m_https == true )
            //{ request.setOpt( curlpp::options::SslVerifyHost( m_verify_host ) ); }
            { request.setOpt( curlpp::options::CaInfo ( endpoint_dsn() ) ); }



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

		return true;
}

//---------------------------------------------------------------------------------------
bool cci_curl_stream::results_by_naked_param( 	//naked param json
						const nlohmann::json& naked_param ,
						const nlohmann::json& url ,
						std::ostream* ostr )

{
		curlpp::Easy request;
		if( debug() )
		{ debug_request( request ); }


		try
		{
			ostr->flush();

			request.setOpt (Url( url.at( "url" ).get<std::string>() ) );
           	request.setOpt( FailOnError( true  ));
            if( m_https == true )
            {
                //request.setOpt( curlpp::options::CaInfo ( "/home/wiljoh/tornado_certs/chromatic-universe-expansion.pem") );
                //request.setOpt( curlpp::options::CaInfo ( endpoint_dsn() ) );
                request.setOpt( curlpp::options::SslVerifyHost( 0 ) );
                request.setOpt( curlpp::options::SslVerifyPeer( 0 ) );
            }


			string_list headers;
    		headers.push_back( app_json_t );

			base_post(  request ,
				        headers ,
                        naked_param.dump() ,
                        ostr );

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



		return true;
}

//---------------------------------------------------------------------------------------
void  cci_curl_stream::base_post( curlpp::Easy& req ,
				  const string_list& headers ,
				  const std::string& post_fields ,
				  std::ostream* ostr )

{

		//output write stream
		curlpp::options::WriteStream ws( ostr );
		req.setOpt( ws );

		req.setOpt( FailOnError( true  ));
		req.setOpt( curlpp::options::HttpHeader( headers ) );

		req.setOpt( curlpp::options::PostFields( post_fields ) );
		req.setOpt( curlpp::options::PostFieldSize( post_fields.length() ) );
        if( m_https == true )
        {
            req.setOpt( curlpp::options::SslVerifyHost( 0 ) );
            req.setOpt( curlpp::options::SslVerifyPeer( 0 ) );
            //req.setOpt( curlpp::options::CaInfo ( endpoint_dsn() ) );
            //req.setOpt( curlpp::options::CaInfo ( "/home/wiljoh/tornado_certs/chromatic-universe-expansion.pem") );
        }

		req.perform();

}


//---------------------------------------------------------------------------------------
bool  cci_curl_stream::results_by_naked_param_async( 	const nlohmann::json& naked_param ,
                                                        const nlohmann::json& url ,
                                                        std::ostream* ostr ,
                                                        unsigned future_wait_duration_secs )
{

		bool b_ret { false };
        std::future<std::string> future;

		try
		{
            if( m_https == true ) { future = invoke_async_post_ssl( url.at( "url" ).get<std::string>() ,
                                                                   naked_param.dump() ,
                                                                   m_verify_host ,
                                                                   m_endpoint_dsn ); }
            else { future = invoke_async_post( url.at( "url" ).get<std::string>() ,
                                                                                         naked_param.dump() ); }


			std::cout << "waiting...invoke_async_post\n";
	        std::future_status status;
            do
			{
                status = future.wait_for( std::chrono::seconds( 9 ) );
				if( status == std::future_status::deferred )
				{   std::cerr << "deferre\n"; }
				else if( status == std::future_status::timeout )
				{   std::cerr << "timeout\n"; }
				else if( status == std::future_status::ready )
                                {   std::cerr << "ready!\n"; }

		    } while ( status != std::future_status::ready );



		    *ostr << future.get();

			b_ret = true;

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


		return b_ret;
}

