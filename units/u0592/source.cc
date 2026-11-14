// u0592 – ceres::TinySolver::Initialize
// Trích từ include/ceres/tiny_solver.h, dòng 371–375 (chỉ để xem, không compile)

  template <int R, int P>
  typename enable_if<(R != Eigen::Dynamic && P == Eigen::Dynamic), void>::type
  Initialize(const Function& function) {
    Initialize(R, function.NumParameters());
  }
