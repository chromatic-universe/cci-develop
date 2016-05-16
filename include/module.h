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


static llvm::Module* baby_module = new  llvm::Module( "walk_a_baby_module", llvm::getGlobalContext() );


