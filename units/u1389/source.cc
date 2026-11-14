// u1389 – ceres::internal::EventLogger::~EventLogger
// Trích từ internal/ceres/wall_time.cc, dòng 72–78 (chỉ để xem, không compile)

EventLogger::~EventLogger() {
  if (!VLOG_IS_ON(3)) {
    return;
  }
  AddEvent("Total");
  VLOG(3) << "\n" << events_ << "\n";
}
