// u0905 – ceres::LossFunctionWrapper::Reset
// Trích từ include/ceres/loss_function.h, dòng 416–422 (chỉ để xem, không compile)

  void Reset(LossFunction* rho, Ownership ownership) {
    if (ownership_ == DO_NOT_TAKE_OWNERSHIP) {
      rho_.release();
    }
    rho_.reset(rho);
    ownership_ = ownership;
  }
