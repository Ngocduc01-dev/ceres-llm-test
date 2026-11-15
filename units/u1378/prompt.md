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

- Hàm: `SolveReducedLinearSystemUsingConjugateGradients(const LinearSolver::PerSolveOptions & per_solve_options, double * solution)`, trả về `LinearSolver::Summary`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SparseSchurComplementSolver`
- Vị trí: `internal/ceres/schur_complement_solver.cc`, dòng 335–406

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
335 | LinearSolver::Summary
336 | SparseSchurComplementSolver::SolveReducedLinearSystemUsingConjugateGradients(
337 |     const LinearSolver::PerSolveOptions& per_solve_options, double* solution) {
338 |   CHECK(options().use_explicit_schur_complement);
339 |   const int num_rows = lhs()->num_rows();
340 |   // The case where there are no f blocks, and the system is block
341 |   // diagonal.
342 |   if (num_rows == 0) {
343 |     LinearSolver::Summary summary;
344 |     summary.num_iterations = 0;
345 |     summary.termination_type = LinearSolverTerminationType::SUCCESS;
346 |     summary.message = "Success.";
347 |     return summary;
348 |   }
349 | 
350 |   // Only SCHUR_JACOBI is supported over here right now.
351 |   CHECK_EQ(options().preconditioner_type, SCHUR_JACOBI);
352 | 
353 |   if (preconditioner_ == nullptr) {
354 |     preconditioner_ = std::make_unique<BlockRandomAccessDiagonalMatrix>(
355 |         blocks_, options().context, options().num_threads);
356 |   }
357 | 
358 |   auto* sc = down_cast<BlockRandomAccessSparseMatrix*>(mutable_lhs());
359 | 
360 |   // Extract block diagonal from the Schur complement to construct the
361 |   // schur_jacobi preconditioner.
362 |   for (int i = 0; i < blocks_.size(); ++i) {
363 |     const int block_size = blocks_[i].size;
364 | 
365 |     int sc_r, sc_c, sc_row_stride, sc_col_stride;
366 |     CellInfo* sc_cell_info =
367 |         sc->GetCell(i, i, &sc_r, &sc_c, &sc_row_stride, &sc_col_stride);
368 |     CHECK(sc_cell_info != nullptr);
369 |     MatrixRef sc_m(sc_cell_info->values, sc_row_stride, sc_col_stride);
370 | 
371 |     int pre_r, pre_c, pre_row_stride, pre_col_stride;
372 |     CellInfo* pre_cell_info = preconditioner_->GetCell(
373 |         i, i, &pre_r, &pre_c, &pre_row_stride, &pre_col_stride);
374 |     CHECK(pre_cell_info != nullptr);
375 |     MatrixRef pre_m(pre_cell_info->values, pre_row_stride, pre_col_stride);
376 | 
377 |     pre_m.block(pre_r, pre_c, block_size, block_size) =
378 |         sc_m.block(sc_r, sc_c, block_size, block_size);
379 |   }
380 |   preconditioner_->Invert();
381 | 
382 |   VectorRef(solution, num_rows).setZero();
383 | 
384 |   auto lhs = std::make_unique<BlockRandomAccessSparseMatrixAdapter>(*sc);
385 |   auto preconditioner =
386 |       std::make_unique<BlockRandomAccessDiagonalMatrixAdapter>(
387 |           *preconditioner_);
388 | 
389 |   ConjugateGradientsSolverOptions cg_options;
390 |   cg_options.min_num_iterations = options().min_num_iterations;
391 |   cg_options.max_num_iterations = options().max_num_iterations;
392 |   cg_options.residual_reset_period = options().residual_reset_period;
393 |   cg_options.q_tolerance = per_solve_options.q_tolerance;
394 |   cg_options.r_tolerance = per_solve_options.r_tolerance;
395 | 
396 |   cg_solution_ = Vector::Zero(sc->num_rows());
397 |   for (int i = 0; i < 4; ++i) {
398 |     if (scratch_[i] == nullptr) {
399 |       scratch_[i] = new Vector(sc->num_rows());
400 |     }
401 |   }
402 |   auto summary = ConjugateGradientsSolver<Vector>(
403 |       cg_options, *lhs, rhs(), *preconditioner, scratch_, cg_solution_);
404 |   VectorRef(solution, sc->num_rows()) = cg_solution_;
405 |   return summary;
406 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5 (và 4 lệnh CHECK)

START → 1
1   CHECK(options().use_explicit_schur_complement)                 đúng → 2   sai → DỪNG
2   const int num_rows = lhs()->num_rows()                         → 3
3   if (num_rows == 0)                                             đúng → 4   sai → 5
4   summary.num_iterations = 0
    summary.termination_type = LinearSolverTerminationType::SUCCESS
    summary.message = "Success."                                   → END
5   CHECK_EQ(options().preconditioner_type, SCHUR_JACOBI)          đúng → 6   sai → DỪNG
6   if (preconditioner_ == nullptr)                                đúng → 7   sai → 8
7   preconditioner_ = std::make_unique<BlockRandomAccessDiagonalMatrix>(blocks_, options().context, options().num_threads)   → 8
8   auto *sc = down_cast<BlockRandomAccessSparseMatrix *>(mutable_lhs())
    int i = 0                                                      → 9
9   vòng for, điều kiện: i < blocks_.size()                        đúng → 10   sai → 15
10  const int block_size = blocks_[i].size
    int sc_r
    int sc_c
    int sc_row_stride
    int sc_col_stride
    CellInfo *sc_cell_info = sc->GetCell(i, i, &sc_r, &sc_c, &sc_row_stride, &sc_col_stride)   → 11
11  CHECK(sc_cell_info != nullptr)                                 đúng → 12   sai → DỪNG
12  sc_cell_info->values, sc_row_stride, sc_col_stride
    int pre_r
    int pre_c
    int pre_row_stride
    int pre_col_stride
    CellInfo *pre_cell_info = preconditioner_->GetCell(i, i, &pre_r, &pre_c, &pre_row_stride, &pre_col_stride)   → 13
13  CHECK(pre_cell_info != nullptr)                                đúng → 14   sai → DỪNG
14  ++i                                                            → 9
15  preconditioner_->Invert()
    VectorRef(solution, num_rows).setZero()
    operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    cg_options.min_num_iterations = options().min_num_iterations
    cg_options.max_num_iterations = options().max_num_iterations
    cg_options.residual_reset_period = options().residual_reset_period
    cg_options.q_tolerance = per_solve_options.q_tolerance
    cg_options.r_tolerance = per_solve_options.r_tolerance
    cg_solution_ = Vector::Zero(sc->num_rows())
    int i = 0                                                      → 16
16  vòng for, điều kiện: i < 4                                     đúng → 17   sai → 20
17  if (scratch_[i] == nullptr)                                    đúng → 18   sai → 19
18  CFGNewAllocator(Vector *)
    scratch_[i] = new Vector(sc->num_rows())                       → 19
19  ++i                                                            → 16
20  operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    VectorRef(solution, sc->num_rows()) = cg_solution_             → END
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
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::SparseSchurComplementSolver`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `SparseSchurComplementSolver`:
Các constructor:
```cpp
  SparseSchurComplementSolver(const LinearSolver::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1378_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
