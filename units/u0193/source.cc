// u0193 – ceres::OrderedGroups::IsMember
// Trích từ include/ceres/ordered_groups.h, dòng 156–159 (chỉ để xem, không compile)

  bool IsMember(const T element) const {
    auto it = element_to_group_.find(element);
    return (it != element_to_group_.end());
  }
