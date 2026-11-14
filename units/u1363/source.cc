// u1363 – ceres::internal::TypedLinearSolver::Solve
// Trích từ internal/ceres/linear_solver.h, dòng 366–376 (chỉ để xem, không compile)

  LinearSolver::Summary Solve(
      LinearOperator* A,
      const double* b,
      const LinearSolver::PerSolveOptions& per_solve_options,
      double* x) override {
    ScopedExecutionTimer total_time("LinearSolver::Solve", &execution_summary_);
    CHECK(A != nullptr);
    CHECK(b != nullptr);
    CHECK(x != nullptr);
    return SolveImpl(down_cast<MatrixType*>(A), b, per_solve_options, x);
  }
