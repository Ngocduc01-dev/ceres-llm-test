// u1087 – ceres::internal::DenseIterativeRefiner::Refine
// Trích từ internal/ceres/iterative_refiner.cc, dòng 83–99 (chỉ để xem, không compile)

void DenseIterativeRefiner::Refine(const int num_cols,
                                   const double* lhs_ptr,
                                   const double* rhs_ptr,
                                   DenseCholesky* cholesky,
                                   double* solution_ptr) {
  Allocate(num_cols);
  ConstMatrixRef lhs(lhs_ptr, num_cols, num_cols);
  ConstVectorRef rhs(rhs_ptr, num_cols);
  VectorRef solution(solution_ptr, num_cols);
  std::string ignored_message;
  for (int i = 0; i < max_num_iterations_; ++i) {
    residual_ = rhs - lhs * solution;
    // solution += lhs^-1 residual
    cholesky->Solve(residual_.data(), correction_.data(), &ignored_message);
    solution += correction_;
  }
};
