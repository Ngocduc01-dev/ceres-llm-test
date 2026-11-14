// u1263 – ceres::TinySolverCostFunctionAdapter::operator()
// Trích từ include/ceres/tiny_solver_cost_function_adapter.h, dòng 107–127 (chỉ để xem, không compile)

  bool operator()(const double* parameters,
                  double* residuals,
                  double* jacobian) const {
    if (!jacobian) {
      return cost_function_.Evaluate(&parameters, residuals, nullptr);
    }

    double* jacobians[1] = {row_major_jacobian_.data()};
    if (!cost_function_.Evaluate(&parameters, residuals, jacobians)) {
      return false;
    }

    // The Function object used by TinySolver takes its Jacobian in a
    // column-major layout, and the CostFunction objects use row-major
    // Jacobian matrices. So the following bit of code does the
    // conversion from row-major Jacobians to column-major Jacobians.
    Eigen::Map<Eigen::Matrix<double, NUM_RESIDUALS, NUM_PARAMETERS>>
        col_major_jacobian(jacobian, NumResiduals(), NumParameters());
    col_major_jacobian = row_major_jacobian_;
    return true;
  }
