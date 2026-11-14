// u0820 – ceres::ScaledLoss::ScaledLoss
// Trích từ include/ceres/loss_function.h, dòng 335–336 (chỉ để xem, không compile)

  ScaledLoss(const LossFunction* rho, double a, Ownership ownership)
      : rho_(rho), a_(a), ownership_(ownership) {}
