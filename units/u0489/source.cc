// u0489 – ceres::STLDeleteElements
// Trích từ internal/ceres/stl_util.h, dòng 81–86 (chỉ để xem, không compile)

template <class T>
void STLDeleteElements(T* container) {
  if (!container) return;
  STLDeleteContainerPointers(container->begin(), container->end());
  container->clear();
}
