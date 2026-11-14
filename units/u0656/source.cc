// u0656 – ceres::internal::RefinedDenseCholesky::RefinedDenseCholesky
// Trích từ internal/ceres/dense_cholesky.cc, dòng 319–323 (chỉ để xem, không compile)

RefinedDenseCholesky::RefinedDenseCholesky(
    std::unique_ptr<DenseCholesky> dense_cholesky,
    std::unique_ptr<DenseIterativeRefiner> iterative_refiner)
    : dense_cholesky_(std::move(dense_cholesky)),
      iterative_refiner_(std::move(iterative_refiner)) {}
