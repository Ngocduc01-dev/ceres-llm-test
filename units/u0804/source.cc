// u0804 – ceres::internal::(anonymous)::RemoveLeadingZeros
// Trích từ internal/ceres/polynomial.cc, dòng 116–122 (chỉ để xem, không compile)

Vector RemoveLeadingZeros(const Vector& polynomial_in) {
  int i = 0;
  while (i < (polynomial_in.size() - 1) && polynomial_in(i) == 0.0) {
    ++i;
  }
  return polynomial_in.tail(polynomial_in.size() - i);
}
