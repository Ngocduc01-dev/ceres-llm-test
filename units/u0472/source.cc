// u0472 – ceres::ScaledLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 165–176 (chỉ để xem, không compile)

void ScaledLoss::Evaluate(double s, double rho[3]) const {
  if (rho_.get() == nullptr) {
    rho[0] = a_ * s;
    rho[1] = a_;
    rho[2] = 0.0;
  } else {
    rho_->Evaluate(s, rho);
    rho[0] *= a_;
    rho[1] *= a_;
    rho[2] *= a_;
  }
}
