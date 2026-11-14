// u0488 – ceres::STLDeleteUniqueContainerPointers
// Trích từ internal/ceres/stl_util.h, dòng 59–69 (chỉ để xem, không compile)

template <class ForwardIterator>
void STLDeleteUniqueContainerPointers(ForwardIterator begin,
                                      ForwardIterator end) {
  sort(begin, end);
  ForwardIterator new_end = unique(begin, end);
  while (begin != new_end) {
    ForwardIterator temp = begin;
    ++begin;
    delete *temp;
  }
}
