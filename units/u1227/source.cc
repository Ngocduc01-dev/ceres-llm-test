// u1227 – ceres::internal::(anonymous)::InitializeContext
// Trích từ internal/ceres/problem_impl.cc, dòng 108–118 (chỉ để xem, không compile)

void InitializeContext(Context* context,
                       ContextImpl** context_impl,
                       bool* context_impl_owned) {
  if (context == nullptr) {
    *context_impl_owned = true;
    *context_impl = new ContextImpl;
  } else {
    *context_impl_owned = false;
    *context_impl = down_cast<ContextImpl*>(context);
  }
}
