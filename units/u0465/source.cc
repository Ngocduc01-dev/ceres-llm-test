// u0465 – ceres::ConditionedCostFunction::~ConditionedCostFunction
// Trích từ internal/ceres/conditioned_cost_function.cc, dòng 69–76 (chỉ để xem, không compile)

ConditionedCostFunction::~ConditionedCostFunction() {
  if (ownership_ == TAKE_OWNERSHIP) {
    STLDeleteUniqueContainerPointers(conditioners_.begin(),
                                     conditioners_.end());
  } else {
    wrapped_cost_function_.release();
  }
}
