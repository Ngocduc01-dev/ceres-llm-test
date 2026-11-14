// u0725 – ceres::internal::ReadFileToStringOrDie
// Trích từ internal/ceres/file.cc, dòng 52–74 (chỉ để xem, không compile)

void ReadFileToStringOrDie(const std::string& filename, std::string* data) {
  FILE* file_descriptor = fopen(filename.c_str(), "r");

  if (!file_descriptor) {
    LOG(FATAL) << "Couldn't read file: " << filename;
  }

  // Resize the input buffer appropriately.
  fseek(file_descriptor, 0L, SEEK_END);
  int64_t num_bytes = ftell(file_descriptor);
  data->resize(num_bytes);

  // Read the data.
  fseek(file_descriptor, 0L, SEEK_SET);
  int64_t num_read =
      fread(&((*data)[0]), sizeof((*data)[0]), num_bytes, file_descriptor);
  if (num_read != num_bytes) {
    LOG(FATAL) << "Couldn't read all of " << filename
               << "expected bytes: " << num_bytes * sizeof((*data)[0])
               << "actual bytes: " << num_read;
  }
  fclose(file_descriptor);
}
