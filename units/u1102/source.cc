// u1102 – ceres::OrderedGroups::Remove
// Trích từ include/ceres/ordered_groups.h, dòng 112–122 (chỉ để xem, không compile)

  int Remove(const std::vector<T>& elements) {
    if (NumElements() == 0 || elements.size() == 0) {
      return 0;
    }

    int num_removed = 0;
    for (int i = 0; i < elements.size(); ++i) {
      num_removed += Remove(elements[i]);
    }
    return num_removed;
  }
