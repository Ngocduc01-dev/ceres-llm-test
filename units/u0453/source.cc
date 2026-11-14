// u0453 – ceres::LossFunctionWrapper::~LossFunctionWrapper
// Trích từ include/ceres/loss_function.h, dòng 400–404 (chỉ để xem, không compile)

  ~LossFunctionWrapper() override {
    if (ownership_ == DO_NOT_TAKE_OWNERSHIP) {
      rho_.release();
    }
  }
