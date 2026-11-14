// u0545 – ceres::internal::CopyRange
// Trích từ include/ceres/internal/memory.h, dòng 65–84 (chỉ để xem, không compile)

template <typename Allocator, typename Iterator, typename InputIterator>
void CopyRange(Allocator& alloc,
               Iterator destination,
               InputIterator first,
               InputIterator last) {
  for (Iterator cur = destination; first != last;
       static_cast<void>(++cur), static_cast<void>(++first)) {
    CERES_INTERNAL_TRY {
      std::allocator_traits<Allocator>::construct(
          alloc, std::addressof(*cur), *first);
    }
    CERES_INTERNAL_CATCH_ANY {
      while (cur != destination) {
        --cur;
        std::allocator_traits<Allocator>::destroy(alloc, std::addressof(*cur));
      }
      CERES_INTERNAL_RETHROW;
    }
  }
}
