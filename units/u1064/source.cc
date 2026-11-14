// u1064 – ceres::internal::FixedArray::Storage::InitializeData
// Trích từ include/ceres/internal/fixed_array.h, dòng 437–445 (chỉ để xem, không compile)

    StorageElement* InitializeData() {
      if (UsingInlinedStorage(size())) {
        InlinedStorage::AnnotateConstruct(size());
        return InlinedStorage::data();
      } else {
        return reinterpret_cast<StorageElement*>(
            AllocatorTraits::allocate(alloc(), size()));
      }
    }
