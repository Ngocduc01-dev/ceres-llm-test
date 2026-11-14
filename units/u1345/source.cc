// u1345 – ceres::internal::DenseSchurComplementSolver::DenseSchurComplementSolver
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 159–162 (chỉ để xem, không compile)

DenseSchurComplementSolver::DenseSchurComplementSolver(
    const LinearSolver::Options& options)
    : SchurComplementSolver(options),
      cholesky_(DenseCholesky::Create(options)) {}
