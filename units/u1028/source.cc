// u1028 – ceres::internal::FixedArray::Storage::~Storage
// Trích từ include/ceres/internal/fixed_array.h, dòng 419–425 (chỉ để xem, không compile)

    ~Storage() noexcept {
      if (UsingInlinedStorage(size())) {
        InlinedStorage::AnnotateDestruct(size());
      } else {
        AllocatorTraits::deallocate(alloc(), AsValueType(begin()), size());
      }
    }
