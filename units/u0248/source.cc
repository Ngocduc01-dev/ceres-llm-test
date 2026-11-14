// u0248 – ceres::internal::GradientProblemSolverStateUpdatingCallback::GradientProblemSolverStateUpdatingCallback
// Trích từ internal/ceres/callbacks.cc, dòng 56–63 (chỉ để xem, không compile)

GradientProblemSolverStateUpdatingCallback::
    GradientProblemSolverStateUpdatingCallback(
        int num_parameters,
        const double* internal_parameters,
        double* user_parameters)
    : num_parameters_(num_parameters),
      internal_parameters_(internal_parameters),
      user_parameters_(user_parameters) {}
