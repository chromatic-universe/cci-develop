//cci_mini_curl_run.cpp   chromatic universe 2017    william k. johnson


#include <cci_curl_stream.h>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;


using namespace cpp_real_stream;
using json = nlohmann::json;

//---------------------------------------------------------------------------------------------
bool retr_kernel_addr_space_snapshot( json& out , const std::string& internal_url )
{
          auto adapter_strm = std::make_unique<cci_curl_stream>();

          assert( adapter_strm );
          adapter_strm->debug( false );
          auto ostr = std::make_unique<std::ostringstream>();

          const std::string retr_call { "retr_one_addr_space_metadata" };
          std::ostringstream dostr;
          dostr << internal_url
                << "/"
                << retr_call;

          json mon = { { "moniker" , "cci_stream_mta" } };
          json naked_j = { { "url" ,  dostr.str() } };


          bool b_ret = adapter_strm->results_by_naked_param_async( mon ,
                                                                   naked_j ,
                                                                   ostr.get() );
          if( b_ret )
          { out = json::parse( ostr->str() ); }

          std::cerr << ostr->str()
                    << "\n";

          return b_ret;

}

//---------------------------------------------------------------------------------------------
bool retr_fetch_inquiry( json& out , const std::string& internal_url )
{
          auto adapter_strm = std::make_unique<cci_curl_stream>();

          assert( adapter_strm );
          adapter_strm->debug( false );
          adapter_strm->https( true  );
          adapter_strm->verify_host( false );
          auto ostr = std::make_unique<std::ostringstream>();

          const std::string retr_call { "fetch_ping_query" };
          std::ostringstream dostr;
          dostr << internal_url
                << "/"
                << retr_call;

          json mon = { { "moniker" , "cci_stream_mta" } };
          json naked_j = { { "url" ,  dostr.str() } };


          bool b_ret = adapter_strm->results_by_naked_param_async( mon ,
                                                                   naked_j ,
                                                                   ostr.get() );
          if( b_ret )
          { out = json::parse( ostr->str() ); }

          //std::cerr << ostr->str()
          //          << "\n";

          return b_ret;

}


//---------------------------------------------------------------------------------------------
bool retr_db_connection_info( json& out , const std::string& internal_url )
{
          auto adapter_strm = std::make_unique<cci_curl_stream>();

          assert( adapter_strm );
          adapter_strm->debug( false );
          adapter_strm->https( true  );
          adapter_strm->verify_host( false );
          adapter_strm->endpoint_dsn( "/etc/chromatic-universe/certs/chromatic-1.pem" );
          auto ostr = std::make_unique<std::ostringstream>();

          const std::string retr_call { "plain_text_auth" };
          std::ostringstream dostr;
          dostr << internal_url
                << "/"
                << retr_call;

          json mon = { { "user" , "mann-k" } , { "password" ,  "Argentina1" } };
          json naked_j = { { "url" ,  dostr.str() } };


          bool b_ret = adapter_strm->results_by_naked_param_async( mon ,
                                                                   naked_j ,
                                                                   ostr.get() );
          if( b_ret )
          { out = json::parse( ostr->str() ); }
          else{ std::cerr  << "..failed....\n"; }

          //std::cerr << ostr->str()
          //          << "\n";

          return b_ret;

}


//---------------------------------------------------------------------------------------------
int main( int argc , char** argv )
{

		//library init and de-init
		curlpp::Cleanup _cleanup;


		try
		{
            json j;
            bool b_ret = retr_db_connection_info( j  , "https://chromatic-centos:7080/mongo/imap2017" );
            if( b_ret ) { std::cout << j.dump( 4 ) << "\n";  }
			//auto curl = make_unique<cci_curl_stream>();
            //curl->debug( false );
			//curl->execute_base_bool_p( "http://localhost:7080/mongo/imap2017/plain_text_auth" ,
                        //                           "user=wiljoh&password=Argentina1" ,
                        //                         &std::cerr );
            //auto ostr = make_unique<std::ostringstream>();
			//json mon;
			//json meta_j = { { "from" , "wiljoh@localhost" } , { "to" , "corny@snaps" } };
			//json naked_j = { { "url" , "http://127.0.0.1:7080/mongo/imap2017/instantiate_atomic_payload" } };
			//json resource_j = { { "resource" , "/opt/imap_spool/staging/201707261829.7a9bee45" } } ;


            //curl->instantiate_atomic_payload( mon ,
			//		                  meta_j ,
			//				  naked_j ,
			//				  resource_j ,
			//				  ostr.get() );
			//json mon = { { "context" , "other_users" } };
                        //json url = { { "url" , "http://localhost:7080//mongo/imap2017/retr_namespace" } };
			//curl->results_by_naked_param_async( mon , url ,  ostr.get() );
			//std::cerr  << ostr->str() << "\n";
            //for( ;; )
            //{
            //    curl->execute_base_bool_g( "http://192.168.1.221:9200" ,
            //                                           ostr.get() );
            //    std::cerr  << ostr->str() << "\n";

             //   std::this_thread::sleep_for( 3s ) ;
            //}




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
