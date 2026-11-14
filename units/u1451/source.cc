// u1451 – ceres::internal::ProblemImpl::InternalSetManifold
// Trích từ internal/ceres/problem_impl.cc, dòng 362–369 (chỉ để xem, không compile)

void ProblemImpl::InternalSetManifold(double* /*values*/,
                                      ParameterBlock* parameter_block,
                                      Manifold* manifold) {
  if (manifold != nullptr && options_.manifold_ownership == TAKE_OWNERSHIP) {
    manifolds_to_delete_.push_back(manifold);
  }
  parameter_block->SetManifold(manifold);
}
