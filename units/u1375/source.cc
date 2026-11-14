// u1375 – ceres::internal::(anonymous)::DumpLinearLeastSquaresProblemToTextFile
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 966–1020 (chỉ để xem, không compile)

bool DumpLinearLeastSquaresProblemToTextFile(const std::string& filename_base,
                                             const SparseMatrix* A,
                                             const double* D,
                                             const double* b,
                                             const double* x,
                                             int /*num_eliminate_blocks*/) {
  CHECK(A != nullptr);
  LOG(INFO) << "writing to: " << filename_base << "*";

  std::string matlab_script;
  StringAppendF(&matlab_script,
                "function lsqp = load_trust_region_problem()\n");
  StringAppendF(&matlab_script, "lsqp.num_rows = %d;\n", A->num_rows());
  StringAppendF(&matlab_script, "lsqp.num_cols = %d;\n", A->num_cols());

  {
    std::string filename = filename_base + "_A.txt";
    FILE* fptr = fopen(filename.c_str(), "w");
    CHECK(fptr != nullptr);
    A->ToTextFile(fptr);
    fclose(fptr);
    StringAppendF(
        &matlab_script, "tmp = load('%s', '-ascii');\n", filename.c_str());
    StringAppendF(
        &matlab_script,
        "lsqp.A = sparse(tmp(:, 1) + 1, tmp(:, 2) + 1, tmp(:, 3), %d, %d);\n",
        A->num_rows(),
        A->num_cols());
  }

  if (D != nullptr) {
    std::string filename = filename_base + "_D.txt";
    WriteArrayToFileOrDie(filename, D, A->num_cols());
    StringAppendF(
        &matlab_script, "lsqp.D = load('%s', '-ascii');\n", filename.c_str());
  }

  if (b != nullptr) {
    std::string filename = filename_base + "_b.txt";
    WriteArrayToFileOrDie(filename, b, A->num_rows());
    StringAppendF(
        &matlab_script, "lsqp.b = load('%s', '-ascii');\n", filename.c_str());
  }

  if (x != nullptr) {
    std::string filename = filename_base + "_x.txt";
    WriteArrayToFileOrDie(filename, x, A->num_cols());
    StringAppendF(
        &matlab_script, "lsqp.x = load('%s', '-ascii');\n", filename.c_str());
  }

  std::string matlab_filename = filename_base + ".m";
  WriteStringToFileOrDie(matlab_script, matlab_filename);
  return true;
}
