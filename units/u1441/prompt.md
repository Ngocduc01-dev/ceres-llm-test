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

- Hàm: `SolveImpl(BlockSparseMatrix * A, const double * b, const LinearSolver::PerSolveOptions & per_solve_options, double * x)`, trả về `LinearSolver::Summary`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CgnrSolver`
- Vị trí: `internal/ceres/cgnr_solver.cc`, dòng 145–206

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
145 | LinearSolver::Summary CgnrSolver::SolveImpl(
146 |     BlockSparseMatrix* A,
147 |     const double* b,
148 |     const LinearSolver::PerSolveOptions& per_solve_options,
149 |     double* x) {
150 |   EventLogger event_logger("CgnrSolver::Solve");
151 |   if (!preconditioner_) {
152 |     Preconditioner::Options preconditioner_options;
153 |     preconditioner_options.type = options_.preconditioner_type;
154 |     preconditioner_options.subset_preconditioner_start_row_block =
155 |         options_.subset_preconditioner_start_row_block;
156 |     preconditioner_options.sparse_linear_algebra_library_type =
157 |         options_.sparse_linear_algebra_library_type;
158 |     preconditioner_options.ordering_type = options_.ordering_type;
159 |     preconditioner_options.num_threads = options_.num_threads;
160 |     preconditioner_options.context = options_.context;
161 | 
162 |     if (options_.preconditioner_type == JACOBI) {
163 |       preconditioner_ = std::make_unique<BlockSparseJacobiPreconditioner>(
164 |           preconditioner_options, *A);
165 |     } else if (options_.preconditioner_type == SUBSET) {
166 |       preconditioner_ =
167 |           std::make_unique<SubsetPreconditioner>(preconditioner_options, *A);
168 |     } else {
169 |       preconditioner_ = std::make_unique<IdentityPreconditioner>(A->num_cols());
170 |     }
171 |   }
172 |   preconditioner_->Update(*A, per_solve_options.D);
173 | 
174 |   ConjugateGradientsSolverOptions cg_options;
175 |   cg_options.min_num_iterations = options_.min_num_iterations;
176 |   cg_options.max_num_iterations = options_.max_num_iterations;
177 |   cg_options.residual_reset_period = options_.residual_reset_period;
178 |   cg_options.q_tolerance = per_solve_options.q_tolerance;
179 |   cg_options.r_tolerance = per_solve_options.r_tolerance;
180 |   cg_options.context = options_.context;
181 |   cg_options.num_threads = options_.num_threads;
182 | 
183 |   // lhs = AtA + DtD
184 |   CgnrLinearOperator lhs(
185 |       *A, per_solve_options.D, options_.context, options_.num_threads);
186 |   // rhs = Atb.
187 |   Vector rhs(A->num_cols());
188 |   rhs.setZero();
189 |   A->LeftMultiplyAndAccumulate(
190 |       b, rhs.data(), options_.context, options_.num_threads);
191 | 
192 |   cg_solution_ = Vector::Zero(A->num_cols());
193 |   for (int i = 0; i < 4; ++i) {
194 |     if (scratch_[i] == nullptr) {
195 |       scratch_[i] = new Vector(A->num_cols());
196 |     }
197 |   }
198 |   event_logger.AddEvent("Setup");
199 | 
200 |   LinearOperatorAdapter preconditioner(*preconditioner_);
201 |   auto summary = ConjugateGradientsSolver(
202 |       cg_options, lhs, rhs, preconditioner, scratch_, cg_solution_);
203 |   VectorRef(x, A->num_cols()) = cg_solution_;
204 |   event_logger.AddEvent("Solve");
205 |   return summary;
206 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5

START → 1
1   "CgnrSolver::Solve"                                            → 2
2   if (!preconditioner_)                                          đúng → 3   sai → 6
3   preconditioner_options.type = options_.preconditioner_type
    preconditioner_options.subset_preconditioner_start_row_block = options_.subset_preconditioner_start_row_block
    preconditioner_options.sparse_linear_algebra_library_type = options_.sparse_linear_algebra_library_type
    preconditioner_options.ordering_type = options_.ordering_type
    preconditioner_options.num_threads = options_.num_threads
    preconditioner_options.context = options_.context              → 4
4   if (options_.preconditioner_type == JACOBI)                    đúng → 5   sai → 12
5   preconditioner_ = std::make_unique<BlockSparseJacobiPreconditioner>(preconditioner_options, *A)   → 6
6   preconditioner_->Update(*A, per_solve_options.D)
    cg_options.min_num_iterations = options_.min_num_iterations
    cg_options.max_num_iterations = options_.max_num_iterations
    cg_options.residual_reset_period = options_.residual_reset_period
    cg_options.q_tolerance = per_solve_options.q_tolerance
    cg_options.r_tolerance = per_solve_options.r_tolerance
    cg_options.context = options_.context
    cg_options.num_threads = options_.num_threads
    *A, per_solve_options.D, options_.context, options_.num_threads
    rhs.setZero()
    A->LeftMultiplyAndAccumulate(b, rhs.data(), options_.context, options_.num_threads)
    cg_solution_ = Vector::Zero(A->num_cols())
    int i = 0                                                      → 7
7   vòng for, điều kiện: i < 4                                     đúng → 8   sai → 11
8   if (scratch_[i] == nullptr)                                    đúng → 9   sai → 10
9   CFGNewAllocator(Vector *)
    scratch_[i] = new Vector(A->num_cols())                        → 10
10  ++i                                                            → 7
11  event_logger.AddEvent("Setup")
    operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    * preconditioner_
    VectorRef(x, A->num_cols()) = cg_solution_
    event_logger.AddEvent("Solve")                                 → END
12  if (options_.preconditioner_type == SUBSET)                    đúng → 13   sai → 14
13  preconditioner_ = std::make_unique<SubsetPreconditioner>(preconditioner_options, *A)   → 6
14  preconditioner_ = std::make_unique<IdentityPreconditioner>(A->num_cols())   → 6
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
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/cgnr_solver.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/subset_preconditioner.h"
#include "ceres/wall_time.h"
```

- Đây là method của class `ceres::internal::CgnrSolver`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `CgnrSolver`:
Các constructor:
```cpp
  CgnrSolver(LinearSolver::Options options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1441_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
