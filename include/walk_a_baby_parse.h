//walk_a_baby_parse.h william k. johnson 2015

#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-private-field"
#pragma GCC diagnostic ignored "-Wswitch"


//llvm
#include "llvm/Analysis/Passes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/Verifier.h>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
//c++ standard
#include <cctype>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <walk_a_baby_lex.h>
#include <walk_a_baby_ast.h>
//adaptive coummnication environment
#include <ace/Log_Msg.h>
#include <ace/Trace.h>

extern "C"
{
    double printd(double X);
}

namespace walk_a_baby
{

        //forward declarations
        class walk_a_baby_parse;

        //types
        typedef std::vector<std::string> v_str;
        typedef v_str* v_str_ptr;
        typedef walk_a_baby_parse* walk_a_baby_parse_ptr;
        typedef llvm::Module* module_ptr;
        typedef llvm::IRBuilder<>* ir_builder_ptr;
        typedef std::map<std::string, llvm::Value*> symbol_table;
        typedef symbol_table* symbol_table_ptr;
        typedef llvm::legacy::FunctionPassManager* pass_mgr_ptr;
        typedef llvm::ExecutionEngine* exec_engine_ptr;

        //parser
        class walk_a_baby_parse
        {

            public :

                //ctors
                explicit walk_a_baby_parse();

                //dtor
                virtual ~walk_a_baby_parse();


           protected :

                //attributes
                static std::unique_ptr<walk_a_baby_lex> m_ptr_lex;

                ///binopPrecedence - this holds the precedence for each
                ///binary operator that is defined.
                static std::map<char, int> bin_op_precedence;

                //helpers


            private :

                //no assign
                const walk_a_baby_parse& operator= ( const walk_a_baby_parse& wabl );
                //copy
                walk_a_baby_parse( const walk_a_baby_parse& wapb );

                //attributes

            public :

                //accessors-inspectors
                static walk_a_baby_lex_ptr lex() { return ( m_ptr_lex.get() );  }

                //mutators


                //services
                static int next_token();
                static expr_ast_ptr parse_expression();
                static expr_ast_ptr parse_paren_expr();
                static expr_ast_ptr parse_identifier_expr();
                static expr_ast_ptr parse_primary();
                static expr_ast_ptr parse_numeric_expr();
                static expr_ast_ptr parse_bin_op_rhs( int expr_prec ,
                                                      expr_ast_ptr lhs );
                static function_ast_ptr parse_definition();
                static prototype_ast_ptr parse_prototype();
                static prototype_ast_ptr parse_extern();
                static function_ast_ptr parse_top_level_expr();
                static expr_ast_ptr parse_if_expr();
                static expr_ast_ptr parse_for_expr();
                static expr_ast_ptr parse_unary_expr();

                void handle_definition();
                void handle_extern();
                void handle_top_level_expression();

                static int get_tok_precedence();

                //immutable
                static int current_lex_token;

        };

        //driver
        class walk_a_baby_driver
        {

            friend std::ostream& operator << ( std::ostream& ostr , const walk_a_baby_driver& wabd  )
                          { return ( ostr << "todo=walk-a-baby-driver" ); }

            public :

                  //ctor
                  walk_a_baby_driver();

                  //dtor
                  virtual ~walk_a_baby_driver();

            protected :

                 //

            private :

                //attributes , initialization order here is significant
                static std::unique_ptr<v_str> m_v_filenames;
                static std::unique_ptr<walk_a_baby_parse> m_baby_parse;
                static std::unique_ptr<symbol_table> m_symbol_table;
                //static std::unique_ptr<llvm::Module> m_module;
                static module_ptr m_ptr_module;
                static exec_engine_ptr m_ptr_exec;
                static std::unique_ptr<llvm::IRBuilder<>> m_ir_builder;
                static pass_mgr_ptr m_pass_mgr;

                //no copy
                walk_a_baby_driver( const walk_a_baby_driver& wabd );
                //no assign
                const walk_a_baby_driver& operator= ( const walk_a_baby_driver& wabd );

            public :

                //accessors-inspectors
                v_str_ptr file_name() const noexcept { return ( m_v_filenames.get() ); }
                static walk_a_baby_parse_ptr parse() { return ( m_baby_parse.get() ); }
                static module_ptr module() { return ( m_ptr_module ); }
                static ir_builder_ptr ir_builder() { return ( m_ir_builder.get() ); }
                static symbol_table_ptr symbols() { return ( m_symbol_table.get() ); }
                static pass_mgr_ptr pass_mgr() { return ( m_pass_mgr ); }
                static exec_engine_ptr engine() { return ( m_ptr_exec ); }
                //mutators
                void file_name( const v_str sources ) { *file_name() = sources;  }
                static void module( module_ptr ptr ) { m_ptr_module = ptr; }
                static void engine( exec_engine_ptr ptr ) { m_ptr_exec = ptr; }
                static void pass_mgr( pass_mgr_ptr ptr ) { m_pass_mgr = ptr; }

                //helpers
                static llvm::Value* error_v( const std::string& str ) { std::cerr << str << "\n"; return ( 0 ); }
                static void init_pipeline();

                //services
                static void perform();


        };
}

