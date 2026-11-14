// u1344 – ceres::internal::ProblemImpl::ProblemImpl
// Trích từ internal/ceres/problem_impl.cc, dòng 233–237 (chỉ để xem, không compile)

ProblemImpl::ProblemImpl(const Problem::Options& options)
    : options_(options), program_(new internal::Program) {
  program_->evaluation_callback_ = options.evaluation_callback;
  InitializeContext(options_.context, &context_impl_, &context_impl_owned_);
}
