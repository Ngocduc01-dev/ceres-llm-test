// u1513 – ceres::internal::ProblemImpl::AddParameterBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 371–376 (chỉ để xem, không compile)

void ProblemImpl::AddParameterBlock(double* values,
                                    int size,
                                    Manifold* manifold) {
  ParameterBlock* parameter_block = InternalAddParameterBlock(values, size);
  InternalSetManifold(values, parameter_block, manifold);
}
