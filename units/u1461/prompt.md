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

- Hàm: `SolveImpl(BlockSparseMatrix * A, const double * b, const LinearSolver::PerSolveOptions & per_solve_options, double * x)`, trả về `LinearSolver::Summary`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::IterativeSchurComplementSolver`
- Vị trí: `internal/ceres/iterative_schur_complement_solver.cc`, dòng 63–156

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 63 | LinearSolver::Summary IterativeSchurComplementSolver::SolveImpl(
 64 |     BlockSparseMatrix* A,
 65 |     const double* b,
 66 |     const LinearSolver::PerSolveOptions& per_solve_options,
 67 |     double* x) {
 68 |   EventLogger event_logger("IterativeSchurComplementSolver::Solve");
 69 | 
 70 |   CHECK(A->block_structure() != nullptr);
 71 |   CHECK(A->transpose_block_structure() != nullptr);
 72 | 
 73 |   const int num_eliminate_blocks = options_.elimination_groups[0];
 74 |   // Initialize a ImplicitSchurComplement object.
 75 |   if (schur_complement_ == nullptr) {
 76 |     DetectStructure(*(A->block_structure()),
 77 |                     num_eliminate_blocks,
 78 |                     &options_.row_block_size,
 79 |                     &options_.e_block_size,
 80 |                     &options_.f_block_size);
 81 |     schur_complement_ = std::make_unique<ImplicitSchurComplement>(options_);
 82 |   }
 83 |   schur_complement_->Init(*A, per_solve_options.D, b);
 84 | 
 85 |   const int num_schur_complement_blocks =
 86 |       A->block_structure()->cols.size() - num_eliminate_blocks;
 87 |   if (num_schur_complement_blocks == 0) {
 88 |     VLOG(2) << "No parameter blocks left in the schur complement.";
 89 |     LinearSolver::Summary summary;
 90 |     summary.num_iterations = 0;
 91 |     summary.termination_type = LinearSolverTerminationType::SUCCESS;
 92 |     schur_complement_->BackSubstitute(nullptr, x);
 93 |     return summary;
 94 |   }
 95 | 
 96 |   // Initialize the solution to the Schur complement system.
 97 |   reduced_linear_system_solution_.resize(schur_complement_->num_rows());
 98 |   reduced_linear_system_solution_.setZero();
 99 |   if (options_.use_spse_initialization) {
100 |     Preconditioner::Options preconditioner_options(options_);
101 |     preconditioner_options.type = SCHUR_POWER_SERIES_EXPANSION;
102 |     PowerSeriesExpansionPreconditioner pse_solver(
103 |         schur_complement_.get(),
104 |         options_.max_num_spse_iterations,
105 |         options_.spse_tolerance,
106 |         preconditioner_options);
107 |     pse_solver.RightMultiplyAndAccumulate(
108 |         schur_complement_->rhs().data(),
109 |         reduced_linear_system_solution_.data());
110 |   }
111 | 
112 |   CreatePreconditioner(A);
113 |   if (preconditioner_ != nullptr) {
114 |     if (!preconditioner_->Update(*A, per_solve_options.D)) {
115 |       LinearSolver::Summary summary;
116 |       summary.num_iterations = 0;
117 |       summary.termination_type = LinearSolverTerminationType::FAILURE;
118 |       summary.message = "Preconditioner update failed.";
119 |       return summary;
120 |     }
121 |   }
122 | 
123 |   ConjugateGradientsSolverOptions cg_options;
124 |   cg_options.min_num_iterations = options_.min_num_iterations;
125 |   cg_options.max_num_iterations = options_.max_num_iterations;
126 |   cg_options.residual_reset_period = options_.residual_reset_period;
127 |   cg_options.q_tolerance = per_solve_options.q_tolerance;
128 |   cg_options.r_tolerance = per_solve_options.r_tolerance;
129 | 
130 |   LinearOperatorAdapter lhs(*schur_complement_);
131 |   LinearOperatorAdapter preconditioner(*preconditioner_);
132 | 
133 |   Vector scratch[4];
134 |   for (int i = 0; i < 4; ++i) {
135 |     scratch[i].resize(schur_complement_->num_cols());
136 |   }
137 |   Vector* scratch_ptr[4] = {&scratch[0], &scratch[1], &scratch[2], &scratch[3]};
138 | 
139 |   event_logger.AddEvent("Setup");
140 | 
141 |   LinearSolver::Summary summary =
142 |       ConjugateGradientsSolver(cg_options,
143 |                                lhs,
144 |                                schur_complement_->rhs(),
145 |                                preconditioner,
146 |                                scratch_ptr,
147 |                                reduced_linear_system_solution_);
148 | 
149 |   if (summary.termination_type != LinearSolverTerminationType::FAILURE &&
150 |       summary.termination_type != LinearSolverTerminationType::FATAL_ERROR) {
151 |     schur_complement_->BackSubstitute(reduced_linear_system_solution_.data(),
152 |                                       x);
153 |   }
154 |   event_logger.AddEvent("Solve");
155 |   return summary;
156 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 7 (và 2 lệnh CHECK)

START → 1
1   "IterativeSchurComplementSolver::Solve"                        → 2
2   CHECK(A->block_structure() != nullptr)                         đúng → 3   sai → DỪNG
3   CHECK(A->transpose_block_structure() != nullptr)               đúng → 4   sai → DỪNG
4   const int num_eliminate_blocks = options_.elimination_groups[0]   → 5
5   if (schur_complement_ == nullptr)                              đúng → 6   sai → 7
6   DetectStructure(*(A->block_structure()), num_eliminate_blocks, &options_.row_block_size, &options_.e_block_size, &options_.f_block_size)
    schur_complement_ = std::make_unique<ImplicitSchurComplement>(options_)   → 7
7   schur_complement_->Init(*A, per_solve_options.D, b)
    const int num_schur_complement_blocks = A->block_structure()->cols.size() - num_eliminate_blocks   → 8
8   if (num_schur_complement_blocks == 0)                          đúng → END   sai → 9
9   reduced_linear_system_solution_.resize(schur_complement_->num_rows())
    reduced_linear_system_solution_.setZero()                      → 10
10  if (options_.use_spse_initialization)                          đúng → 11   sai → 12
11  preconditioner_options.type = SCHUR_POWER_SERIES_EXPANSION
    schur_complement_.get(), options_.max_num_spse_iterations, options_.spse_tolerance, preconditioner_options
    pse_solver.RightMultiplyAndAccumulate(schur_complement_->rhs().data(), reduced_linear_system_solution_.data())   → 12
12  CreatePreconditioner(A)                                        → 13
13  if (preconditioner_ != nullptr)                                đúng → 14   sai → 16
14  if (!preconditioner_->Update(*A, per_solve_options.D))         đúng → 15   sai → 16
15  summary.num_iterations = 0
    summary.termination_type = LinearSolverTerminationType::FAILURE
    summary.message = "Preconditioner update failed."              → END
16  cg_options.min_num_iterations = options_.min_num_iterations
    cg_options.max_num_iterations = options_.max_num_iterations
    cg_options.residual_reset_period = options_.residual_reset_period
    cg_options.q_tolerance = per_solve_options.q_tolerance
    cg_options.r_tolerance = per_solve_options.r_tolerance
    operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    * schur_complement_
    operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    * preconditioner_
    int i = 0                                                      → 17
17  vòng for, điều kiện: i < 4                                     đúng → 18   sai → 20
18  scratch[i].resize(schur_complement_->num_cols())               → 19
19  ++i                                                            → 17
20  Vector *scratch_ptr[4] = {&scratch[0], &scratch[1], &scratch[2], &scratch[3]}
    event_logger.AddEvent("Setup")                                 → 21
21  if (summary.termination_type != LinearSolverTerminationType::FAILURE && summary.termination_type != LinearSolverTerminationType::FATAL_ERROR)   đúng → 22   sai → 23
22  schur_complement_->BackSubstitute(reduced_linear_system_solution_.data(), x)   → 23
23  event_logger.AddEvent("Solve")                                 → END
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
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/power_series_expansion_preconditioner.h"
#include "ceres/preconditioner.h"
#include "ceres/wall_time.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::IterativeSchurComplementSolver`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `IterativeSchurComplementSolver`:
Các constructor:
```cpp
  IterativeSchurComplementSolver(LinearSolver::Options options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1461_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
