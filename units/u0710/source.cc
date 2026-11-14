// u0710 – ceres::internal::WriteStringToFileOrDie
// Trích từ internal/ceres/file.cc, dòng 42–50 (chỉ để xem, không compile)

void WriteStringToFileOrDie(const std::string& data,
                            const std::string& filename) {
  FILE* file_descriptor = fopen(filename.c_str(), "wb");
  if (!file_descriptor) {
    LOG(FATAL) << "Couldn't write to file: " << filename;
  }
  fwrite(data.c_str(), 1, data.size(), file_descriptor);
  fclose(file_descriptor);
}
