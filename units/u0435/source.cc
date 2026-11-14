// u0435 – ceres::internal::WallTimeInSeconds
// Trích từ internal/ceres/wall_time.cc, dòng 45–58 (chỉ để xem, không compile)

double WallTimeInSeconds() {
#ifdef _WIN32
  LARGE_INTEGER count;
  LARGE_INTEGER frequency;
  QueryPerformanceCounter(&count);
  QueryPerformanceFrequency(&frequency);
  return static_cast<double>(count.QuadPart) /
         static_cast<double>(frequency.QuadPart);
#else
  timeval time_val;
  gettimeofday(&time_val, nullptr);
  return (time_val.tv_sec + time_val.tv_usec * 1e-6);
#endif
}
