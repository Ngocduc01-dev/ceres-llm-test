// u0965 – ceres::internal::ThreadPool::Stop
// Trích từ internal/ceres/thread_pool.cc, dòng 102–102 (chỉ để xem, không compile)

void ThreadPool::Stop() { task_queue_.StopWaiters(); }
