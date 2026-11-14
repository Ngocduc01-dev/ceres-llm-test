// u0508 – ceres::ComposedLoss::~ComposedLoss
// Trích từ internal/ceres/loss_function.cc, dòng 145–152 (chỉ để xem, không compile)

ComposedLoss::~ComposedLoss() {
  if (ownership_f_ == DO_NOT_TAKE_OWNERSHIP) {
    f_.release();
  }
  if (ownership_g_ == DO_NOT_TAKE_OWNERSHIP) {
    g_.release();
  }
}
