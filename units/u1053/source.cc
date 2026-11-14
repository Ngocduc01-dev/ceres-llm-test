// u1053 – ceres::OrderedGroups::Reverse
// Trích từ include/ceres/ordered_groups.h, dòng 125–144 (chỉ để xem, không compile)

  void Reverse() {
    if (NumGroups() == 0) {
      return;
    }

    auto it = group_to_elements_.rbegin();
    std::map<int, std::set<T>> new_group_to_elements;
    new_group_to_elements[it->first] = it->second;

    int new_group_id = it->first + 1;
    for (++it; it != group_to_elements_.rend(); ++it) {
      for (const auto& element : it->second) {
        element_to_group_[element] = new_group_id;
      }
      new_group_to_elements[new_group_id] = it->second;
      new_group_id++;
    }

    group_to_elements_.swap(new_group_to_elements);
  }
