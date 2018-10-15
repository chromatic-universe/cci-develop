//cci_stream_generic.h   william k. johnson 2016

#pragma once

#include "cci_time_utils.h"
#include "cci_kafka_stream.h"

namespace rdkafka = RdKafka;
using rd_broker_vector =  rdkafka::Metadata::BrokerMetadataVector;
using rd_topic_vector =   rdkafka::Metadata::TopicMetadataVector;
using rd_topic_info_v =  std::vector<std::pair<std::string,unsigned>>;

//for tuple unpcking
//--------------------------------------------------------------------------------
template<typename e>
constexpr typename std::underlying_type<e>::type
to_utype( e enumerator ) noexcept
{
    return static_cast<typename
        std::underlying_type<e>::type>( enumerator );
}

//--------------------------------------------------------------------------------
template<typename stream , typename meta_container>
inline void metadata_stream( stream* strm , const meta_container& vtor )
{
            for( auto elem : vtor )
            {
                   *strm << elem << "\n";
            }
}

//--------------------------------------------------------------------------------
inline void metadata_stream( std::ostream* const ostr ,  const rd_broker_vector* brks )
{
            *ostr << brks->size()
                  << " broker(s):\n";
            for( auto elem : *brks )
            {
                 *ostr << "  broker "
                       << elem->id()
                       << " at "
                       << elem->host()
                       << ":"
                       << elem->port()
                       << "\n";
            }
            *ostr << "\n";
 }

//--------------------------------------------------------------------------------
inline void metadata_stream( std::ostream* const ostr ,  const  rd_topic_vector* topics )
{

            *ostr << topics->size()
                  << " topic(s):\n";
            for( auto elem : *topics )
            {
                 *ostr << "  topic \""
                       << elem->topic()
                       << "\" with  "
                       << elem->partitions()->size()
                       << " partition(s)"
                       << "\n";
            }
            *ostr << "\n";
 }



//--------------------------------------------------------------------------------
template <typename stream , typename metadata>
inline void stream_metadata_header( stream* ostr ,
                                    const metadata* meta ,
                                    const std::string& preamble )
{
            *ostr << "metadata for "
                  << preamble
                  << "\n"
                  << "\tservice origin id "
                  << meta->orig_broker_id()
                  << "\n"
                  << "\tservice origin name "
                  << meta->orig_broker_name()
                  << "\n\n";

}

//--------------------------------------------------------------------------------
inline std::unique_ptr<rd_topic_info_v>  metadata_naked_stream( const  rd_topic_vector* topics )
{
            auto v_topics = std::make_unique<rd_topic_info_v>();

            std::pair<std::string,unsigned> pr;
            for( auto elem : *topics )
            {
                       pr.first = elem->topic();
                       pr.second = elem->partitions()->size();
                       v_topics->push_back( pr );
            }

            return v_topics;
 }

//--------------------------------------------------------------------------------
template <typename stream , typename metadata>
inline void stream_metadata( stream* ostr ,
                             const metadata* meta )
{
            stream_metadata_header( ostr , meta );
}

//--------------------------------------------------------------------------------
inline void stream_metadata( std::ostream* ostr ,
                             const rdkafka::Metadata* meta )
{
            stream_metadata_header( ostr , meta , "kafka server at " );

            metadata_stream( ostr , meta->brokers() );
}



