// u0554 – ceres::internal::ComputeHouseholderVector
// Trích từ include/ceres/internal/householder_vector.h, dòng 47–82 (chỉ để xem, không compile)

template <typename XVectorType, typename Scalar, int N>
void ComputeHouseholderVector(const XVectorType& x,
                              Eigen::Matrix<Scalar, N, 1>* v,
                              Scalar* beta) {
  CHECK(beta != nullptr);
  CHECK(v != nullptr);
  CHECK_GT(x.rows(), 1);
  CHECK_EQ(x.rows(), v->rows());

  Scalar sigma = x.head(x.rows() - 1).squaredNorm();
  *v = x;
  (*v)(v->rows() - 1) = Scalar(1.0);

  *beta = Scalar(0.0);
  const Scalar& x_pivot = x(x.rows() - 1);

  if (sigma <= Scalar(std::numeric_limits<double>::epsilon())) {
    if (x_pivot < Scalar(0.0)) {
      *beta = Scalar(2.0);
    }
    return;
  }

  const Scalar mu = sqrt(x_pivot * x_pivot + sigma);
  Scalar v_pivot = Scalar(1.0);

  if (x_pivot <= Scalar(0.0)) {
    v_pivot = x_pivot - mu;
  } else {
    v_pivot = -sigma / (x_pivot + mu);
  }

  *beta = Scalar(2.0) * v_pivot * v_pivot / (sigma + v_pivot * v_pivot);

  v->head(v->rows() - 1) /= v_pivot;
}
