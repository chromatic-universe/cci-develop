//cci_opt_utils.h   william k. johnson 2016

#pragma once


#include <chrono>

//cci
#include <cci_opt_utils.h>

namespace cci_expansion
{

               //forward declarations

               //enumerations

               //aliases

               //services
               class timer_base_impl  :  public cci_base_stopwatch
               {

                        public:

                            //clears the timer
                            explicit timer_base_impl( bool start  = true );
                            //dtor
                            virtual ~timer_base_impl() = default;


                        private :

                             //attributes
                             time_point_t  m_start;

                        public :

                             //servies
                             virtual time_point_t lap() const noexcept;
                             virtual time_point_t show();
                             virtual time_point_t stop();

                             //clears the timer
                             virtual void clear();
                             //returns true if the timer is running
                             virtual bool is_started() const noexcept;

                             // start the timer
                             virtual void start();

                             //get the number of milliseconds since the timer was started
                             virtual unsigned long duration_ms();
               };

}
