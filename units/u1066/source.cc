// u1066 – ceres::internal::ParameterBlock::UpdatePlusJacobian
// Trích từ internal/ceres/parameter_block.h, dòng 312–339 (chỉ để xem, không compile)

  bool UpdatePlusJacobian() {
    if (manifold_ == nullptr) {
      return true;
    }

    // Update the Plus Jacobian. In some cases this is
    // wasted effort; if this is a bottleneck, we will find a solution
    // at that time.
    const int jacobian_size = Size() * TangentSize();
    InvalidateArray(jacobian_size, plus_jacobian_.get());
    if (!manifold_->PlusJacobian(state_, plus_jacobian_.get())) {
      LOG(WARNING) << "Manifold::PlusJacobian computation failed"
                      "for x: "
                   << ConstVectorRef(state_, Size()).transpose();
      return false;
    }

    if (!IsArrayValid(jacobian_size, plus_jacobian_.get())) {
      LOG(WARNING) << "Manifold::PlusJacobian computation returned "
                   << "an invalid matrix for x: "
                   << ConstVectorRef(state_, Size()).transpose()
                   << "\n Jacobian matrix : "
                   << ConstMatrixRef(
                          plus_jacobian_.get(), Size(), TangentSize());
      return false;
    }
    return true;
  }
