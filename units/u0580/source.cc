// u0580 – ceres::internal::DenseIterativeRefiner::Allocate
// Trích từ internal/ceres/iterative_refiner.cc, dòng 78–81 (chỉ để xem, không compile)

void DenseIterativeRefiner::Allocate(int num_cols) {
  residual_.resize(num_cols);
  correction_.resize(num_cols);
}
