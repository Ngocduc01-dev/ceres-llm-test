// u1022 – ceres::internal::ScopedThreadToken::~ScopedThreadToken
// Trích từ internal/ceres/scoped_thread_token.h, dòng 46–46 (chỉ để xem, không compile)

  ~ScopedThreadToken() { provider_->Release(token_); }
