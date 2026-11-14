// u0174 – ceres::CauchyLoss::CauchyLoss
// Trích từ include/ceres/loss_function.h, dòng 210–210 (chỉ để xem, không compile)

  explicit CauchyLoss(double a) : b_(a * a), c_(1 / b_) {}
