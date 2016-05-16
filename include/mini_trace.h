//mini_trace.h william k. johnson 2015

#include <iostream>
#include <sstream>

namespace chromatic_utils
{
    //forward
    class cci_mini_trace;

    //types
    typedef std::ostream* ostr_ptr;
    typedef cci_mini_trace* trace_ptr;

    //enumerations
    enum class trace_t : unsigned long
    {
        tt_base = 0 ,
        tt_extended
    };

    //forward
    class cci_mini_trace
    {
        friend std::ostream& operator << ( std::ostream& ostr , const trace_ptr ptr  )
        {
            trace_ptr->perform();

            return ( ostr << ptr->stream()->str() << std::endl ); }
        }

        public :

            //ctor
            explicit cci_mini_trace( std::ostream& ostr = std::cout ,
                                     const std::string& moniker ,
                                     trace_t tt = tt_base ) : m_ptr_ostr { ostr } ,
                                                              m_str_moniker{ moniker } ,
                                                              m_trace_t { tt }

            {}

            //dtor
            virtual ~cci_mini_trace()
            {
                if( m_ptr_ostr->good() ) { m_ptr_ostr->flush(); }
            }

        protected :

            //attributes
            std::string m_str_moniker;
            trace_t     m_trace_t;

        private :

            //attributes
            ostr_ptr m_ptr_ostr;

        public :

            //accessors-inspectors
            const ostr_ptr stream() { return( m_ptr_ostr ); }
            std::string moniker() const noexcept { return ( m_str_moniker ); }
            trace_t t_type() const noexcept { return ( m_trace_t ); }

            //services
            void perform()
            {
                if( m_ptr_ostr->good() )
                {
                    m_ptr_ostr->str( "" );
                    switch( t_type() ) :
                    {
                        case trace_t::tt_base :
                        {

                        }
                    }
                }
            }

    };
}

