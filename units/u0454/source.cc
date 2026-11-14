// u0454 – ceres::LossFunctionWrapper::Evaluate
// Trích từ include/ceres/loss_function.h, dòng 406–414 (chỉ để xem, không compile)

  void Evaluate(double sq_norm, double out[3]) const override {
    if (rho_.get() == nullptr) {
      out[0] = sq_norm;
      out[1] = 1.0;
      out[2] = 0.0;
    } else {
      rho_->Evaluate(sq_norm, out);
    }
  }
