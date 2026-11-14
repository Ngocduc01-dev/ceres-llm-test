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
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `Create(const LinearSolver::Options & options, const BlockSparseMatrix & matrix)`, trả về `std::unique_ptr<PartitionedMatrixViewBase>`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::PartitionedMatrixViewBase`
- Vị trí: `internal/ceres/partitioned_matrix_view.cc`, dòng 51–183

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 51 | std::unique_ptr<PartitionedMatrixViewBase> PartitionedMatrixViewBase::Create(
 52 |     const LinearSolver::Options& options, const BlockSparseMatrix& matrix) {
 53 | #ifndef CERES_RESTRICT_SCHUR_SPECIALIZATION
 54 |   if ((options.row_block_size == 2) &&
 55 |      (options.e_block_size == 2) &&
 56 |      (options.f_block_size == 2)) {
 57 |     return std::make_unique<PartitionedMatrixView<2,2, 2>>(
 58 |                    options, matrix);
 59 |   }
 60 |   if ((options.row_block_size == 2) &&
 61 |      (options.e_block_size == 2) &&
 62 |      (options.f_block_size == 3)) {
 63 |     return std::make_unique<PartitionedMatrixView<2,2, 3>>(
 64 |                    options, matrix);
 65 |   }
 66 |   if ((options.row_block_size == 2) &&
 67 |      (options.e_block_size == 2) &&
 68 |      (options.f_block_size == 4)) {
 69 |     return std::make_unique<PartitionedMatrixView<2,2, 4>>(
 70 |                    options, matrix);
 71 |   }
 72 |   if ((options.row_block_size == 2) &&
 73 |      (options.e_block_size == 2)) {
 74 |     return std::make_unique<PartitionedMatrixView<2,2, Eigen::Dynamic>>(
 75 |                    options, matrix);
 76 |   }
 77 |   if ((options.row_block_size == 2) &&
 78 |      (options.e_block_size == 3) &&
 79 |      (options.f_block_size == 3)) {
 80 |     return std::make_unique<PartitionedMatrixView<2,3, 3>>(
 81 |                    options, matrix);
 82 |   }
 83 |   if ((options.row_block_size == 2) &&
 84 |      (options.e_block_size == 3) &&
 85 |      (options.f_block_size == 4)) {
 86 |     return std::make_unique<PartitionedMatrixView<2,3, 4>>(
 87 |                    options, matrix);
 88 |   }
 89 |   if ((options.row_block_size == 2) &&
 90 |      (options.e_block_size == 3) &&
 91 |      (options.f_block_size == 6)) {
 92 |     return std::make_unique<PartitionedMatrixView<2,3, 6>>(
 93 |                    options, matrix);
 94 |   }
 95 |   if ((options.row_block_size == 2) &&
 96 |      (options.e_block_size == 3) &&
 97 |      (options.f_block_size == 9)) {
 98 |     return std::make_unique<PartitionedMatrixView<2,3, 9>>(
 99 |                    options, matrix);
100 |   }
101 |   if ((options.row_block_size == 2) &&
102 |      (options.e_block_size == 3)) {
103 |     return std::make_unique<PartitionedMatrixView<2,3, Eigen::Dynamic>>(
104 |                    options, matrix);
105 |   }
106 |   if ((options.row_block_size == 2) &&
107 |      (options.e_block_size == 4) &&
108 |      (options.f_block_size == 3)) {
109 |     return std::make_unique<PartitionedMatrixView<2,4, 3>>(
110 |                    options, matrix);
111 |   }
112 |   if ((options.row_block_size == 2) &&
113 |      (options.e_block_size == 4) &&
114 |      (options.f_block_size == 4)) {
115 |     return std::make_unique<PartitionedMatrixView<2,4, 4>>(
116 |                    options, matrix);
117 |   }
118 |   if ((options.row_block_size == 2) &&
119 |      (options.e_block_size == 4) &&
120 |      (options.f_block_size == 6)) {
121 |     return std::make_unique<PartitionedMatrixView<2,4, 6>>(
122 |                    options, matrix);
123 |   }
124 |   if ((options.row_block_size == 2) &&
125 |      (options.e_block_size == 4) &&
126 |      (options.f_block_size == 8)) {
127 |     return std::make_unique<PartitionedMatrixView<2,4, 8>>(
128 |                    options, matrix);
129 |   }
130 |   if ((options.row_block_size == 2) &&
131 |      (options.e_block_size == 4) &&
132 |      (options.f_block_size == 9)) {
133 |     return std::make_unique<PartitionedMatrixView<2,4, 9>>(
134 |                    options, matrix);
135 |   }
136 |   if ((options.row_block_size == 2) &&
137 |      (options.e_block_size == 4)) {
138 |     return std::make_unique<PartitionedMatrixView<2,4, Eigen::Dynamic>>(
139 |                    options, matrix);
140 |   }
141 |   if (options.row_block_size == 2) {
142 |     return std::make_unique<PartitionedMatrixView<2,Eigen::Dynamic, Eigen::Dynamic>>(
143 |                    options, matrix);
144 |   }
145 |   if ((options.row_block_size == 3) &&
146 |      (options.e_block_size == 3) &&
147 |      (options.f_block_size == 3)) {
148 |     return std::make_unique<PartitionedMatrixView<3,3, 3>>(
149 |                    options, matrix);
150 |   }
151 |   if ((options.row_block_size == 4) &&
152 |      (options.e_block_size == 4) &&
153 |      (options.f_block_size == 2)) {
154 |     return std::make_unique<PartitionedMatrixView<4,4, 2>>(
155 |                    options, matrix);
156 |   }
157 |   if ((options.row_block_size == 4) &&
158 |      (options.e_block_size == 4) &&
159 |      (options.f_block_size == 3)) {
160 |     return std::make_unique<PartitionedMatrixView<4,4, 3>>(
161 |                    options, matrix);
162 |   }
163 |   if ((options.row_block_size == 4) &&
164 |      (options.e_block_size == 4) &&
165 |      (options.f_block_size == 4)) {
166 |     return std::make_unique<PartitionedMatrixView<4,4, 4>>(
167 |                    options, matrix);
168 |   }
169 |   if ((options.row_block_size == 4) &&
170 |      (options.e_block_size == 4)) {
171 |     return std::make_unique<PartitionedMatrixView<4,4, Eigen::Dynamic>>(
172 |                    options, matrix);
173 |   }
174 | 
175 | #endif
176 |   VLOG(1) << "Template specializations not found for <"
177 |           << options.row_block_size << "," << options.e_block_size << ","
178 |           << options.f_block_size << ">";
179 |   return std::make_unique<PartitionedMatrixView<Eigen::Dynamic,
180 |                                                 Eigen::Dynamic,
181 |                                                 Eigen::Dynamic>>(
182 |       options, matrix);
183 | };
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 0

START → END
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
#include "ceres/block_sparse_matrix.h"
#include "ceres/linear_solver.h"
#include "ceres/partitioned_matrix_view.h"
```

- Đây là method của class `ceres::internal::PartitionedMatrixViewBase`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `PartitionedMatrixViewBase`:
- Class không tự khai báo constructor → tạo bằng constructor mặc định: `PartitionedMatrixViewBase obj;`
- Class có hàm **thuần ảo** (chưa có code, phải viết ở class con) nên không tạo object trực tiếp được: viết một class con kế thừa và viết các hàm: `LeftMultiplyAndAccumulateE(const double *, double *)`, `LeftMultiplyAndAccumulateESingleThreaded(const double *, double *)`, `LeftMultiplyAndAccumulateEMultiThreaded(const double *, double *)`, `LeftMultiplyAndAccumulateF(const double *, double *)`, `LeftMultiplyAndAccumulateFSingleThreaded(const double *, double *)`, `LeftMultiplyAndAccumulateFMultiThreaded(const double *, double *)`, `RightMultiplyAndAccumulateE(const double *, double *)`, `RightMultiplyAndAccumulateF(const double *, double *)`, `CreateBlockDiagonalEtE()`, `CreateBlockDiagonalFtF()`, `UpdateBlockDiagonalEtE(BlockSparseMatrix *)`, `UpdateBlockDiagonalFtF(BlockSparseMatrix *)`, `num_col_blocks_e()`, `num_col_blocks_f()`, `num_cols_e()`, `num_cols_f()`, `num_rows()`, `num_cols()`, `e_cols_partition()`, `f_cols_partition()`.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0922_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
