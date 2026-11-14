// u0523 – ceres::down_cast
// Trích từ internal/ceres/casts.h, dòng 89–104 (chỉ để xem, không compile)

template <typename To, typename From>  // use like this: down_cast<T*>(foo);
inline To down_cast(From* f) {         // so we only accept pointers
  // Ensures that To is a sub-type of From *.  This test is here only
  // for compile-time type checking, and has no overhead in an
  // optimized build at run-time, as it will be optimized away
  // completely.

  // TODO(csilvers): This should use COMPILE_ASSERT.
  if (false) {
    implicit_cast<From*, To>(nullptr);
  }

  // uses RTTI in dbg and fastbuild. asserts are disabled in opt builds.
  assert(f == nullptr || dynamic_cast<To>(f) != nullptr);  // NOLINT
  return static_cast<To>(f);
}
