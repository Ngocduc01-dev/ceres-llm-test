// u0652 – ceres::internal::StateUpdatingCallback::StateUpdatingCallback
// Trích từ internal/ceres/callbacks.cc, dòng 43–45 (chỉ để xem, không compile)

StateUpdatingCallback::StateUpdatingCallback(Program* program,
                                             double* parameters)
    : program_(program), parameters_(parameters) {}
