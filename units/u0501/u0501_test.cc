// FILE: u0501_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"
TEST(Unit_u0501, Rotate) { double angle_axis[3]={1,2,3}, point[3]={1,2,3}, result[3]={}; ceres::AngleAxisRotatePoint(angle_axis,point,result); }
