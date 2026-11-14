// u0641 – ceres::NumericDiffFirstOrderFunction::NumericDiffFirstOrderFunction<FirstOrderFunctor, kMethod, kNumParameters>
// Trích từ include/ceres/numeric_diff_first_order_function.h, dòng 119–132 (chỉ để xem, không compile)

  explicit NumericDiffFirstOrderFunction(
      FirstOrderFunctor* functor,
      Ownership ownership = TAKE_OWNERSHIP,
      const NumericDiffOptions& options = NumericDiffOptions())
      : functor_(functor),
        num_parameters_(kNumParameters),
        ownership_(ownership),
        options_(options) {
    static_assert(kNumParameters != DYNAMIC,
                  "Number of parameters must be static when defined via the "
                  "template parameter. Use the other constructor for "
                  "dynamically sized functions.");
    static_assert(kNumParameters > 0, "kNumParameters must be positive");
  }
