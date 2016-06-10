//cci_opt_utils.h   william k. johnson 2016

#pragma once

//cci
#include <cci_generic.h>

namespace cci_expansion
{

                //forward declarations

                //enumerations


                //aliases


                //services
                template <typename T>
                class cci_base_stopwatch : T
                {
                    typedef typename T  base_timer;

                    public:

                        //ctors
                        explicit cci_basic_stopwatch( bool start );
                        explicit cci_basic_stopwatch( char const* activity = "stopwatch" ,
                                                      bool start = true );
                        cci_basic_stopwatch( std::ostream& log,
                                             char const* activity = "stopwatch",
                                             bool start = true );
                        // ddtor
                        ~cci_basic_stopwatch();


                    private :

                       //attributes
                       char const*cons      tm_activity;
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

}
