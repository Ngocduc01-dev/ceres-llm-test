// u0997 – ceres_create_tolerant_loss_function_data
// Trích từ internal/ceres/c_api.cc, dòng 123–125 (chỉ để xem, không compile)

void* ceres_create_tolerant_loss_function_data(double a, double b) {
  return new ceres::TolerantLoss(a, b);
}
