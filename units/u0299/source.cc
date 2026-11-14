// u0299 – ceres::internal::FunctionSample::FunctionSample
// Trích từ internal/ceres/function_sample.cc, dòng 55–64 (chỉ để xem, không compile)

FunctionSample::FunctionSample(const double x,
                               const double value,
                               const double gradient)
    : x(x),
      vector_x_is_valid(false),
      value(value),
      value_is_valid(true),
      vector_gradient_is_valid(false),
      gradient(gradient),
      gradient_is_valid(true) {}
