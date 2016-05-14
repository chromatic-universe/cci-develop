#pragma once

//kafka
#include <librdkafka/rdkafkacpp.h>
//c++ std
#include <chrono>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>
#include <type_traits>
//c runtime
#include <ctime>
#include <cstdint>
#include <cassert>
#include <sys/types.h>
#include <unistd.h>
//cci
#include "cci_time_utils.h"
#include "cci_stream_generic.h"

//cmommand line
#include <tclap/CmdLine.h>

namespace rdkafka = RdKafka;
namespace tclap = TCLAP;

namespace cpp_real_stream
{

        //forward declarations
        class cci_kafka_consumer;
        class kf_callback_mogrifier;
        class cci_kafka_preamble;
        class delivery_report_cb;
        enum class kafka_callback : char;


        //aliases
        using cci_kafka_broker = std::tuple<std::string,int,int>;
        using broker_ptr = std::unique_ptr<cci_kafka_broker>;
        using consumer_ptr = cci_kafka_consumer*;
        using kafka_brokers = std::vector<broker_ptr>;
        using brokers_ptr = kafka_brokers*;
        using rd_consumer_ptr = rdkafka::Consumer*;
        using rd_producer_ptr = rdkafka::Producer*;
        using topic_ptr = rdkafka::Topic*;
        using callback_dictionary = std::map<kafka_callback,std::string>;
        using kafka_preamble_ptr = cci_kafka_preamble*;
        using kafka_mogrifier_ptr = kf_callback_mogrifier*;
        using delivery_report_ptr = delivery_report_cb*;
        using switch_arg = tclap::SwitchArg;
        using value_arg = tclap::ValueArg<std::string>;
        using cmd_line = tclap::CmdLine;

        //enumerations
        enum class broker_fields : char
        {
            bf_destination ,
            bf_port ,
            bf_partition
        };
        enum class kafka_callback : char
        {
            kc_sock ,
            kc_open ,
            kc_event ,
            kc_consumer
        };

        //helpers
        class cci_cli_output : public tclap::StdOutput
        {
            protected :

                std::ostringstream* m_ptr_ostr;
                std::unique_ptr<time_utils> m_tmu;

            public :

                //ctor
                cci_cli_output( std::ostringstream* ostr_ptr ) : m_ptr_ostr { ostr_ptr } ,
                                                           m_tmu( std::make_unique<time_utils>( stamp_color::blue ) )
                {}
                //dtor
                ~cci_cli_output() = default;

                virtual void failure( tclap::CmdLineInterface& c , tclap::ArgException& e );
                virtual void usage( tclap::CmdLineInterface& c );
                virtual void version( tclap::CmdLineInterface& c );
        };

        //services
        //--------------------------------------------------------------------------------
        class cci_kafka_preamble
        {

            public :

                //ctor
                explicit cci_kafka_preamble( std::unique_ptr<kafka_brokers>& brokers );

                cci_kafka_preamble( cci_kafka_preamble&& ckc ) = default;
                cci_kafka_preamble& operator= ( cci_kafka_preamble&& ckc ) = default;
                //copy
                cci_kafka_preamble( const cci_kafka_preamble& ckc ) = default;
                cci_kafka_preamble& operator= ( const cci_kafka_preamble& ckc ) = default;
                //use unary bool compare
                bool operator!() const { return !m_b_valid; }
                //disable bitwise compare
                friend bool operator== ( const cci_kafka_preamble &a , const cci_kafka_preamble &b ) = delete;
                friend bool operator!= ( const cci_kafka_preamble &a , const cci_kafka_preamble &b ) = delete;

                //dtor
                virtual ~cci_kafka_preamble();

           private :

                //attributes
                std::unique_ptr<time_utils> m_tut;
                std::unique_ptr<kf_callback_mogrifier> m_mogrifier;
                bool m_b_valid;

                //helpers
                void config_metadata();
                bool config_debug();
                void config_callbacks();

                //rdkafka
                static rdkafka::Conf *gconf ;

            protected :

                //attributes
                std::unique_ptr<kafka_brokers>  m_brokers;
                std::unique_ptr<time_utils>     m_tmu;
                bool                            m_b_events;

            public :

                //accessors-inspectors
                brokers_ptr brokers()  noexcept { return m_brokers.get(); }
                kafka_mogrifier_ptr mogrifier() { return m_mogrifier.get(); }
                static rdkafka::Conf* g_config() { return gconf; }

                //mutators
                void events( bool ev ) { m_b_events = ev; }

                //ummutable
                static std::string  crs_metadata_key;
                //cli
                static std::unique_ptr<tclap::CmdLine> ccmd;
                //immutable cli
                static std::unique_ptr<switch_arg>          debug_switch;
                static std::unique_ptr<switch_arg>          consumer_switch;
                static std::unique_ptr<switch_arg>          producer_switch;
                static std::unique_ptr<value_arg>           topic_name;
                static std::unique_ptr<value_arg>           topic_metadata;
                static std::unique_ptr<value_arg>           the_brokers;

                //services
                void init();

        };

        class delivery_report_cb : public rdkafka::DeliveryReportCb
        {
              public:

                  delivery_report_cb() : m_tmu(  new time_utils( stamp_color::green ) )
                  {}
                  void dr_cb ( rdkafka::Message &message );

              protected :

                  std::unique_ptr<time_utils> m_tmu;
        };

        //we could encapsulate all of the rdkafka callbacks
        //nicely here , except the 'open' and 'socket' callbacks
        //have ambigous signatureswhich can't be resolved by
        //the vmt.we have to use composition for these.
        class kf_callback_mogrifier : public rdkafka::EventCb ,
                                      public rdkafka::ConsumeCb
        {
            public :

                //ctor
                kf_callback_mogrifier( std::ostream* ostr ,
                                       std::unique_ptr<time_utils>& tu ,
                                       bool exit_eof = false ,
                                       bool run = false
                                     )
                                     : m_eof { exit_eof } ,
                                       m_run { run } ,
                                       m_ostr( std::move( ostr ) ) ,
                                       m_tym( std::move( tu ) ) ,
                                       m_show_log { true } ,
                                       m_delivery( new delivery_report_cb )
                {
                    assert( m_ostr );
                    assert( m_tym.get() );
                }

                //dtor
                virtual ~kf_callback_mogrifier() = default;

                //no copy
                kf_callback_mogrifier( const kf_callback_mogrifier& kcm ) = delete;
                //no assign
                const kf_callback_mogrifier& operator= ( const kf_callback_mogrifier& kcm ) = delete;

            private :

                //attributes
                bool m_eof;
                bool m_run;

            protected :

                //attributes
                std::ostream*                       m_ostr;
                std::unique_ptr<time_utils>         m_tym;
                bool                                m_show_log;
                std::unique_ptr<delivery_report_cb> m_delivery;

                //helpers
                virtual void perform_event( rdkafka::Event& event );
                virtual void perform_consumption( rdkafka::Message &message , void *opaque );

            public :

                //accessors-inspectors
                const time_utils_ptr tym() { return m_tym.get(); }
                bool exit_on_eof() const noexcept { return m_eof; }
                bool run() const noexcept { return m_run; }
                bool show_log() const noexcept { return m_show_log; }
                delivery_report_ptr delivery_ptr() { return m_delivery.get(); }

                //mutators
                void raw_ostr( std::ostream* ostr )
                {  m_ostr = ostr; }
                void exit_on_eof( bool eof ) { m_eof = eof; }
                void run( bool rn ) { m_run = rn; }
                void show_log( bool show ) { m_show_log = show; }

                //services
                virtual void   event_cb ( rdkafka::Event &event ) override;
                virtual void   consume_cb ( rdkafka::Message &message , void *opaque ) override;

                //immutable
                static callback_dictionary k_callbacks;

        };

        //--------------------------------------------------------------------------------
        class cci_kafka_consumer
        {

            public :

                //ctor
                explicit cci_kafka_consumer( kafka_preamble_ptr ptr_preamble ,
                                             bool events = false );
                //move
                cci_kafka_consumer( cci_kafka_consumer&& ckc ) = default;
                cci_kafka_consumer& operator= ( cci_kafka_consumer&& ckc )  = default;
                //copy
                cci_kafka_consumer( const cci_kafka_consumer& ckc ) = default;
                cci_kafka_consumer& operator= ( const cci_kafka_consumer& ckc ) = default;
                //use unary bool compare
                bool operator!() const { return !m_ptr_rd; }
                //disable bitwise compare
                friend bool operator== ( const cci_kafka_consumer &a , const cci_kafka_consumer &b ) = delete;
                friend bool operator!= ( const cci_kafka_consumer &a , const cci_kafka_consumer &b ) = delete;

                //dtor
                virtual ~cci_kafka_consumer();

            private :

                    //helpers
                    bool config_library_consumer();

                    //single topic
                    static rdkafka::Conf *topic_conf;

            protected :

                    //attributes
                    kafka_preamble_ptr              m_preamble;
                    std::unique_ptr<time_utils>     m_tmu;
                    rd_consumer_ptr                 m_ptr_rd;
                    std::string                     m_str_topic;
                    topic_ptr                       m_ptr_topic;
                    int                             m_cur_partition;
                    int64_t                         m_start_offset;
                    bool                            m_b_events;

            public :

                    //accessors-inspectors
                    rd_consumer_ptr rd_consumer() noexcept { return m_ptr_rd; }
                    std::string topic_str() const noexcept { return m_str_topic; }
                    int64_t start_offset() const noexcept { return m_start_offset; }
                    bool events() const noexcept { return m_b_events; }
                    //mutators
                    void start_offset( const int64_t start ) { m_start_offset = start; }
                    void events( bool ev ) { m_b_events = ev; }

                    //services
                    bool config_topic( const std::string& topic );
                    void consume();

                    //immutable
                    static bool         crs_run;
                    static bool         crs_exit_eof;
                    static int          crs_eof_cnt;
                    static int          crs_partition_cnt;
                    static int          crs_verbosity;
                    static long         crs_msg_cnt;
                    static int64_t      crs_msg_bytes;

        };
        //--------------------------------------------------------------------------------
        class cci_kafka_producer
        {

             public :

                //ctor
                explicit cci_kafka_producer( kafka_preamble_ptr ptr_preamble ,
                                             bool events = false );

                //move
                cci_kafka_producer( cci_kafka_producer&& ckc ) = default;
                cci_kafka_producer& operator= ( cci_kafka_producer&& ckc )  = default;
                //copy
                cci_kafka_producer( const cci_kafka_producer& ckc ) = default;
                cci_kafka_producer& operator= ( const cci_kafka_producer& ckc ) = default;
                //use unary bool compare
                bool operator!() const { return !m_ptr_rd; }
                //disable bitwise compare
                friend bool operator== ( const cci_kafka_producer &a , const cci_kafka_producer &b ) = delete;
                friend bool operator!= ( const cci_kafka_producer &a , const cci_kafka_producer &b ) = delete;

                //dtor
                virtual ~cci_kafka_producer();

             private :

                    //helpers
                    bool config_library_producer();

                    //single topic
                    static rdkafka::Conf *topic_conf;

             protected :

                    //attributes
                    kafka_preamble_ptr              m_preamble;
                    std::unique_ptr<time_utils>     m_tmu;
                    rd_producer_ptr                 m_ptr_rd;
                    std::string                     m_str_topic;
                    topic_ptr                       m_ptr_topic;
                    int                             m_cur_partition;
                    bool                            m_b_events;

             public :

                    //accessors-inspectors
                    rd_producer_ptr rd_producer() noexcept { return m_ptr_rd; }
                    std::string topic_str() const noexcept { return m_str_topic; }
                    bool events() const noexcept { return m_b_events; }
                    time_utils* tutils() { return m_tmu.get();  }
                    topic_ptr topic() { return m_ptr_topic; }
                    //mutators
                    void events( bool ev ) { m_b_events = ev; }

                    //services
                    bool config_topic( const std::string& topic );
                    void produce();


        };

        void gen_kafka_meta_stream( const std::string& broker  ,
                                    const std::string& topic ,
                                    int partition ,
                                    kafka_preamble_ptr preamble = nullptr );



};

namespace crstream = cpp_real_stream;
