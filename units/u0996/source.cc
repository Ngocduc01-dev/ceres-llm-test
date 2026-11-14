// u0996 – ceres_create_arctan_loss_function_data
// Trích từ internal/ceres/c_api.cc, dòng 120–122 (chỉ để xem, không compile)

void* ceres_create_arctan_loss_function_data(double a) {
  return new ceres::ArctanLoss(a);
}
