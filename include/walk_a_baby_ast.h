//walk_a_baby_ast.h william k. johnson 2015

#pragma once
#ifdef DEBUG
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #pragma GCC diagnostic ignored "-Wunused-variable"
    #pragma GCC diagnostic ignored "-Wunused-function"
    #pragma GCC diagnostic ignored "-Wunused-private-field"
    #pragma GCC diagnostic ignored "-Wswitch"
#endif

//llvm
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/Verifier.h>
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


namespace walk_a_baby
{

        //forwared declarations
        class expr_ast;
        class numeric_expr_ast;
        class variable_ast;
        class binary_ast;
        class prototype_ast;
        class function_ast;
        class call_expr_ast;
        class if_expr_ast;
        class for_expr_ast;

        typedef  std::unique_ptr<expr_ast>              expr_ast_ptr;
        typedef  std::unique_ptr<numeric_expr_ast>      numeric_expr_ast_ptr;
        typedef  std::unique_ptr<variable_ast>          variable_ast_ptr;
        typedef  std::unique_ptr<binary_ast>            binary_ast_ptr;
        typedef  std::unique_ptr<prototype_ast>         prototype_ast_ptr;
        typedef  std::unique_ptr<function_ast>         function_ast_ptr;
        typedef  std::unique_ptr<call_expr_ast>         call_expr_ast_ptr;
        typedef  std::unique_ptr<if_expr_ast>           if_expr_ast_ptr;
        typedef  std::unique_ptr<for_expr_ast>          for_expr_ast_ptr;


        //abstract syntax
        //base
        class expr_ast
        {
            public :

                //dtor
                virtual ~expr_ast() {}
                //llvm ir
                virtual llvm::Value* codegen() = 0;
        };
        //numeric
        class numeric_expr_ast : public expr_ast
        {
            public :

                //ctor
                numeric_expr_ast( double dw_val ) : m_dw_val { dw_val  } {}

                //dtor
                virtual ~numeric_expr_ast() {}

            private :

                //attributes
                double m_dw_val;

            public :

                //accessors-inspectors
                double value() const noexcept { return ( m_dw_val ); }

                //llvm ir
                llvm::Value* codegen() override;

        };
        //variable
        class variable_ast :  public expr_ast
        {
            public :

                //ctor
                variable_ast( const std::string& name ) : m_str_name { name } {}

                //dtor
                virtual ~variable_ast() {}

            private :

                //attributes
                std::string m_str_name;

            public :

                //accessors-inspectors
                std::string name() const noexcept { return ( m_str_name ); }

                //llvm_ir
                llvm::Value* codegen() override;

        };
        //binary
        class binary_ast : public expr_ast
        {
            public :

                //ctor
                binary_ast( char binary_op ,
                            expr_ast_ptr right_hand_side ,
                            expr_ast_ptr left_hand_side
                          ) : m_char_op { binary_op } ,
                              m_rhs_ptr ( std::move( right_hand_side ) )  ,
                              m_lhs_ptr ( std::move( left_hand_side ) )
                {}

                //dtor
                virtual ~binary_ast() {}

            private :

                //attributes
                char m_char_op;
                expr_ast_ptr m_rhs_ptr;
                expr_ast_ptr m_lhs_ptr;

            public :

                //accessors-inspectors
                char bin_op() const noexcept { return ( m_char_op ); }

                //llvm_ir
                llvm::Value* codegen() override;

        };
        //function declaration
        class prototype_ast
        {
            ///prototype_ast- this class represents the "prototype" for a function,
            ///which captures its argument names as well as if it is an operator.
            public :

                //ctor
                explicit prototype_ast( const std::string& name ,
                                        const std::vector<std::string>& args ,
                                        bool is_operator = false ,
                                        unsigned precedence = 0  ) : m_str_name { name } ,
                                                                     m_v_args ( std::move( args ) ) ,
                                                                     m_b_operator { is_operator } ,
                                                                     m_dw_precedence { precedence }
                {}

                //dtor
                virtual ~prototype_ast() {}

            private :

                //attributes
                std::string m_str_name;
                std::vector<std::string> m_v_args;
                bool m_b_operator;
                unsigned m_dw_precedence;

            public :

                //accessors-inspectors
                std::string name() const noexcept { return ( m_str_name ); }
                std::vector<std::string> args() const noexcept { return ( m_v_args ); }
                unsigned precedence() const noexcept{ return ( m_dw_precedence); }

                //services
                bool is_unary_op() const noexcept { return ( m_b_operator && m_v_args.size() == 1 ); }
                bool is_binary_op() const { return ( m_b_operator && m_v_args.size() == 2 ); }
                char operator_name() const
                {
                     //both ops cannot be true or false
                     assert( is_unary_op() || is_binary_op() );

                     return ( m_str_name[m_str_name.size() - 1] );
                }

                //llvm ir
                llvm::Function* codegen();

        };
        //function definition
        class function_ast
        {
            public :

                //ctor
                function_ast( prototype_ast_ptr proto ,
                              expr_ast_ptr body ) : m_ptr_decl ( std::move( proto ) ) ,
                                                    m_ptr_body ( std::move( body ) )
                {}

                //dtor
                virtual ~function_ast() {}

            private :

                //attributes
                prototype_ast_ptr m_ptr_decl;
                expr_ast_ptr      m_ptr_body;

            public :

                //accessors-inspectors


                //;;vm_ir
                virtual llvm::Function* codegen();


        };
        //function call
        class call_expr_ast : public expr_ast
        {
            public :

                //ctor
                call_expr_ast( const std::string& func_callee ,
                               std::vector<expr_ast_ptr>  func_args  )
                                                                        : m_str_callee { func_callee } ,
                                                                          m_v_args( std::move( func_args ) )
                {}

                //dtor
                virtual ~call_expr_ast()
                {}

            private :

                //attributes
                std::string m_str_callee;
                std::vector<expr_ast_ptr> m_v_args;

            public :

                //accessors-inspectors
                std::string callee() const noexcept { return ( m_str_callee ); }

                //llvm ir
                llvm::Value* codegen() override;

        };
        //if-then-else
        class if_expr_ast : public expr_ast
        {

          public :

              //ctor
              if_expr_ast( expr_ast_ptr cond ,
                           expr_ast_ptr then ,
                           expr_ast_ptr _else ) : m_ptr_cond ( std::move( cond ) ) ,
                                                  m_ptr_then ( std::move( then ) ) ,
                                                  m_ptr_else ( std::move( _else ) )
              {}

              //dtor
              virtual ~if_expr_ast()
              {}

         private :

            //attributes
            expr_ast_ptr m_ptr_cond;
            expr_ast_ptr m_ptr_then;
            expr_ast_ptr m_ptr_else;

        public:

            //accessors-inspectors

            //llvm ir
            llvm::Value* codegen() override;

      };
      //for loop
      class for_expr_ast : public expr_ast
      {
        public :

            //ctor
            for_expr_ast( const std::string& var_name ,
                          expr_ast_ptr start ,
                          expr_ast_ptr end ,
                          expr_ast_ptr step ,
                          expr_ast_ptr body ) : m_str_var { var_name } ,
                                                m_ptr_start ( std::move( start ) ) ,
                                                m_ptr_end ( std::move( end ) ) ,
                                                m_ptr_step ( std::move( step ) ) ,
                                                m_ptr_body ( std::move( body ) )
            {}

            virtual ~for_expr_ast()
            {}

        private :

            //attributes
            std::string m_str_var;
            expr_ast_ptr m_ptr_start;

            expr_ast_ptr m_ptr_end;
            expr_ast_ptr m_ptr_step;
            expr_ast_ptr m_ptr_body;

        public :

            //accessors-inspectors

            //llvm ir
            virtual llvm::Value* codegen() override;
      };
      //unary ast
      class unary_expr_ast : public expr_ast
      {
          ///eepression class for a unary operator.
          public :

              //ctor
              explicit unary_expr_ast( char op_code , expr_ast_ptr operand ) : m_c_op { op_code } ,
                                                                               m_ptr_operand ( std::move( operand ) )
              {}

              //dtor
              virtual ~unary_expr_ast()
              {}

            private :

              //attributes
              char m_c_op;
              expr_ast_ptr m_ptr_operand;

            public :

              //accessors-inspectors

              //llvm ir
              virtual llvm::Value* codegen() override;

      };

}
