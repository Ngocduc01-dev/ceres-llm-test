// u0994 – ceres_create_softl1_loss_function_data
// Trích từ internal/ceres/c_api.cc, dòng 114–116 (chỉ để xem, không compile)

void* ceres_create_softl1_loss_function_data(double a) {
  return new ceres::SoftLOneLoss(a);
}
