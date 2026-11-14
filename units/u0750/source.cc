// u0750 – ceres::internal::operator<<
// Trích từ internal/ceres/linear_solver.h, dòng 113–128 (chỉ để xem, không compile)

inline std::ostream& operator<<(std::ostream& s, OrderingType type) {
  switch (type) {
    case OrderingType::NATURAL:
      s << "NATURAL";
      break;
    case OrderingType::AMD:
      s << "AMD";
      break;
    case OrderingType::NESDIS:
      s << "NESDIS";
      break;
    default:
      s << "UNKNOWN OrderingType";
  }
  return s;
}
