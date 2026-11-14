// u0740 – ceres::AutoDiffFirstOrderFunction::Evaluate
// Trích từ include/ceres/autodiff_first_order_function.h, dòng 113–139 (chỉ để xem, không compile)

  bool Evaluate(const double* const parameters,
                double* cost,
                double* gradient) const override {
    if (gradient == nullptr) {
      return (*functor_)(parameters, cost);
    }

    using JetT = Jet<double, kNumParameters>;
    internal::FixedArray<JetT, (256 * 7) / sizeof(JetT)> x(kNumParameters);
    for (int i = 0; i < kNumParameters; ++i) {
      x[i].a = parameters[i];
      x[i].v.setZero();
      x[i].v[i] = 1.0;
    }

    JetT output;
    output.a = kImpossibleValue;
    output.v.setConstant(kImpossibleValue);

    if (!(*functor_)(x.data(), &output)) {
      return false;
    }

    *cost = output.a;
    VectorRef(gradient, kNumParameters) = output.v;
    return true;
  }
