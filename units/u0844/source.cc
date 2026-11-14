// u0844 – ceres::Covariance::Covariance
// Trích từ internal/ceres/covariance.cc, dòng 42–44 (chỉ để xem, không compile)

Covariance::Covariance(const Covariance::Options& options) {
  impl_ = std::make_unique<internal::CovarianceImpl>(options);
}
