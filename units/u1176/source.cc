// u1176 – ceres::internal::ChangeNumThreadsIfNeeded
// Trích từ internal/ceres/preprocessor.cc, dòng 61–73 (chỉ để xem, không compile)

void ChangeNumThreadsIfNeeded(Solver::Options* options) {
  if (options->num_threads == 1) {
    return;
  }
  const int num_threads_available = ThreadPool::MaxNumThreadsAvailable();
  if (options->num_threads > num_threads_available) {
    LOG(WARNING) << "Specified options.num_threads: " << options->num_threads
                 << " exceeds maximum available from the threading model Ceres "
                 << "was compiled with: " << num_threads_available
                 << ".  Bounding to maximum number available.";
    options->num_threads = num_threads_available;
  }
}
