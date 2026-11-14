// u0687 – ceres::internal::PowerSeriesExpansionPreconditioner::PowerSeriesExpansionPreconditioner
// Trích từ internal/ceres/power_series_expansion_preconditioner.cc, dòng 39–47 (chỉ để xem, không compile)

PowerSeriesExpansionPreconditioner::PowerSeriesExpansionPreconditioner(
    const ImplicitSchurComplement* isc,
    const int max_num_spse_iterations,
    const double spse_tolerance,
    const Preconditioner::Options& options)
    : isc_(isc),
      max_num_spse_iterations_(max_num_spse_iterations),
      spse_tolerance_(spse_tolerance),
      options_(options) {}
