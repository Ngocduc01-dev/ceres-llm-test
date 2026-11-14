// u0697 – ceres::NumericDiffFirstOrderFunction::NumericDiffFirstOrderFunction<FirstOrderFunctor, kMethod, kNumParameters>
// Trích từ include/ceres/numeric_diff_first_order_function.h, dòng 135–150 (chỉ để xem, không compile)

  explicit NumericDiffFirstOrderFunction(
      FirstOrderFunctor* functor,
      int num_parameters,
      Ownership ownership = TAKE_OWNERSHIP,
      const NumericDiffOptions& options = NumericDiffOptions())
      : functor_(functor),
        num_parameters_(num_parameters),
        ownership_(ownership),
        options_(options) {
    static_assert(
        kNumParameters == DYNAMIC,
        "Template parameter must be DYNAMIC when using this constructor. If "
        "you want to provide the number of parameters statically use the other "
        "constructor.");
    CHECK_GT(num_parameters, 0);
  }
