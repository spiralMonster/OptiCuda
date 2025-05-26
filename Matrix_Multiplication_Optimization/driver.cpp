#include "warp_optimization.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

int main(int argc, char **argv) {
  InitLLVM X(argc, argv);
  LLVMContext Context;

  SMDiagnostic Err;
  auto M = parseIRFile("normal_matmul.ll", Err, Context);
  if (!M) {
    Err.print(argv[0], errs());
    return 1;
  }

  legacy::PassManager PM;
  PM.add(new WarpOptimization());

  PM.run(*M);

  std::error_code EC;
  raw_fd_ostream out("optimized_matmul.ll", EC, sys::fs::OF_None);
  M->print(out, nullptr);

  return 0;
}

