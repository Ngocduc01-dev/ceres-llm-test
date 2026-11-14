// u0298 – ceres::internal::FunctionSample::FunctionSample
// Trích từ internal/ceres/function_sample.cc, dòng 46–53 (chỉ để xem, không compile)

FunctionSample::FunctionSample(const double x, const double value)
    : x(x),
      vector_x_is_valid(false),
      value(value),
      value_is_valid(true),
      vector_gradient_is_valid(false),
      gradient(0.0),
      gradient_is_valid(false) {}
