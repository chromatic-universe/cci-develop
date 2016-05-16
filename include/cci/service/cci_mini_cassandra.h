//cci_mini_cassandra.h william k. johnson 2015
//cassandra walk-a-baby

#pragma once

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cassandra.h"

//adt
struct basic_ {
  cass_bool_t bln;
  cass_float_t flt;
  cass_double_t dbl;
  cass_int32_t i32;
  cass_int64_t i64;
};

//types
typedef struct basic_   basic;
typedef CassFuture*     cdra_future_ptr;
typedef CassCluster*    cdra_cluster_ptr;
typedef CassError       cass_error;

//utils
//
///cdra_future_err
//------------------------------------------------------------------------
extern void cdra_stream_err( cdra_future_ptr future );
///cdra_create_cluster
//-------------------------------------------------------------------------
extern cdra_cluster_ptr create_cluster( const char* ip_string );
