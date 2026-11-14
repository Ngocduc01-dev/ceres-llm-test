// u1366 – ceres::internal::ParameterBlock::SetManifold
// Trích từ internal/ceres/parameter_block.h, dòng 160–188 (chỉ để xem, không compile)

  void SetManifold(Manifold* new_manifold) {
    // Nothing to do if the new manifold is the same as the old
    // manifold.
    if (new_manifold == manifold_) {
      return;
    }

    if (new_manifold == nullptr) {
      manifold_ = nullptr;
      plus_jacobian_ = nullptr;
      return;
    }

    CHECK_EQ(new_manifold->AmbientSize(), size_)
        << "The parameter block has size = " << size_
        << " while the manifold has ambient size = "
        << new_manifold->AmbientSize();

    CHECK_GE(new_manifold->TangentSize(), 0)
        << "Invalid Manifold. Manifolds must have a "
        << "non-negative dimensional tangent space.";

    manifold_ = new_manifold;
    plus_jacobian_ = std::make_unique<double[]>(manifold_->AmbientSize() *
                                                manifold_->TangentSize());
    CHECK(UpdatePlusJacobian())
        << "Manifold::PlusJacobian computation failed for x: "
        << ConstVectorRef(state_, Size()).transpose();
  }
