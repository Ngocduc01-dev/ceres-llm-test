// u0175 – ceres::ArctanLoss::ArctanLoss
// Trích từ include/ceres/loss_function.h, dòng 231–231 (chỉ để xem, không compile)

  explicit ArctanLoss(double a) : a_(a), b_(1 / (a * a)) {}
