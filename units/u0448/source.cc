// u0448 – ceres::internal::FixedArray::~FixedArray<T, N, A>
// Trích từ include/ceres/internal/fixed_array.h, dòng 163–167 (chỉ để xem, không compile)

  ~FixedArray() noexcept {
    for (auto* cur = storage_.begin(); cur != storage_.end(); ++cur) {
      AllocatorTraits::destroy(storage_.alloc(), cur);
    }
  }
