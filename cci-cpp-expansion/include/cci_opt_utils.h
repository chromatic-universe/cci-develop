//concurrenti_utils.h  pimpl  william k. johnson 2016

#include <memory>
#include <chrono>

namespace cci_expansion
{
        //forward declarations
        class timer_base_impl;

        //aliases
        using  time_point_t = std::chrono::system_clock::time_point;
        using  tbi_ptr = timer_base_impl*;

        //-------------------------------------------------------------------------------
        class cci_base_stopwatch
        {
             public:

                  //ctors
                  cci_base_stopwatch() ;

                  // ddtor
                  virtual ~cci_base_stopwatch() = 0;

                  //srvices
                  //last lap time (time of last stop)
                  virtual time_point_t lap() const = 0;
                  //predicate: return true if the stopwatch is running
                  virtual bool is_started() const noexcept = 0;
                  //show accumulated time, keep running, set/return lap
                  virtual time_point_t show() = 0;
                  // (re)start a stopwatch, set/return lap time
                  virtual void start() = 0;
                  // stop a running stopwatch, set/return lap time
                  virtual time_point_t stop() = 0;
                  //get the number of milliseconds since the timer was started
                  virtual unsigned long duration_ms() = 0;

        };

        //services
        class cci_timer_base : public cci_base_stopwatch
        {

            public :

                //ctor
                explicit  cci_timer_base( bool start = true );
                //dtor
                virtual ~cci_timer_base() = default;
                //no  copy
                cci_timer_base( const cci_timer_base& ctb ) = delete;
                //no assign
                cci_timer_base&  operator=( const cci_timer_base& ctb ) = delete;

            private :

                //atttributes
                //implementation
                //class timer_base_impl;
                std::unique_ptr<timer_base_impl>  m_tbi;

            public :

                //accessors-inspectors
                //last lap time (time of last stop)
                virtual time_point_t lap() const noexcept;
                tbi_ptr watch_ptr() { return m_tbi.get(); }

                //services
                //predicate: return true if the stopwatch is running
                virtual bool is_started() const noexcept;
                //show accumulated time, keep running, set/return lap
                virtual time_point_t show();
                // (re)start a stopwatch, set/return lap time
                virtual void start();
                // stop a running stopwatch, set/return lap time
                virtual time_point_t stop();
                //get the number of milliseconds since the timer was started
                unsigned long duration_ms();
                //clears the timer
                virtual void clear();

        };

}

