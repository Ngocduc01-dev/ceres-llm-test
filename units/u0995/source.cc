// u0995 – ceres_create_cauchy_loss_function_data
// Trích từ internal/ceres/c_api.cc, dòng 117–119 (chỉ để xem, không compile)

void* ceres_create_cauchy_loss_function_data(double a) {
  return new ceres::CauchyLoss(a);
}
