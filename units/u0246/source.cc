// u0246 – CallbackLossFunction::Evaluate
// Trích từ internal/ceres/c_api.cc, dòng 101–103 (chỉ để xem, không compile)

  void Evaluate(double sq_norm, double* rho) const final {
    (*loss_function_)(user_data_, sq_norm, rho);
  }
