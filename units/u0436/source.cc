// u0436 – ceres::AutoDiffCostFunction::~AutoDiffCostFunction<CostFunctor, kNumResiduals, Ns...>
// Trích từ include/ceres/autodiff_cost_function.h, dòng 185–194 (chỉ để xem, không compile)

  virtual ~AutoDiffCostFunction() {
    // Manually release pointer if configured to not take ownership rather than
    // deleting only if ownership is taken.
    // This is to stay maximally compatible to old user code which may have
    // forgotten to implement a virtual destructor, from when the
    // AutoDiffCostFunction always took ownership.
    if (ownership_ == DO_NOT_TAKE_OWNERSHIP) {
      functor_.release();
    }
  }
