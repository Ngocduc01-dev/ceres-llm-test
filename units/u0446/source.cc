// u0446 – ceres::internal::ArraySelector::ArraySelector<type-parameter-0-0, num_elements, max_num_elements_on_stack, false, false>
// Trích từ include/ceres/internal/array_selector.h, dòng 88–90 (chỉ để xem, không compile)

  explicit ArraySelector(int s) : std::vector<T>(s) {
    CHECK_EQ(s, num_elements);
  }
