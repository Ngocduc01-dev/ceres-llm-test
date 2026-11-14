// u0747 – ceres::internal::EigenSparseCholeskyTemplate::Solve
// Trích từ internal/ceres/eigensparse.cc, dòng 88–110 (chỉ để xem, không compile)

  LinearSolverTerminationType Solve(const double* rhs_ptr,
                                    double* solution_ptr,
                                    std::string* message) override {
    CHECK(analyzed_) << "Solve called without a call to Factorize first.";

    // Avoid copying when the scalar type is double
    if constexpr (std::is_same_v<typename Solver::Scalar, double>) {
      ConstVectorRef scalar_rhs(rhs_ptr, solver_.cols());
      VectorRef(solution_ptr, solver_.cols()) = solver_.solve(scalar_rhs);
    } else {
      auto scalar_rhs = ConstVectorRef(rhs_ptr, solver_.cols())
                            .template cast<typename Solver::Scalar>();
      auto scalar_solution = solver_.solve(scalar_rhs);
      VectorRef(solution_ptr, solver_.cols()) =
          scalar_solution.template cast<double>();
    }

    if (solver_.info() != Eigen::Success) {
      *message = "Eigen failure. Unable to do triangular solve.";
      return LinearSolverTerminationType::FAILURE;
    }
    return LinearSolverTerminationType::SUCCESS;
  }
