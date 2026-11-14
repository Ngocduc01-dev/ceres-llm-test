// u0951 – ceres::internal::EigenSparseCholeskyTemplate::Factorize
// Trích từ internal/ceres/eigensparse.cc, dòng 60–86 (chỉ để xem, không compile)

  LinearSolverTerminationType Factorize(
      const Eigen::SparseMatrix<typename Solver::Scalar>& lhs,
      std::string* message) {
    if (!analyzed_) {
      solver_.analyzePattern(lhs);

      if (VLOG_IS_ON(2)) {
        std::stringstream ss;
        solver_.dumpMemory(ss);
        VLOG(2) << "Symbolic Analysis\n" << ss.str();
      }

      if (solver_.info() != Eigen::Success) {
        *message = "Eigen failure. Unable to find symbolic factorization.";
        return LinearSolverTerminationType::FATAL_ERROR;
      }

      analyzed_ = true;
    }

    solver_.factorize(lhs);
    if (solver_.info() != Eigen::Success) {
      *message = "Eigen failure. Unable to find numeric factorization.";
      return LinearSolverTerminationType::FAILURE;
    }
    return LinearSolverTerminationType::SUCCESS;
  }
