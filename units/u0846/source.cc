// u0846 – ceres::internal::CovarianceImpl::CovarianceImpl
// Trích từ internal/ceres/covariance_impl.cc, dòng 64–68 (chỉ để xem, không compile)

CovarianceImpl::CovarianceImpl(const Covariance::Options& options)
    : options_(options), is_computed_(false), is_valid_(false) {
  evaluate_options_.num_threads = options_.num_threads;
  evaluate_options_.apply_loss_function = options_.apply_loss_function;
}
