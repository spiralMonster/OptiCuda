; ModuleID = 'normal_matmul.ll'
source_filename = "normal_matmul.cu"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.dim3 = type { i32, i32, i32 }

; Function Attrs: noinline norecurse optnone uwtable
define dso_local void @__device_stub__matmul(ptr noundef %0, ptr noundef %1, ptr noundef %2, i32 noundef %3) #0 {
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  %9 = alloca %struct.dim3, align 8
  %10 = alloca %struct.dim3, align 8
  %11 = alloca i64, align 8
  %12 = alloca ptr, align 8
  %13 = alloca { i64, i32 }, align 8
  %14 = alloca { i64, i32 }, align 8
  store ptr %0, ptr %5, align 8
  store ptr %1, ptr %6, align 8
  store ptr %2, ptr %7, align 8
  store i32 %3, ptr %8, align 4
  %15 = alloca ptr, i64 4, align 16
  %16 = getelementptr ptr, ptr %15, i32 0
  store ptr %5, ptr %16, align 8
  %17 = getelementptr ptr, ptr %15, i32 1
  store ptr %6, ptr %17, align 8
  %18 = getelementptr ptr, ptr %15, i32 2
  store ptr %7, ptr %18, align 8
  %19 = getelementptr ptr, ptr %15, i32 3
  store ptr %8, ptr %19, align 8
  %20 = call i32 @__cudaPopCallConfiguration(ptr %9, ptr %10, ptr %11, ptr %12)
  %21 = load i64, ptr %11, align 8
  %22 = load ptr, ptr %12, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 8 %13, ptr align 8 %9, i64 12, i1 false)
  %23 = getelementptr inbounds { i64, i32 }, ptr %13, i32 0, i32 0
  %24 = load i64, ptr %23, align 8
  %25 = getelementptr inbounds { i64, i32 }, ptr %13, i32 0, i32 1
  %26 = load i32, ptr %25, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 8 %14, ptr align 8 %10, i64 12, i1 false)
  %27 = getelementptr inbounds { i64, i32 }, ptr %14, i32 0, i32 0
  %28 = load i64, ptr %27, align 8
  %29 = getelementptr inbounds { i64, i32 }, ptr %14, i32 0, i32 1
  %30 = load i32, ptr %29, align 8
  %31 = call noundef i32 @cudaLaunchKernel(ptr noundef @__device_stub__matmul, i64 %24, i32 %26, i64 %28, i32 %30, ptr noundef %15, i64 noundef %21, ptr noundef %22)
  br label %32

32:                                               ; preds = %4
  ret void
}

declare i32 @__cudaPopCallConfiguration(ptr, ptr, ptr, ptr)

declare i32 @cudaLaunchKernel(ptr, i64, i32, i64, i32, ptr, i64, ptr)

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #1

; Function Attrs: convergent nocallback nounwind memory(inaccessiblemem: readwrite)
declare i32 @llvm.nvvm.shfl.sync.down.i32(i32, i32, i32, i32) #2

attributes #0 = { noinline norecurse optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { convergent nocallback nounwind memory(inaccessiblemem: readwrite) }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5}
!llvm.ident = !{!6}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 11, i32 8]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{i32 7, !"frame-pointer", i32 2}
!6 = !{!"Ubuntu clang version 16.0.6 (++20231112100510+7cbf1a259152-1~exp1~20231112100554.106)"}
