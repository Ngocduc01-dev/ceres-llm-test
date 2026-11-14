// u1148 – ceres::Context::Create
// Trích từ internal/ceres/context.cc, dòng 38–38 (chỉ để xem, không compile)

Context* Context::Create() { return new internal::ContextImpl(); }
