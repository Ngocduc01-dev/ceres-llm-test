// u0507 – ceres::TolerantLoss::TolerantLoss
// Trích từ internal/ceres/loss_function.cc, dòng 93–97 (chỉ để xem, không compile)

TolerantLoss::TolerantLoss(double a, double b)
    : a_(a), b_(b), c_(b * log(1.0 + exp(-a / b))) {
  CHECK_GE(a, 0.0);
  CHECK_GT(b, 0.0);
}
