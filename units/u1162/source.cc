// u1162 – ceres::internal::SparseIterativeRefiner::Refine
// Trích từ internal/ceres/iterative_refiner.cc, dòng 53–71 (chỉ để xem, không compile)

void SparseIterativeRefiner::Refine(const SparseMatrix& lhs,
                                    const double* rhs_ptr,
                                    SparseCholesky* cholesky,
                                    double* solution_ptr) {
  const int num_cols = lhs.num_cols();
  Allocate(num_cols);
  ConstVectorRef rhs(rhs_ptr, num_cols);
  VectorRef solution(solution_ptr, num_cols);
  std::string ignored_message;
  for (int i = 0; i < max_num_iterations_; ++i) {
    // residual = rhs - lhs * solution
    lhs_x_solution_.setZero();
    lhs.RightMultiplyAndAccumulate(solution_ptr, lhs_x_solution_.data());
    residual_ = rhs - lhs_x_solution_;
    // solution += lhs^-1 residual
    cholesky->Solve(residual_.data(), correction_.data(), &ignored_message);
    solution += correction_;
  }
};
