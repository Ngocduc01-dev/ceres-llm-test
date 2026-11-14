// u0487 – ceres::STLDeleteContainerPointers
// Trích từ internal/ceres/stl_util.h, dòng 48–55 (chỉ để xem, không compile)

template <class ForwardIterator>
void STLDeleteContainerPointers(ForwardIterator begin, ForwardIterator end) {
  while (begin != end) {
    ForwardIterator temp = begin;
    ++begin;
    delete *temp;
  }
}
