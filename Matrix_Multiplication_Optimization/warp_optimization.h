#ifndef WARP_OPTIMIZATION_H
#define WARP_OPTIMIZATION_H

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"

using namespace llvm;

struct WarpOptimization : public FunctionPass {
  static char ID;
  WarpOptimization() : FunctionPass(ID) {}
  bool runOnFunction(Function &F) override;
};

#endif

