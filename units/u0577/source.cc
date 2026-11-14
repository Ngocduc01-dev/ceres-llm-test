// u0577 – ceres::internal::DoglegStrategy::MakePolynomialForBoundaryConstrainedProblem
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 418–437 (chỉ để xem, không compile)

Vector DoglegStrategy::MakePolynomialForBoundaryConstrainedProblem() const {
  const double detB = subspace_B_.determinant();
  const double trB = subspace_B_.trace();
  const double r2 = radius_ * radius_;
  Matrix2d B_adj;
  // clang-format off
  B_adj <<  subspace_B_(1, 1) , -subspace_B_(0, 1),
           -subspace_B_(1, 0) ,  subspace_B_(0, 0);
  // clang-format on

  Vector polynomial(5);
  polynomial(0) = r2;
  polynomial(1) = 2.0 * r2 * trB;
  polynomial(2) = r2 * (trB * trB + 2.0 * detB) - subspace_g_.squaredNorm();
  polynomial(3) =
      -2.0 * (subspace_g_.transpose() * B_adj * subspace_g_ - r2 * detB * trB);
  polynomial(4) = r2 * detB * detB - (B_adj * subspace_g_).squaredNorm();

  return polynomial;
}
