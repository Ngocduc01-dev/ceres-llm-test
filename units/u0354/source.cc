// u0354 – ceres::internal::BlockUntilFinished::BlockUntilFinished
// Trích từ internal/ceres/parallel_invoke.cc, dòng 46–47 (chỉ để xem, không compile)

BlockUntilFinished::BlockUntilFinished(int num_total_jobs)
    : num_total_jobs_finished_(0), num_total_jobs_(num_total_jobs) {}
