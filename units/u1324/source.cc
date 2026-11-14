// u1324 – ceres::internal::DenseNormalCholeskySolver::DenseNormalCholeskySolver
// Trích từ internal/ceres/dense_normal_cholesky_solver.cc, dòng 44–47 (chỉ để xem, không compile)

DenseNormalCholeskySolver::DenseNormalCholeskySolver(
    LinearSolver::Options options)
    : options_(std::move(options)),
      cholesky_(DenseCholesky::Create(options_)) {}
