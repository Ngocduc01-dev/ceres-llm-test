// u0067 – ceres::internal::FirstOrderFunctorAdapter::operator()
// Trích từ include/ceres/internal/variadic_evaluate.h, dòng 124–126 (chỉ để xem, không compile)

  bool operator()(double const* const* parameters, double* cost) const {
    return functor_(*parameters, cost);
  }
