// u0919 – ceres::ComposedLoss::ComposedLoss
// Trích từ internal/ceres/loss_function.cc, dòng 136–143 (chỉ để xem, không compile)

ComposedLoss::ComposedLoss(const LossFunction* f,
                           Ownership ownership_f,
                           const LossFunction* g,
                           Ownership ownership_g)
    : f_(f), g_(g), ownership_f_(ownership_f), ownership_g_(ownership_g) {
  CHECK(f_ != nullptr);
  CHECK(g_ != nullptr);
}
