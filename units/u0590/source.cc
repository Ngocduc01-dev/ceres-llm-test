// u0590 – ceres::TinySolver::Initialize
// Trích từ include/ceres/tiny_solver.h, dòng 355–359 (chỉ để xem, không compile)

  template <int R, int P>
  typename enable_if<(R == Eigen::Dynamic && P == Eigen::Dynamic), void>::type
  Initialize(const Function& function) {
    Initialize(function.NumResiduals(), function.NumParameters());
  }
