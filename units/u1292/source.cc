// u1292 – ceres::internal::EventLogger::AddEvent
// Trích từ internal/ceres/wall_time.cc, dòng 80–95 (chỉ để xem, không compile)

void EventLogger::AddEvent(const std::string& event_name) {
  if (!VLOG_IS_ON(3)) {
    return;
  }

  const double current_time = WallTimeInSeconds();
  const double relative_time_delta = current_time - last_event_time_;
  const double absolute_time_delta = current_time - start_time_;
  last_event_time_ = current_time;

  StringAppendF(&events_,
                "  %30s : %10.5f   %10.5f\n",
                event_name.c_str(),
                relative_time_delta,
                absolute_time_delta);
}
