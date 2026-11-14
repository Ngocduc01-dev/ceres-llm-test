// u0600 – ceres::internal::(anonymous)::STLDeleteContainerPairFirstPointers
// Trích từ internal/ceres/problem_impl.cc, dòng 99–106 (chỉ để xem, không compile)

template <typename ForwardIterator>
void STLDeleteContainerPairFirstPointers(ForwardIterator begin,
                                         ForwardIterator end) {
  while (begin != end) {
    delete begin->first;
    ++begin;
  }
}
