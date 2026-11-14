// u1291 – ceres::internal::EventLogger::EventLogger
// Trích từ internal/ceres/wall_time.cc, dòng 60–70 (chỉ để xem, không compile)

EventLogger::EventLogger(const std::string& logger_name) {
  if (!VLOG_IS_ON(3)) {
    return;
  }

  start_time_ = WallTimeInSeconds();
  last_event_time_ = start_time_;
  events_ = StringPrintf(
      "\n%s\n                                        Delta   Cumulative\n",
      logger_name.c_str());
}
