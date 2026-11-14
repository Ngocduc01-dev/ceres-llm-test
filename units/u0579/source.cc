// u0579 – ceres::internal::SparseIterativeRefiner::Allocate
// Trích từ internal/ceres/iterative_refiner.cc, dòng 47–51 (chỉ để xem, không compile)

void SparseIterativeRefiner::Allocate(int num_cols) {
  residual_.resize(num_cols);
  correction_.resize(num_cols);
  lhs_x_solution_.resize(num_cols);
}
