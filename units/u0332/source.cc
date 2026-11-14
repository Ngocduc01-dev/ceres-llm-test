// u0332 – ceres::TrivialLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 44–48 (chỉ để xem, không compile)

void TrivialLoss::Evaluate(double s, double rho[3]) const {
  rho[0] = s;
  rho[1] = 1.0;
  rho[2] = 0.0;
}
