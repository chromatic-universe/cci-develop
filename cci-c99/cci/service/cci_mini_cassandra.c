//cci_mini_cassandra.c william k. johnson 2015

#include "cci/service/cci_mini_cassandra.h"


///cdra_future_err
//------------------------------------------------------------------------
void cdra_stream_err( cdra_future_ptr future )
{
    //
}

///cdra_create_cluster
//-------------------------------------------------------------------------
cdra_cluster_ptr create_cluster( const char* ip_string )
{
     cdra_cluster_ptr ptr_cluster = cass_cluster_new();
     cass_cluster_set_contact_points( ptr_cluster , ip_string );

     return ptr_cluster;
}


