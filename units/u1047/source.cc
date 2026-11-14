// u1047 – ceres::OrderedGroups::Remove
// Trích từ include/ceres/ordered_groups.h, dòng 93–108 (chỉ để xem, không compile)

  bool Remove(const T element) {
    const int current_group = GroupId(element);
    if (current_group < 0) {
      return false;
    }

    group_to_elements_[current_group].erase(element);

    if (group_to_elements_[current_group].size() == 0) {
      // If the group is empty, then get rid of it.
      group_to_elements_.erase(current_group);
    }

    element_to_group_.erase(element);
    return true;
  }
