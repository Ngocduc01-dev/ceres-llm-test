// u0458 – ceres::OrderedGroups::GroupSize
// Trích từ include/ceres/ordered_groups.h, dòng 163–166 (chỉ để xem, không compile)

  int GroupSize(const int group) const {
    auto it = group_to_elements_.find(group);
    return (it == group_to_elements_.end()) ? 0 : it->second.size();
  }
