//cci_concurrent_impl.h   william k. johnson  2016


#include  "opt_utils.h"

using namespace cci_expansion;


//cci_timer_base
//---------------------------------------------------------------------------------------
cci_timer_base::cci_timer_base( bool start ) : m_tbi( new timer_base_impl( start ) )
{
        //
}

//---------------------------------------------------------------------------------------
bool cci_timer_base::is_started() const noexcept
{
        return m_tbi->is_started();
}

//---------------------------------------------------------------------------------------
time_point_t cci_timer_base::lap() const noexcept
{
        return m_tbi->lap();
}

//---------------------------------------------------------------------------------------
time_point_t cci_timer_base::show()
{
        return m_tbi->show();
}

//----------------------------------------------------------------------------------------
void cci_timer_base::start()
{
        return m_tbi->start();
}

//---------------------------------------------------------------------------------------
time_point_t cci_timer_base::stop()
{
        return m_tbi->stop();
}

//----------------------------------------------------------------------------------------
void cci_timer_base::clear()
{
        return m_tbi->clear();
}


//---------------------------------------------------------------------------------------
unsigned long cci_timer_base::duration_ms()
{
        return m_tbi->duration_ms();
}

//timer_base_impl
//----------------------------------------------------------------------------------------
timer_base_impl::timer_base_impl( bool start ) : m_start( std::chrono::system_clock::time_point::min() )
{
        if( start ) { this->start(); }
}

//---------------------------------------------------------------------------------------
bool timer_base_impl::is_started() const noexcept
{
        return ( m_start.time_since_epoch() != std::chrono::system_clock::duration( 0 ) );
}

//------------------------------------------------------------------------------------------
time_point_t timer_base_impl::lap() const noexcept
{
        return m_start;
}

//------------------------------------------------------------------------------------------
time_point_t timer_base_impl::show()
{
        return m_start;
}

//------------------------------------------------------------------------------------------
time_point_t timer_base_impl::stop()
{
        clear();
        return m_start;
}

//------------------------------------------------------------------------------------------
void timer_base_impl::start()
{
        m_start = std::chrono::system_clock::now();
}

//------------------------------------------------------------------------------------------
void timer_base_impl::clear()
{
        m_start = std::chrono::system_clock::time_point::min();
}

//------------------------------------------------------------------------------------------
unsigned long timer_base_impl::duration_ms()
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







