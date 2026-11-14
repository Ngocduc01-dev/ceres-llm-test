// u1343 – ceres::internal::ProblemImpl::ProblemImpl
// Trích từ internal/ceres/problem_impl.cc, dòng 228–231 (chỉ để xem, không compile)

ProblemImpl::ProblemImpl()
    : options_(Problem::Options()), program_(new internal::Program) {
  InitializeContext(options_.context, &context_impl_, &context_impl_owned_);
}
