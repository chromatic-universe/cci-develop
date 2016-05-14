//cci_mini_rpc apache thrift idl   william k. johnson

//common boilerplate and marshaling
include "shared.thrift"

//barebones exception
//------------------------------------------------------------------------
exception invalid_clang_op
{
       1: i32 what_op ,
       2: string wat
}

//------------------------------------------------------------------------
service cci_mini_clang_rpc extends shared.SharedService
{
       //method invocation
       //cci_mini_diag from cci_llvm_clang
       //index_module->cpp filename , we use clang semantics
       //for args names
       //returns string buffer of diagnostic info
       //see cci_mini_diag.py
       string perform_diag( 1:string index_module )
}
