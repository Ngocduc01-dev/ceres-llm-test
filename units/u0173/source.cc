// u0173 – ceres::SoftLOneLoss::SoftLOneLoss
// Trích từ include/ceres/loss_function.h, dòng 193–193 (chỉ để xem, không compile)

  explicit SoftLOneLoss(double a) : b_(a * a), c_(1 / b_) {}
