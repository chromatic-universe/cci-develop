//cci_concurrent_utils.h   william k. johnson 2016

#pragma once

//stl
#include <thread>
//cci
#include <cci_generic.h>

using namespace std::literals;

namespace cci_expansion
{

           //forward declarations

           //enumerations
           enum class dtor_action { join , detach };

           //aliases


           //services
           //
           //-------------------------------------------------------------------------------------
           template<typename T>
           class scoped_thread
           {

                    public :

                        //ctor
                        explicit scoped_thread( T& t_ ) :  m_t ( std::move(  t_ ) )
                        {
                            if( m_t.joinable() )
                            {
                                throw std::logic_error( "no thread..." );
                            }
                        }
                       //dtor
                       ~scoped_thread() {  m_t.join();  }

                       //no copy
                       scoped_thread( const scoped_thread& st ) = delete;
                       //no  assign
                       scoped_thread& operator= ( const scoped_thread&  ) = delete;


                    private :

                       //attributes
                       //declare last for tls safety
                       T m_t;


           };
           //-------------------------------------------------------------------------------------
           template<typename T>
           class thread_raii
           {
                    //single path for thread join
                    public :


                        //ctor
                        explicit thread_raii( T&  t_  ,
                                              dtor_action act ) :  m_action { act } ,
                                                                   m_t ( std::move( t_ ) )
                        {}
                        //dtor
                        ~thread_raii()
                        {
                            if( m_t.joinable() )
                            {
                                m_action == dtor_action::join ? m_t.join() : m_t.detach();
                            }
                        }

                        //no copy
                        thread_raii( const thread_raii& ctg ) = delete;
                        //no assign
                        thread_raii& operator= (  const thread_raii& ctg ) = delete;

                    private :

                       //attributes
                       dtor_action m_action;
                       //declare last for tls safety
                       T   m_t;

                    public :

                        //accessors/inspectors
                        T& get() { return m_t; }

          };
          //-------------------------------------------------------------------------------------
          template<typename F , typename... Ts>
          inline auto true_async( F&& f , Ts&&... params  )
          {
                  //wrapper that makes async policy default
                  return std::async( std::launch::async ,
                                     std::forward<F> ( f ) ,
                                     std::forward<Ts> ( params )...);
          }
}
