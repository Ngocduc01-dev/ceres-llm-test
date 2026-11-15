// FILE: u0437_test.cc
#include <memory>
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"
struct BinaryScalarCost { template <typename T> bool operator()(const T* x, const T* y, T* r) const { r[0] = x[0] + y[0]; return true; } };
TEST(Unit_u0437, Evaluate) { auto target = std::make_unique<ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2>>(new BinaryScalarCost); double x[2]={}, y[2]={}, r[1]={}; double* p[]={x,y}; target->Evaluate(p,r,nullptr); }
