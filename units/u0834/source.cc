// u0834 – ceres_stock_loss_function
// Trích từ internal/ceres/c_api.cc, dòng 131–136 (chỉ để xem, không compile)

void ceres_stock_loss_function(void* user_data,
                               double squared_norm,
                               double out[3]) {
  reinterpret_cast<ceres::LossFunction*>(user_data)->Evaluate(squared_norm,
                                                              out);
}
