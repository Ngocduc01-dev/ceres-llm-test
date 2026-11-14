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

- Hàm: `ComputeStep(const TrustRegionStrategy::PerSolveOptions & per_solve_options, SparseMatrix * jacobian, const double * residuals, double * step)`, trả về `TrustRegionStrategy::Summary`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::LevenbergMarquardtStrategy`
- Vị trí: `internal/ceres/levenberg_marquardt_strategy.cc`, dòng 68–155

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 68 | TrustRegionStrategy::Summary LevenbergMarquardtStrategy::ComputeStep(
 69 |     const TrustRegionStrategy::PerSolveOptions& per_solve_options,
 70 |     SparseMatrix* jacobian,
 71 |     const double* residuals,
 72 |     double* step) {
 73 |   CHECK(jacobian != nullptr);
 74 |   CHECK(residuals != nullptr);
 75 |   CHECK(step != nullptr);
 76 | 
 77 |   const int num_parameters = jacobian->num_cols();
 78 |   if (!reuse_diagonal_) {
 79 |     if (diagonal_.rows() != num_parameters) {
 80 |       diagonal_.resize(num_parameters, 1);
 81 |     }
 82 | 
 83 |     jacobian->SquaredColumnNorm(diagonal_.data(), context_, num_threads_);
 84 |     ParallelAssign(context_,
 85 |                    num_threads_,
 86 |                    diagonal_,
 87 |                    diagonal_.array().max(min_diagonal_).min(max_diagonal_));
 88 |   }
 89 | 
 90 |   if (lm_diagonal_.size() == 0) {
 91 |     lm_diagonal_.resize(num_parameters);
 92 |   }
 93 |   ParallelAssign(
 94 |       context_, num_threads_, lm_diagonal_, (diagonal_ / radius_).cwiseSqrt());
 95 | 
 96 |   LinearSolver::PerSolveOptions solve_options;
 97 |   solve_options.D = lm_diagonal_.data();
 98 |   solve_options.q_tolerance = per_solve_options.eta;
 99 |   // Disable r_tolerance checking. Since we only care about
100 |   // termination via the q_tolerance. As Nash and Sofer show,
101 |   // r_tolerance based termination is essentially useless in
102 |   // Truncated Newton methods.
103 |   solve_options.r_tolerance = -1.0;
104 | 
105 |   // Invalidate the output array lm_step, so that we can detect if
106 |   // the linear solver generated numerical garbage.  This is known
107 |   // to happen for the DENSE_QR and then DENSE_SCHUR solver when
108 |   // the Jacobian is severely rank deficient and mu is too small.
109 |   InvalidateArray(num_parameters, step);
110 | 
111 |   // Instead of solving Jx = -r, solve Jy = r.
112 |   // Then x can be found as x = -y, but the inputs jacobian and residuals
113 |   // do not need to be modified.
114 |   LinearSolver::Summary linear_solver_summary =
115 |       linear_solver_->Solve(jacobian, residuals, solve_options, step);
116 | 
117 |   if (linear_solver_summary.termination_type ==
118 |       LinearSolverTerminationType::FATAL_ERROR) {
119 |     LOG(WARNING) << "Linear solver fatal error: "
120 |                  << linear_solver_summary.message;
121 |   } else if (linear_solver_summary.termination_type ==
122 |              LinearSolverTerminationType::FAILURE) {
123 |     LOG(WARNING) << "Linear solver failure. Failed to compute a step: "
124 |                  << linear_solver_summary.message;
125 |   } else if (!IsArrayValid(num_parameters, step)) {
126 |     LOG(WARNING) << "Linear solver failure. Failed to compute a finite step.";
127 |     linear_solver_summary.termination_type =
128 |         LinearSolverTerminationType::FAILURE;
129 |   } else {
130 |     VectorRef step_vec(step, num_parameters);
131 |     ParallelAssign(context_, num_threads_, step_vec, -step_vec);
132 |   }
133 |   reuse_diagonal_ = true;
134 | 
135 |   if (per_solve_options.dump_format_type == CONSOLE ||
136 |       (per_solve_options.dump_format_type != CONSOLE &&
137 |        !per_solve_options.dump_filename_base.empty())) {
138 |     if (!DumpLinearLeastSquaresProblem(per_solve_options.dump_filename_base,
139 |                                        per_solve_options.dump_format_type,
140 |                                        jacobian,
141 |                                        solve_options.D,
142 |                                        residuals,
143 |                                        step,
144 |                                        0)) {
145 |       LOG(ERROR) << "Unable to dump trust region problem."
146 |                  << " Filename base: " << per_solve_options.dump_filename_base;
147 |     }
148 |   }
149 | 
150 |   TrustRegionStrategy::Summary summary;
151 |   summary.residual_norm = linear_solver_summary.residual_norm;
152 |   summary.num_iterations = linear_solver_summary.num_iterations;
153 |   summary.termination_type = linear_solver_summary.termination_type;
154 |   return summary;
155 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 8 (và 3 lệnh CHECK)

START → 1
1   CHECK(jacobian != nullptr)                                     đúng → 2   sai → DỪNG
2   CHECK(residuals != nullptr)                                    đúng → 3   sai → DỪNG
3   CHECK(step != nullptr)                                         đúng → 4   sai → DỪNG
4   const int num_parameters = jacobian->num_cols()                → 5
5   if (!reuse_diagonal_)                                          đúng → 6   sai → 9
6   if (diagonal_.rows() != num_parameters)                        đúng → 7   sai → 8
7   diagonal_.resize(num_parameters, 1)                            → 8
8   jacobian->SquaredColumnNorm(diagonal_.data(), context_, num_threads_)
    ParallelAssign(context_, num_threads_, diagonal_, diagonal_.array().max(min_diagonal_).min(max_diagonal_))   → 9
9   if (lm_diagonal_.size() == 0)                                  đúng → 10   sai → 11
10  lm_diagonal_.resize(num_parameters)                            → 11
11  ParallelAssign(context_, num_threads_, lm_diagonal_, (diagonal_ / radius_).cwiseSqrt())
    solve_options.D = lm_diagonal_.data()
    solve_options.q_tolerance = per_solve_options.eta
    solve_options.r_tolerance = -1.
    InvalidateArray(num_parameters, step)                          → 12
12  if (linear_solver_summary.termination_type == LinearSolverTerminationType::FATAL_ERROR)   đúng → 13   sai → 17
13  reuse_diagonal_ = true                                         → 14
14  if (per_solve_options.dump_format_type == CONSOLE || (per_solve_options.dump_format_type != CONSOLE && !per_solve_options.dump_filename_base.empty()))   đúng → 15   sai → 16
15  if (!DumpLinearLeastSquaresProblem(per_solve_options.dump_filename_base, per_solve_options.dump_format_type, jacobian, solve_options.D, residuals, step, 0))   đúng → 16   sai → 16
16  summary.residual_norm = linear_solver_summary.residual_norm
    summary.num_iterations = linear_solver_summary.num_iterations
    summary.termination_type = linear_solver_summary.termination_type   → END
17  if (linear_solver_summary.termination_type == LinearSolverTerminationType::FAILURE)   đúng → 13   sai → 18
18  if (!IsArrayValid(num_parameters, step))                       đúng → 13   sai → 19
19  step, num_parameters
    ParallelAssign(context_, num_threads_, step_vec, - step_vec)   → 13
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
#include "ceres/levenberg_marquardt_strategy.h"
#include "ceres/linear_solver.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_strategy.h"
```

- Đây là method của class `ceres::internal::LevenbergMarquardtStrategy`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `LevenbergMarquardtStrategy`:
Các constructor:
```cpp
  LevenbergMarquardtStrategy(const TrustRegionStrategy::Options & options)
```

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1489_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
