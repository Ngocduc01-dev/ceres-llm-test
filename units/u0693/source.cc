// u0693 – ceres::internal::RefinedSparseCholesky::RefinedSparseCholesky
// Trích từ internal/ceres/sparse_cholesky.cc, dòng 120–124 (chỉ để xem, không compile)

RefinedSparseCholesky::RefinedSparseCholesky(
    std::unique_ptr<SparseCholesky> sparse_cholesky,
    std::unique_ptr<SparseIterativeRefiner> iterative_refiner)
    : sparse_cholesky_(std::move(sparse_cholesky)),
      iterative_refiner_(std::move(iterative_refiner)) {}
