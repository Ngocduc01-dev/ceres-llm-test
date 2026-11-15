# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM

- **CFG (đồ thị luồng điều khiển):** sơ đồ các bước của hàm. Mỗi **node** là một đoạn lệnh chạy liền nhau hoặc một chỗ rẽ nhánh; mũi tên nối các node theo thứ tự chạy.
- **Điểm rẽ nhánh:** chỗ chương trình chọn đường đi theo một điều kiện: `if`, `else if`, vòng `for` / `while`, `switch`, `?:`. Mỗi điểm rẽ nhánh có **2 nhánh**: điều kiện **đúng** và điều kiện **sai** (`switch` có 1 nhánh cho mỗi `case`).
- **Độ phủ C2 (phủ nhánh):** mọi nhánh của mọi điểm rẽ nhánh đều được chạy qua ít nhất 1 lần.
  **C2 = số nhánh đã chạy qua / tổng số nhánh × 100%.**
  (C2 chặt hơn C1 – chỉ yêu cầu mỗi câu lệnh chạy ít nhất 1 lần. Ví dụ `if (x > 0) y = 1;`: chỉ cần x > 0 là đạt C1, nhưng C2 cần thêm 1 test với x ≤ 0.)
  Điều kiện ghép như `a && b`, `a || b` được tính là **một** điểm rẽ nhánh.
- **Test path (đường kiểm thử):** một đường đi trên CFG, từ `START` tới `END`, ghi rõ ở mỗi điểm rẽ nhánh đi theo nhánh nào.
- **Điều kiện của đường đi:** các điều kiện phải đúng/sai dọc theo một test path. Dữ liệu đầu vào của test phải thoả các điều kiện này.
- **Nhánh không thể đi tới:** nhánh mà không có dữ liệu nào làm chương trình đi vào (ví dụ điều kiện mâu thuẫn). Ghi rõ lý do, vẫn tính vào tổng số nhánh.
- **Tổng số nhánh** (mẫu số của C2) = 2 × số điểm rẽ nhánh ghi ở dòng đầu CFG (`switch`: mỗi `case` là 1 nhánh). **Không** tính nhánh của `CHECK`.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `DumpLinearLeastSquaresProblemToTextFile(const std::string & filename_base, const SparseMatrix * A, const double * D, const double * b, const double * x, int)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal::(namespace không tên)`
- Vị trí: `internal/ceres/linear_least_squares_problems.cc`, dòng 966–1020

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 966 | bool DumpLinearLeastSquaresProblemToTextFile(const std::string& filename_base,
 967 |                                              const SparseMatrix* A,
 968 |                                              const double* D,
 969 |                                              const double* b,
 970 |                                              const double* x,
 971 |                                              int /*num_eliminate_blocks*/) {
 972 |   CHECK(A != nullptr);
 973 |   LOG(INFO) << "writing to: " << filename_base << "*";
 974 | 
 975 |   std::string matlab_script;
 976 |   StringAppendF(&matlab_script,
 977 |                 "function lsqp = load_trust_region_problem()\n");
 978 |   StringAppendF(&matlab_script, "lsqp.num_rows = %d;\n", A->num_rows());
 979 |   StringAppendF(&matlab_script, "lsqp.num_cols = %d;\n", A->num_cols());
 980 | 
 981 |   {
 982 |     std::string filename = filename_base + "_A.txt";
 983 |     FILE* fptr = fopen(filename.c_str(), "w");
 984 |     CHECK(fptr != nullptr);
 985 |     A->ToTextFile(fptr);
 986 |     fclose(fptr);
 987 |     StringAppendF(
 988 |         &matlab_script, "tmp = load('%s', '-ascii');\n", filename.c_str());
 989 |     StringAppendF(
 990 |         &matlab_script,
 991 |         "lsqp.A = sparse(tmp(:, 1) + 1, tmp(:, 2) + 1, tmp(:, 3), %d, %d);\n",
 992 |         A->num_rows(),
 993 |         A->num_cols());
 994 |   }
 995 | 
 996 |   if (D != nullptr) {
 997 |     std::string filename = filename_base + "_D.txt";
 998 |     WriteArrayToFileOrDie(filename, D, A->num_cols());
 999 |     StringAppendF(
1000 |         &matlab_script, "lsqp.D = load('%s', '-ascii');\n", filename.c_str());
1001 |   }
1002 | 
1003 |   if (b != nullptr) {
1004 |     std::string filename = filename_base + "_b.txt";
1005 |     WriteArrayToFileOrDie(filename, b, A->num_rows());
1006 |     StringAppendF(
1007 |         &matlab_script, "lsqp.b = load('%s', '-ascii');\n", filename.c_str());
1008 |   }
1009 | 
1010 |   if (x != nullptr) {
1011 |     std::string filename = filename_base + "_x.txt";
1012 |     WriteArrayToFileOrDie(filename, x, A->num_cols());
1013 |     StringAppendF(
1014 |         &matlab_script, "lsqp.x = load('%s', '-ascii');\n", filename.c_str());
1015 |   }
1016 | 
1017 |   std::string matlab_filename = filename_base + ".m";
1018 |   WriteStringToFileOrDie(matlab_script, matlab_filename);
1019 |   return true;
1020 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3 (và 2 lệnh CHECK)

START → 1
1   CHECK(A != nullptr)                                            đúng → 2   sai → DỪNG
2   StringAppendF(&matlab_script, "function lsqp = load_trust_region_problem()\n")
    StringAppendF(&matlab_script, "lsqp.num_rows = %d;\n", A->num_rows())
    StringAppendF(&matlab_script, "lsqp.num_cols = %d;\n", A->num_cols())
    FILE *fptr = fopen(filename.c_str(), "w")                      → 3
3   CHECK(fptr != nullptr)                                         đúng → 4   sai → DỪNG
4   A->ToTextFile(fptr)
    fclose(fptr)
    StringAppendF(&matlab_script, "tmp = load('%s', '-ascii');\n", filename.c_str())
    StringAppendF(&matlab_script, "lsqp.A = sparse(tmp(:, 1) + 1, tmp(:, 2) + 1, tmp(:, 3), %d, %d);\n", A->num_rows(), A->num_cols())   → 5
5   if (D != nullptr)                                              đúng → 6   sai → 7
6   WriteArrayToFileOrDie(filename, D, A->num_cols())
    StringAppendF(&matlab_script, "lsqp.D = load('%s', '-ascii');\n", filename.c_str())   → 7
7   if (b != nullptr)                                              đúng → 8   sai → 9
8   WriteArrayToFileOrDie(filename, b, A->num_rows())
    StringAppendF(&matlab_script, "lsqp.b = load('%s', '-ascii');\n", filename.c_str())   → 9
9   if (x != nullptr)                                              đúng → 10   sai → 11
10  WriteArrayToFileOrDie(filename, x, A->num_cols())
    StringAppendF(&matlab_script, "lsqp.x = load('%s', '-ascii');\n", filename.c_str())   → 11
11  WriteStringToFileOrDie(matlab_script, matlab_filename)
    return true                                                    → END
```

**Cách đọc:** dòng đầu cho biết hàm có bao nhiêu điểm rẽ nhánh. Mỗi dòng sau đó là **một node**: số node, nội dung (câu lệnh hoặc điều kiện), rồi mũi tên tới node tiếp theo. Dòng "Ghi chú" (nếu có) cho biết unit là template và CFG được dựng với kiểu dữ liệu cụ thể nào.
- Node có điều kiện ghi `đúng → x   sai → y`: điều kiện đúng thì đi tới node x, sai thì đi tới node y.
- `START`: bắt đầu hàm · `END`: kết thúc hàm · `DỪNG`: chương trình dừng do `CHECK` sai.
- Nếu thấy CFG không khớp với mã nguồn, **tin mã nguồn** và ghi chú lại.
- Khi trả lời, gọi các node bằng **đúng số node này**.

## 3.3. Cách gọi unit trong file test

Các dòng `#include` được dùng:
```cpp
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/sparse_matrix.h"
#include "ceres/linear_least_squares_problems.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/linear_least_squares_problems.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/linear_least_squares_problems.cc"` vào file test.

---

# 4. YÊU CẦU ĐỐI VỚI BỘ TEST

1. Mỗi nhánh (đúng và sai) của mỗi điểm rẽ nhánh có **ít nhất 1 test** đi qua.
2. Mỗi vòng lặp được test với số lần lặp như mục 2.
3. Mỗi test ứng với **một test path**, ghi rõ các nhánh nó đi qua (ví dụ `node 2: đúng, node 4: sai`).
4. Dùng **ít test nhất** có thể: một test nên đi qua nhiều nhánh chưa được phủ.
5. **Dữ liệu đầu vào:** từ điều kiện của đường đi, xác định **khoảng giá trị** hợp lệ cho từng đầu vào (ví dụ `n` từ 1 đến 5), rồi **chọn ngẫu nhiên một giá trị** trong khoảng đó. Nếu dùng hàm sinh số ngẫu nhiên trong code thì **cố định giá trị khởi tạo (seed)** để mỗi lần chạy ra cùng một giá trị. Mảng, ma trận nhỏ (tối đa 5 phần tử). Không dùng file, mạng, đa luồng.
6. **Không** kiểm tra kết quả trả về (không có kết quả đúng để so).

---

# 5. CÁC BƯỚC THỰC HIỆN

1. Đọc mã nguồn và CFG của unit.
2. Liệt kê các điểm rẽ nhánh và các nhánh cần phủ.
3. Chọn các test path sao cho phủ hết các nhánh (trừ nhánh không thể đi tới và nhánh `CHECK` sai).
4. Với mỗi test path: viết điều kiện của đường đi → khoảng giá trị đầu vào → chọn giá trị ngẫu nhiên trong khoảng.
5. Viết code GoogleTest: mỗi test chuẩn bị dữ liệu rồi gọi unit **một lần**.
6. Kiểm tra lại: mọi nhánh đã có test chưa, code có dùng đúng tên hàm và `#include` ở mục 3.3 không.

---

# 6. KẾT QUẢ CẦN TRẢ VỀ

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → … → END | node 1: đúng, node 2: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | … | … |

**C. Nhánh không test** (nếu có): nhánh nào, vì sao. Kèm 1 dòng: `C2 dự kiến = <số nhánh có test> / <tổng số nhánh>` (dự kiến, chưa chạy thật).

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1375_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
