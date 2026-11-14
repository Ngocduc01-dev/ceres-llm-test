// u0457 – ceres::OrderedGroups::GroupId
// Trích từ include/ceres/ordered_groups.h, dòng 148–154 (chỉ để xem, không compile)

  int GroupId(const T element) const {
    auto it = element_to_group_.find(element);
    if (it == element_to_group_.end()) {
      return -1;
    }
    return it->second;
  }
