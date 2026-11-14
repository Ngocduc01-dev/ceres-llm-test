// u0456 – ceres::NumericDiffFirstOrderFunction::~NumericDiffFirstOrderFunction<FirstOrderFunctor, kMethod, kNumParameters>
// Trích từ include/ceres/numeric_diff_first_order_function.h, dòng 152–156 (chỉ để xem, không compile)

  ~NumericDiffFirstOrderFunction() override {
    if (ownership_ != TAKE_OWNERSHIP) {
      functor_.release();
    }
  }
