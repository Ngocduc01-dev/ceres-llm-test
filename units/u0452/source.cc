// u0452 – ceres::ScaledLoss::~ScaledLoss
// Trích từ include/ceres/loss_function.h, dòng 340–344 (chỉ để xem, không compile)

  ~ScaledLoss() override {
    if (ownership_ == DO_NOT_TAKE_OWNERSHIP) {
      rho_.release();
    }
  }
