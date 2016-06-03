//cci_concurrent_run.cpp william k. johnson 2016


#include <cci_numeric_utils.h>
#include <cci_complexity.h>
#include <cci_concurrent_utils.h>
#include <exception>
#include <atomic>

using namespace cci_expansion;

struct func
{
    int& i;
    func( int& i_ ) : i{ i_ } {}

    void operator() ()
    {
        for( unsigned j = 0; j < 1000; ++j )
        {
            ++i;
            std::cout << i;
        }
        std::cout << "\n";
    }
};

std::mutex mtx;
std::deque<std::packaged_task<void()> > tasks;
std::atomic<bool> gb_shutdown_stream{ false };
std::atomic<bool> gb_stream_ready{ false };
std::condition_variable var_ready;

void ofstr_stream_thread()
{
          try
          {
                //we're ready
                {
                    //lock atomic
                    std::unique_lock<std::mutex> lk( mtx );
                    //condition ready
                    gb_stream_ready.store( true );
                }
                //signal
                var_ready.notify_one();

                while( !gb_shutdown_stream )
                {
                    /*std::packaged_task<void()> task;
                    {
                        std::cout << "name\n";

                        std::lock_guard<std::mutex> lk( mtx );
                        if (tasks.empty(  )) { continue; }
                        task = std::move( tasks.front() );
                        tasks.pop_front();
                        ::sleep( 1 );
                        std::cout << "name\n";
                    }
                    task();*/
                    std::cout << "name\n";
                    std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );

                }
                std::cerr << "received shutdown notice...exiting\n";

          }
          catch( const std::exception& e)
          {
                std::cerr << e.what();
          }
}

void shutdown_stream_thread()
{
         std::this_thread::sleep_for( std::chrono::seconds( 15 ) );
         gb_shutdown_stream.store( true );
}


int main( int argc , char* argv[])
{
        //start stream thread
        std::thread othr( ofstr_stream_thread );
        {
            //wait for stream thread init
            //lock atomic
            std::unique_lock<std::mutex> lk( mtx );
            var_ready.wait(  lk ,
                             []
                             {
                                return gb_stream_ready.load();
                             });
            //release lock
        }
        std::cerr << "received stream initialization signal....starting threads\n";
        //start exercise thread
        std::thread sthr( shutdown_stream_thread );
        //join both
        othr.join();
        sthr.join();

        return 0;
}

