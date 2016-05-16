//chromatic_llvm_diag william k. johnson
//
#pragma once
#pragma GCC diagnostic ignored "-Wswitch"


extern "C"
{
    #include "clang-c/Index.h"

}

//c runtime
#include <sys/stat.h>
#include <cassert>
//c++ standard
#include <memory>
#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <map>
#include <tuple>
#include <stack>
//llvm-clang
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Host.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"


namespace chromatic_llvm_clang
{


    //forward declarations
    class clang_mini_diag;

    //enumerations
    enum class clang_mini : unsigned long
    {
        cm_parse_trans = 0 ,
        cm_diag_count ,
        cm_diag_done ,
        cm_diag_diagnosed ,
        cm_diag_error ,
        cm_acquire_file ,
        cm_make_range ,
        cm_tokenize ,
        cm_tokenized ,
        cm_stream_out ,
        cm_tok_error ,
        cm_set_diag_opts ,
        cm_driver_set_target ,
        cm_set_ast_consumer ,
        cm_set_compiler_mgrs ,
        cm_create_sema ,
        cm_parse_ast ,
        cm_stream_stats ,
        cm_driven ,
        cm_driver_error
    };


    //types
    typedef clang_mini_diag* clang_mini_diag_ptr;
    typedef std::tuple<CXIndex ,
                       std::string ,
                       const char** ,
                       int ,
                       struct CXUnsavedFile* ,
                       unsigned long ,
                       unsigned> translation_args;
    typedef std::tuple<std::string,unsigned long,std::string,std::string> diag_data;
    typedef std::stack<diag_data> diag_stack;
    typedef CXToken* clang_mini_tokens;

    //helpers
    static std::pair<bool,struct stat> file_exists( const std::string& file_name )
    {
        struct stat buf;
        bool b_ret { false };
        stat( file_name.c_str() , &buf ) == 0 ? b_ret = true : b_ret = false;

        return std::make_pair( b_ret , buf );
    }

    //classes
    //abs
    class clang_mini_tool
    {
        public:

            virtual ~clang_mini_tool() {};
            virtual clang_mini perform() = 0;

            virtual clang_mini clang_mini_atom( const unsigned long atom ) = 0;

    };

    //clang_mini_diag
    class clang_mini_diag : public clang_mini_tool
    {
        friend std::ostream & operator<< ( std::ostream &ostr , const clang_mini_diag& cm_diag )
        { return ( ostr << "todo:clang_mini_diag" ); }

        //small utility class to stream out clang diagnostics
        public :

            //ctor
            explicit clang_mini_diag( const std::string& file_name ,
                                      const translation_args args );
            //compare
            bool operator== ( const clang_mini_diag& cm_diag )
            { return ( this->m_str_filename.compare( cm_diag.m_str_filename ) == 0 ); }

            //dtor
            virtual ~clang_mini_diag();


        protected :

            //attributes
            std::string m_str_filename;
            unsigned long m_diagnostic_count;

            clang_mini clang_mini_atom( const unsigned long atom );

        private :

            std::unique_ptr<translation_args> m_ptr_translation;
            CXTranslationUnit m_translation_unit;

        public :

            //accessors-inspectors
            std::string file_name() const noexcept { return ( m_str_filename ); }
            CXTranslationUnit translation_unit() const noexcept{ return ( m_translation_unit ); }
            unsigned long diag_count() const noexcept { return ( m_diagnostic_count ); }
            //mutators
            void file_name( const std::string& file_name ) { m_str_filename = file_name; }
            void translation_unit( const CXTranslationUnit& tu ) { m_translation_unit = tu; }
            void diag_count( const unsigned long dw_diag ) { m_diagnostic_count = dw_diag; }

            //services
            virtual clang_mini perform();


    };

    //clang_mini_lex
    class clang_mini_lex : public clang_mini_tool
    {
        friend std::ostream & operator<< ( std::ostream &ostr , const clang_mini_lex& cm_lex )
        { return ( ostr << "todo:clang_mini_lex" ); }

        //small lexical utility class to enumerate tokens
        public :

            //ctor
            explicit clang_mini_lex( const std::string& file_name ,
                                     const translation_args args  );
            //dtor
            ~clang_mini_lex();

        protected :

            //attributes
            std::string m_str_filename;
            clang_mini_tokens m_tokens;
            unsigned m_dw_tokens;

            //helpers
            clang_mini clang_mini_atom( const unsigned long atom );


        private :

            //attributes
            std::unique_ptr<translation_args> m_ptr_translation;
            CXTranslationUnit m_translation_unit;

        public :

            //accessors-inspectors
            std::string file_name() const noexcept { return ( m_str_filename ); }
            CXTranslationUnit translation_unit() const noexcept{ return ( m_translation_unit ); }
            //mutators
            void file_name( const std::string& file_name ) { m_str_filename = file_name; }
            void translation_unit( const CXTranslationUnit& tu ) { m_translation_unit = tu; }

            virtual clang_mini perform();

    };

    //clang_mini_driver
    class clang_mini_driver  : public clang_mini_tool
    {

        friend std::ostream& operator <<( std::ostream& ostr , const clang_mini_tool& cmt )
        { return ostr << "todo:clang_mini_driver"; }

        public :

            //ctor
            clang_mini_driver( const std::string& file_name );

            virtual ~clang_mini_driver();

        protected :

            //attributes
            std::string m_str_filename;

            //helpers
            clang_mini clang_mini_atom( const unsigned long atom );

        private :

            //attributes
            std::unique_ptr<clang::CompilerInstance>     m_ptr_compiler;
            std::unique_ptr<clang::DiagnosticOptions>    m_ptr_diag_options;

        public :

            //accessors-inspectors
            std::string file_name() const noexcept { return ( m_str_filename ); }

            //helpers
            void tagline( const std::string& nugget ,
                          const std::string& status ,
                          std::ostream* ostr = &std::cout
                        )
            {
                    *ostr << "clang_mini_driver:<\E[32m"
                          << nugget
                          << "> \E[0m"
                          << status
                          << "\n";
            }

            //services
            virtual clang_mini perform();
    };


    //immutable



}
namespace clc = chromatic_llvm_clang;

