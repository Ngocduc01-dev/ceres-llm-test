// u0297 – ceres::internal::FunctionSample::FunctionSample
// Trích từ internal/ceres/function_sample.cc, dòng 37–44 (chỉ để xem, không compile)

FunctionSample::FunctionSample()
    : x(0.0),
      vector_x_is_valid(false),
      value(0.0),
      value_is_valid(false),
      vector_gradient_is_valid(false),
      gradient(0.0),
      gradient_is_valid(false) {}
