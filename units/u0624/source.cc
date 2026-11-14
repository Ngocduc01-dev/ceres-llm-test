// u0624 – ceres::internal::ArraySelector::ArraySelector<type-parameter-0-0, num_elements, max_num_elements_on_stack, true, fits_on_stack>
// Trích từ include/ceres/internal/array_selector.h, dòng 75–76 (chỉ để xem, không compile)

  explicit ArraySelector(int s)
      : ceres::internal::FixedArray<T, max_num_elements_on_stack>(s) {}
