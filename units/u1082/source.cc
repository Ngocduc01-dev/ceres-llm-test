// u1082 – ceres::internal::ScopedThreadToken::ScopedThreadToken
// Trích từ internal/ceres/scoped_thread_token.h, dòng 43–44 (chỉ để xem, không compile)

  explicit ScopedThreadToken(ThreadTokenProvider* provider)
      : provider_(provider), token_(provider->Acquire()) {}
