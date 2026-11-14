// u0544 – ceres::internal::ConstructRange
// Trích từ include/ceres/internal/memory.h, dòng 45–63 (chỉ để xem, không compile)

template <typename Allocator, typename Iterator, typename... Args>
void ConstructRange(Allocator& alloc,
                    Iterator first,
                    Iterator last,
                    const Args&... args) {
  for (Iterator cur = first; cur != last; ++cur) {
    CERES_INTERNAL_TRY {
      std::allocator_traits<Allocator>::construct(
          alloc, std::addressof(*cur), args...);
    }
    CERES_INTERNAL_CATCH_ANY {
      while (cur != first) {
        --cur;
        std::allocator_traits<Allocator>::destroy(alloc, std::addressof(*cur));
      }
      CERES_INTERNAL_RETHROW;
    }
  }
}
