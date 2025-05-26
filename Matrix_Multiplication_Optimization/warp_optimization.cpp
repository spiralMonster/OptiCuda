#include "warp_optimization.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

char WarpOptimization::ID = 0;

bool WarpOptimization::runOnFunction(Function &F) {
    if (!F.getName().contains("matmul"))
        return false;

    LLVMContext &Ctxt = F.getContext();
    IRBuilder<> Builder(Ctxt);
    Module *M = F.getParent();
    bool modified = false;

    FunctionType *ShuffleTy = FunctionType::get(
        Type::getInt32Ty(Ctxt),  // return: i32
        {
            Type::getInt32Ty(Ctxt), // mask
            Type::getInt32Ty(Ctxt), // val
            Type::getInt32Ty(Ctxt), // delta
            Type::getInt32Ty(Ctxt)  // warp width
        },
        false);

    FunctionCallee shuffle_func = M->getOrInsertFunction(
        "llvm.nvvm.shfl.sync.down.i32", ShuffleTy);

    for (auto &BB : F) {
        for (auto &I : BB) {
            if (auto *load = dyn_cast<LoadInst>(&I)) {
                if (load->getType()->isFloatTy()) {
                    Builder.SetInsertPoint(load);

                    Value *intVal = Builder.CreateBitCast(load, Builder.getInt32Ty());

                    Value *mask = Builder.getInt32(0xFFFFFFFF);
                    Value *val = intVal;
                    Value *delta = Builder.getInt32(1);
                    Value *width = Builder.getInt32(32);

                    Value *args[] = {mask, val, delta, width};

                    Value *shuffled = Builder.CreateCall(shuffle_func, args);

                    Value *float_shuffled = Builder.CreateBitCast(shuffled, Builder.getFloatTy());

                    load->replaceAllUsesWith(float_shuffled);
                    modified = true;
                }
            }
        }
    }
    return modified;
}

static RegisterPass<WarpOptimization> X("warp-opt", "Warp level optimization of matrix multiplication", false, false);

