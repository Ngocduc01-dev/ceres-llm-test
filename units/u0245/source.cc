// u0245 – CallbackLossFunction::CallbackLossFunction
// Trích từ internal/ceres/c_api.cc, dòng 98–100 (chỉ để xem, không compile)

  explicit CallbackLossFunction(ceres_loss_function_t loss_function,
                                void* user_data)
      : loss_function_(loss_function), user_data_(user_data) {}
