// u0072 – ceres::Jet::operator+=
// Trích từ include/ceres/jet.h, dòng 265–268 (chỉ để xem, không compile)

  Jet<T, N>& operator+=(const T& s) {
    *this = *this + s;
    return *this;
  }
