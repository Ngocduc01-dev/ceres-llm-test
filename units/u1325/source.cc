// u1325 – ceres::internal::DenseQRSolver::DenseQRSolver
// Trích từ internal/ceres/dense_qr_solver.cc, dòng 45–46 (chỉ để xem, không compile)

DenseQRSolver::DenseQRSolver(const LinearSolver::Options& options)
    : options_(options), dense_qr_(DenseQR::Create(options)) {}
