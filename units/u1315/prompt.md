# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM CẦN DÙNG

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

- Hàm: `ReorderProgram(PreprocessedProblem * pp)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal::(namespace không tên)`
- Vị trí: `internal/ceres/trust_region_preprocessor.cc`, dòng 110–151

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
110 | bool ReorderProgram(PreprocessedProblem* pp) {
111 |   const Solver::Options& options = pp->options;
112 |   if (IsSchurType(options.linear_solver_type)) {
113 |     return ReorderProgramForSchurTypeLinearSolver(
114 |         options.linear_solver_type,
115 |         options.sparse_linear_algebra_library_type,
116 |         options.linear_solver_ordering_type,
117 |         pp->problem->parameter_map(),
118 |         options.linear_solver_ordering.get(),
119 |         pp->reduced_program.get(),
120 |         &pp->error);
121 |   }
122 | 
123 |   if (options.linear_solver_type == SPARSE_NORMAL_CHOLESKY &&
124 |       !options.dynamic_sparsity) {
125 |     return ReorderProgramForSparseCholesky(
126 |         options.sparse_linear_algebra_library_type,
127 |         options.linear_solver_ordering_type,
128 |         *options.linear_solver_ordering,
129 |         0, /* use all the rows of the jacobian */
130 |         pp->reduced_program.get(),
131 |         &pp->error);
132 |   }
133 | 
134 |   if (options.linear_solver_type == CGNR &&
135 |       options.preconditioner_type == SUBSET) {
136 |     pp->linear_solver_options.subset_preconditioner_start_row_block =
137 |         ReorderResidualBlocksByPartition(
138 |             options.residual_blocks_for_subset_preconditioner,
139 |             pp->reduced_program.get());
140 | 
141 |     return ReorderProgramForSparseCholesky(
142 |         options.sparse_linear_algebra_library_type,
143 |         options.linear_solver_ordering_type,
144 |         *options.linear_solver_ordering,
145 |         pp->linear_solver_options.subset_preconditioner_start_row_block,
146 |         pp->reduced_program.get(),
147 |         &pp->error);
148 |   }
149 | 
150 |   return true;
151 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3

START → 1
1   const Solver::Options &options = pp->options                   → 2
2   if (IsSchurType(options.linear_solver_type))                   đúng → 3   sai → 4
3   return ReorderProgramForSchurTypeLinearSolver(options.linear_solver_type, options.sparse_linear_algebra_library_type, options.linear_solver_ordering_type, pp->problem->parameter_map(), options.linear_solver_ordering.get(), pp->reduced_program.get(), &pp->error)   → END
4   if (options.linear_solver_type == SPARSE_NORMAL_CHOLESKY && !options.dynamic_sparsity)   đúng → 5   sai → 6
5   return ReorderProgramForSparseCholesky(options.sparse_linear_algebra_library_type, options.linear_solver_ordering_type, * options.linear_solver_ordering, 0, pp->reduced_program.get(), &pp->error)   → END
6   if (options.linear_solver_type == CGNR && options.preconditioner_type == SUBSET)   đúng → 7   sai → 8
7   pp->linear_solver_options.subset_preconditioner_start_row_block = ReorderResidualBlocksByPartition(options.residual_blocks_for_subset_preconditioner, pp->reduced_program.get())
    return ReorderProgramForSparseCholesky(options.sparse_linear_algebra_library_type, options.linear_solver_ordering_type, * options.linear_solver_ordering, pp->linear_solver_options.subset_preconditioner_start_row_block, pp->reduced_program.get(), &pp->error)   → END
8   return true                                                    → END
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
#include "ceres/trust_region_preprocessor.h"
#include "ceres/solver.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/reorder_program.h"
#include "ceres/trust_region_preprocessor.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/trust_region_preprocessor.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/trust_region_preprocessor.cc"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1315_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
