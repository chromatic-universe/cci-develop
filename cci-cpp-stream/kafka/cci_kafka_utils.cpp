//cpp_mini_kafka_utils.cpp     william k. johnson 2016

#include "cci_kafka_stream.h"

using namespace cpp_real_stream;
using namespace rdkafka;

//----------------------------------------------------------------------------------------
void cci_cli_output::failure( tclap::CmdLineInterface& c , tclap::ArgException& e )
{
        m_tmu->color(  stamp_color::red );
        m_tmu->time_stamp();
        std::cerr << "failure in parse args : "
                  << "\n"
                  << e.what()
                  << "\n";
        m_tmu->clear_color();

        exit( 1 );
}

//----------------------------------------------------------------------------------------
void cci_cli_output::usage( tclap::CmdLineInterface& c )
{
        std::cerr << colors[stamp_color::none]
                  << "\n\nusage for cci_mini_kafka_run:\n\n"
                  << m_ptr_ostr->str()
                  << "\n\n";
        std::list<tclap::Arg*> args = c.getArgList();
		for( auto elem : args )
        {
              std::cerr  << "\t"
                         << elem->longID()
                         << "\n\t\t"
                         << "(";
             if( elem->isRequired() ) { std::cerr << colors[stamp_color::red];  }
             std::cerr << elem->getDescription()
                       << colors[stamp_color::none]
                       << ")"
                       << "\n";
        }
       m_tmu->clear_color();
}

//----------------------------------------------------------------------------------------
void cci_cli_output::version( tclap::CmdLineInterface& c )
{
    std::cerr << "cci_mini_kafka_run: version 0.12 william k. johnson 2016\n";
    m_tmu->clear_color();

}

