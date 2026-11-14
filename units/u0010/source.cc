// u0010 – ceres::internal::PlusWrapper::operator()
// Trích từ include/ceres/autodiff_manifold.h, dòng 188–191 (chỉ để xem, không compile)

  template <typename T>
  bool operator()(const T* x, const T* delta, T* x_plus_delta) const {
    return functor.Plus(x, delta, x_plus_delta);
  }
