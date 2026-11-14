// u1181 – ceres::internal::CgnrSolver::CgnrSolver
// Trích từ internal/ceres/cgnr_solver.cc, dòng 124–134 (chỉ để xem, không compile)

CgnrSolver::CgnrSolver(LinearSolver::Options options)
    : options_(std::move(options)) {
  if (options_.preconditioner_type != JACOBI &&
      options_.preconditioner_type != IDENTITY &&
      options_.preconditioner_type != SUBSET) {
    LOG(FATAL)
        << "Preconditioner = "
        << PreconditionerTypeToString(options_.preconditioner_type) << ". "
        << "Congratulations, you found a bug in Ceres. Please report it.";
  }
}
