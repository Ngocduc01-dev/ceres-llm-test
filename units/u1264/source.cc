// u1264 – ceres::internal::ParameterBlock::SetState
// Trích từ internal/ceres/parameter_block.h, dòng 91–99 (chỉ để xem, không compile)

  bool SetState(const double* x) {
    CHECK(x != nullptr) << "Tried to set the state of constant parameter "
                        << "with user location " << user_state_;
    CHECK(!IsConstant()) << "Tried to set the state of constant parameter "
                         << "with user location " << user_state_;

    state_ = x;
    return UpdatePlusJacobian();
  }
