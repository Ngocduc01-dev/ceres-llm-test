// u0993 – ceres_create_huber_loss_function_data
// Trích từ internal/ceres/c_api.cc, dòng 111–113 (chỉ để xem, không compile)

void* ceres_create_huber_loss_function_data(double a) {
  return new ceres::HuberLoss(a);
}
