// u0636 – ceres::Jet::operator+=
// Trích từ include/ceres/jet.h, dòng 244–247 (chỉ để xem, không compile)

  Jet<T, N>& operator+=(const Jet<T, N>& y) {
    *this = *this + y;
    return *this;
  }
