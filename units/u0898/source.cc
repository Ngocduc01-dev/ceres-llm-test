// u0898 – ceres::internal::ThreadPool::AddTask
// Trích từ internal/ceres/thread_pool.cc, dòng 86–88 (chỉ để xem, không compile)

void ThreadPool::AddTask(const std::function<void()>& func) {
  task_queue_.Push(func);
}
