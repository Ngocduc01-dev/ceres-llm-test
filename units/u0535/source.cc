// u0535 – ceres::OrderedGroups::AddElementToGroup
// Trích từ include/ceres/ordered_groups.h, dòng 63–84 (chỉ để xem, không compile)

  bool AddElementToGroup(const T element, const int group) {
    if (group < 0) {
      return false;
    }

    auto it = element_to_group_.find(element);
    if (it != element_to_group_.end()) {
      if (it->second == group) {
        // Element is already in the right group, nothing to do.
        return true;
      }

      group_to_elements_[it->second].erase(element);
      if (group_to_elements_[it->second].size() == 0) {
        group_to_elements_.erase(it->second);
      }
    }

    element_to_group_[element] = group;
    group_to_elements_[group].insert(element);
    return true;
  }
