// u0833 – ceres_free_stock_loss_function_data
// Trích từ internal/ceres/c_api.cc, dòng 127–129 (chỉ để xem, không compile)

void ceres_free_stock_loss_function_data(void* loss_function_data) {
  delete reinterpret_cast<ceres::LossFunction*>(loss_function_data);
}
