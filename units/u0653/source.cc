// u0653 – ceres::internal::LoggingCallback::LoggingCallback
// Trích từ internal/ceres/callbacks.cc, dòng 76–78 (chỉ để xem, không compile)

LoggingCallback::LoggingCallback(const MinimizerType minimizer_type,
                                 const bool log_to_stdout)
    : minimizer_type(minimizer_type), log_to_stdout_(log_to_stdout) {}
