// u1101 – ceres::StringtoDumpFormatType
// Trích từ internal/ceres/types.cc, dòng 380–385 (chỉ để xem, không compile)

bool StringtoDumpFormatType(std::string value, DumpFormatType* type) {
  UpperCase(&value);
  STRENUM(CONSOLE);
  STRENUM(TEXTFILE);
  return false;
}
