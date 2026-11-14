// u0011 – ceres::internal::MinusWrapper::operator()
// Trích từ include/ceres/autodiff_manifold.h, dòng 198–201 (chỉ để xem, không compile)

  template <typename T>
  bool operator()(const T* y, const T* x, T* y_minus_x) const {
    return functor.Minus(y, x, y_minus_x);
  }
