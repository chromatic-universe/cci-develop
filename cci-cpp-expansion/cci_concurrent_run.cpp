//cci_concurrent_run.cpp william k. johnson 2016


#include <cci_numeric_utils.h>
#include <cci_complexity.h>
#include <cci_concurrent_utils.h>
#include <exception>
#include <atomic>
#include <algorithm>

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


///concurrency artifacts
std::mutex mtx;
std::deque<std::packaged_task<std::string()> > tasks;
std::atomic<bool> gb_shutdown_stream{ false };
std::atomic<bool> gb_shutdown_tasks{ false };
std::atomic<bool> gb_stream_ready{ false };
std::atomic<bool> gb_tasks_ready{ false };
std::condition_variable var_stream_ready;
std::condition_variable var_tasks_ready;
cci_safe_q<std::string> g_stream_q{};

//stream
void stream_thread_actor()
{
          try
          {
                //we're ready
                {
                    //lock atomic
                    std::unique_lock<std::mutex> lk( mtx );
                    //do initialization here
                    //
                    //condition ready
                    gb_stream_ready.store( true );
                }
                //signal
                var_stream_ready.notify_one();

                do
                {
                    std::cout << "stream\n";
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

                } while ( !gb_shutdown_stream );

                std::cerr << "stream actor speaking: received shutdown notice...exiting\n";


           }
           catch( const std::exception& e )
           {
                std::cerr << e.what();
           }
}

//tasks
void task_thread_actor()
{
          try
          {
                //we're ready
                {
                    //lock atomic
                    std::unique_lock<std::mutex> lk( mtx );
                    //do initialization here
                    //
                    //condition ready
                    gb_tasks_ready.store( true );
                }
                //signal
                var_tasks_ready.notify_one();

                do
                {
                    std::packaged_task<std::string()> task;
                    {

                        std::lock_guard<std::mutex> lk( mtx );
                        std::cout << "packaged task\n";
                        std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );

                        if ( tasks.empty() ) { continue; }
                        /*task = std::move( tasks.front() );
                        tasks.pop_front();
                        ::sleep( 1 );
                        std::cout << "name\n";*/
                    }
                    //task();


                } while ( !gb_shutdown_tasks );

                std::cerr << "task actor speaking: received shutdown notice...exiting\n";

          }
          catch( const std::exception& e)
          {
                std::cerr << e.what();
          }
}

void shutdown_utils_thread()
{
         std::this_thread::sleep_for( std::chrono::seconds( 25 ) );
         //shutdown tasks
         gb_shutdown_tasks.store( true );
         //shutdown stream
         gb_shutdown_stream.store( true );
}

void stream_packet( const std::string& payload )
{

}


/*template<typename funct_t>
std::future<void> post_stream_packet( func_t func )
{
    std::packaged_task<void()> task( func );
    std::future<void> res=task.get_future();
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task));
    return res;
}*/

int main( int argc , char* argv[])
{

            //start stream tthread
            std::thread stream_thr( stream_thread_actor );
            {
                //wait for stream thread init
                //lock atomic
                std::unique_lock<std::mutex> lk( mtx );
                var_stream_ready.wait(    lk ,
                                          []
                                          {
                                             return gb_stream_ready.load();
                                          });
                //release lock
            }
            std::cerr << "received stream initialization signal....\n";

            //start task thread
            std::thread task_thr( task_thread_actor );
            {
                //wait for task thread init
                //lock atomic
                std::unique_lock<std::mutex> lk( mtx );
                var_tasks_ready.wait(    lk ,
                                         []
                                         {
                                            return gb_tasks_ready.load();
                                         });
                //release lock
            }

            std::cerr << "received task initialization signal....\n";
            //start exercise thread
            std::thread sthr( shutdown_utils_thread );
            //join tasks
            task_thr.join();
            //join strea
            stream_thr.join();
            //after stream exits
            sthr.join();

            return 0;
}

