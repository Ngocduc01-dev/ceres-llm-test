// u0616 – ceres::AutoDiffFirstOrderFunction::AutoDiffFirstOrderFunction<FirstOrderFunctor, kNumParameters>
// Trích từ include/ceres/autodiff_first_order_function.h, dòng 108–111 (chỉ để xem, không compile)

  explicit AutoDiffFirstOrderFunction(FirstOrderFunctor* functor)
      : functor_(functor) {
    static_assert(kNumParameters > 0, "kNumParameters must be positive");
  }
