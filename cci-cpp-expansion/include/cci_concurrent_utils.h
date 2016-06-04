//cci_concurrent_utils.h   william k. johnson 2016
//c++14

#pragma once

//stl
#include <thread>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <future>
#include <utility>
#include <condition_variable>

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
           class scoped_thread
           {

                    public :

                        //ctor
                        explicit scoped_thread(  std::thread  t_ ) :  m_t ( std::move(  t_ ) )
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
                       std::thread m_t;


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
          inline
          std::future<typename std::result_of<F(Ts...)>::type>
          true_async( F&& f , Ts&&... params  )
          {
                  //wrapper that makes async policy default
                  return std::async( std::launch::async ,
                                     std::forward<F> ( f ) ,
                                     std::forward<Ts> ( params )...);
          }
          //--------------------------------------------------------------------------------------
          template <typename T>
          class cci_safe_q
          {
                    public :

                        //ctor
                        cci_safe_q() = default;
                        //copy
                        cci_safe_q( const cci_safe_q& csq )
                        {
                            std::lock_guard<std::mutex> lk( csq.m_mutx );
                            m_data_q = csq.m_data_q;
                        }
                        //no assign
                        cci_safe_q& operator= ( const cci_safe_q& csq ) = delete;

                    private :

                        //attributes
                        //mutabe mutex for copy constructor and inspector
                        mutable std::mutex          m_mutx;
                        std::queue<T>               m_data_q;
                        std::condition_variable     m_data_cond;


                    public :

                        //accessors-inspectors
                        bool empty() const noexcept
                        {
                            std::lock_guard<std::mutex> lk( m_mutx );
                            return m_data_q.empty();
                        }

                        //services
                        void push_q( T value_new )
                        {
                            std::lock_guard<std::mutex> lk( m_mutx );
                            m_data_q.push( value_new );
                            m_data_cond.notify_one();
                        }

                        void wait_and_pop( T& value )
                        {
                            std::lock_guard<std::mutex> lk( m_mutx );
                            m_data_cond.wait( lk ,
                                              [this] { return !m_data_q.empty();} );
                            value = m_data_q.front();
                            m_data_q.pop();
                        }

                        std::shared_ptr<T> wait_and_pop()
                        {
                            std::lock_guard<std::mutex> lk( m_mutx );
                             m_data_cond.wait( lk ,
                                              [this] { return !m_data_q.empty();} );
                            std::shared_ptr<T> res ( std::make_shared<T> ( m_data_q.front() ) );
                            m_data_q.pop();

                            return res;

                        }

                        bool try_pop( T& value )
                        {
                             std::lock_guard<std::mutex> lk( m_mutx );
                             m_data_cond.wait( lk ,
                                              [this] { return !m_data_q.empty();} );

                             if( m_data_q.empty() ) { return false; }

                             value = m_data_q.front();
                             m_data_q.pop();

                             return true;
                        }

                        std::shared_ptr<T> try_pop()
                        {
                             std::lock_guard<std::mutex> lk( m_mutx );
                             m_data_cond.wait( lk ,
                                              [this] { return !m_data_q.empty();} );
                            if( m_data_q.empty() ) { return  std::shared_ptr<T>(); }

                            std::shared_ptr<T> res ( std::make_shared<T> ( m_data_q.front() ) );
                            m_data_q.pop();

                            return res;
                        }

          };
}
