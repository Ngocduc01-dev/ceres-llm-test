// FILE: u0478_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"
TEST(Unit_u0478, Invoke) { int observed=0; auto fn=[&](int id,int value){observed=id+value;}; ceres::internal::InvokeWithThreadId(3,fn,4); }
