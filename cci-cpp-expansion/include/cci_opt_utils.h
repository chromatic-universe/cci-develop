//cci_opt_utils.h   william k. johnson 2016

#pragma once


#include <chrono>

//cci
#include <cci_generic.h>

namespace cci_expansion
{

                //forward declarations

                //enumerations


                //aliases


                //services
                //-------------------------------------------------------------------------------
                template <typename T> class cci_base_stopwatch : T
                {
                    typedef  T  base_timer;

                    public:

                        //ctors
                        explicit cci_base_stopwatch( bool start );
                        explicit cci_base_stopwatch( char const* activity = "stopwatch" ,
                                                      bool start = true );
                        cci_base_stopwatch( std::ostream& log,
                                             char const* activity = "stopwatch",
                                             bool start = true );
                        // ddtor
                        ~cci_base_stopwatch();


                    private :

                       //attributes
                       char const*          m_activity;
                       unsigned             m_lap;
                       std::ostream&        m_log;


                    public :

                      //srvices
                      //last lap time (time of last stop)
                      unsigned lap() const;
                      //predicate: return true if the stopwatch is running
                      bool is_started() const;
                      //show accumulated time, keep running, set/return lap
                      unsigned show( char const* event = "show" );
                      // (re)start a stopwatch, set/return lap time
                      unsigned start( char const* event_namee = "start");
                      // stop a running stopwatch, set/return lap time
                      unsigned stop( char const* event_name = "stop" );
             };
             //-------------------------------------------------------------------------------------
             class cci_timer_base
             {

                    public:

                        //clears the timer
                        cci_timer_base() : m_start( std::chrono::system_clock::time_point::min() )
                        {}

                        ~cci_timer_base() = default;


                    private :

                         //attributes
                         std::chrono::system_clock::time_point m_start;


                    public :

                         //servies

                         //clears the timer
                         void clear() { m_start = std::chrono::system_clock::time_point::min(); }

                         //returns true if the timer is running
                         bool is_started() const noexcept
                         { return (  m_start.time_since_epoch() != std::chrono::system_clock::duration( 0 ) ); }

                         // start the timer
                         void start() { m_start = std::chrono::system_clock::now(); }

                         //get the number of milliseconds since the timer was started
                         unsigned long get_ms()
                         {
                            if ( is_started() )
                            {
                                std::chrono::system_clock::duration diff;
                                diff = std::chrono::system_clock::now() - m_start;

                                return (unsigned)( std::chrono::duration_cast<std::chrono::milliseconds>
                                                     (diff).count() );
                            }

                            return 0;
                         }

             };


}
