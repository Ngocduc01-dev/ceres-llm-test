// u0841 – ceres::internal::ContextImpl::~ContextImpl
// Trích từ internal/ceres/context_impl.cc, dòng 186–190 (chỉ để xem, không compile)

ContextImpl::~ContextImpl() {
#ifndef CERES_NO_CUDA
  TearDown();
#endif  // CERES_NO_CUDA
}
