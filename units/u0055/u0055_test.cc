// FILE: u0055_test.cc
#include <array>
#include <cstddef>
#include <iterator>
#include <memory>
#include <tuple>
#include <algorithm>
#include <limits>
#include <new>
#include <type_traits>
#include <utility>

#define private public
#define protected public
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#undef private
#undef protected

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(FixedArrayStorageAlloc, P1_ReturnAllocator) {
  using Array = ceres::internal::FixedArray<int, 20>;
  using Storage = Array::Storage;
  using Alloc = std::allocator<int>;

  const std::size_t n = 3;  // thuộc khoảng [1, 5]
  Alloc a;
  Storage storage(n, a);

  Alloc& result = storage.alloc();
  (void)result;  // không kiểm tra kết quả trả về
}
