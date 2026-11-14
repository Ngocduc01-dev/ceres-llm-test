// u1029 – ceres::OrderedGroups::MinNonZeroGroup
// Trích từ include/ceres/ordered_groups.h, dòng 176–179 (chỉ để xem, không compile)

  int MinNonZeroGroup() const {
    CHECK_NE(NumGroups(), 0);
    return group_to_elements_.begin()->first;
  }
