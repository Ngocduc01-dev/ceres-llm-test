// FILE: u0527_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// Path P1 calls Finished(int num_jobs_finished).
TEST(Unitu0527, CallsTarget) {
  object.Finished(1);
}

// Path P2 calls Finished(int num_jobs_finished) on the alternate CFG path.
TEST(Unitu0527, CallsTargetAlternate) {
  object.Finished(1);
}
