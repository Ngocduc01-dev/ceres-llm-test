// u0956 – ceres::internal::Minimizer::RunCallbacks
// Trích từ internal/ceres/minimizer.cc, dòng 57–89 (chỉ để xem, không compile)

bool Minimizer::RunCallbacks(const Minimizer::Options& options,
                             const IterationSummary& iteration_summary,
                             Solver::Summary* summary) {
  const bool is_not_silent = !options.is_silent;
  CallbackReturnType status = SOLVER_CONTINUE;
  int i = 0;
  while (status == SOLVER_CONTINUE && i < options.callbacks.size()) {
    status = (*options.callbacks[i])(iteration_summary);
    ++i;
  }
  switch (status) {
    case SOLVER_CONTINUE:
      return true;
    case SOLVER_TERMINATE_SUCCESSFULLY:
      summary->termination_type = USER_SUCCESS;
      summary->message =
          "User callback returned SOLVER_TERMINATE_SUCCESSFULLY.";
      if (is_not_silent) {
        VLOG(1) << "Terminating: " << summary->message;
      }
      return false;
    case SOLVER_ABORT:
      summary->termination_type = USER_FAILURE;
      summary->message = "User callback returned SOLVER_ABORT.";
      if (is_not_silent) {
        VLOG(1) << "Terminating: " << summary->message;
      }
      return false;
    default:
      LOG(FATAL) << "Unknown type of user callback status";
  }
  return false;
}
