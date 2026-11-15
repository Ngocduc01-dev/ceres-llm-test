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

- Hàm: `ComputeTrustRegionStep()`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::TrustRegionMinimizer`
- Vị trí: `internal/ceres/trust_region_minimizer.cc`, dòng 378–459

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
378 | bool TrustRegionMinimizer::ComputeTrustRegionStep() {
379 |   const double strategy_start_time = WallTimeInSeconds();
380 |   iteration_summary_.step_is_valid = false;
381 |   TrustRegionStrategy::PerSolveOptions per_solve_options;
382 |   per_solve_options.eta = options_.eta;
383 |   if (find(options_.trust_region_minimizer_iterations_to_dump.begin(),
384 |            options_.trust_region_minimizer_iterations_to_dump.end(),
385 |            iteration_summary_.iteration) !=
386 |       options_.trust_region_minimizer_iterations_to_dump.end()) {
387 |     per_solve_options.dump_format_type =
388 |         options_.trust_region_problem_dump_format_type;
389 |     per_solve_options.dump_filename_base =
390 |         JoinPath(options_.trust_region_problem_dump_directory,
391 |                  StringPrintf("ceres_solver_iteration_%03d",
392 |                               iteration_summary_.iteration));
393 |   }
394 | 
395 |   TrustRegionStrategy::Summary strategy_summary =
396 |       strategy_->ComputeStep(per_solve_options,
397 |                              jacobian_,
398 |                              residuals_.data(),
399 |                              trust_region_step_.data());
400 | 
401 |   if (strategy_summary.termination_type ==
402 |       LinearSolverTerminationType::FATAL_ERROR) {
403 |     solver_summary_->message =
404 |         "Linear solver failed due to unrecoverable "
405 |         "non-numeric causes. Please see the error log for clues. ";
406 |     solver_summary_->termination_type = FAILURE;
407 |     return false;
408 |   }
409 | 
410 |   iteration_summary_.step_solver_time_in_seconds =
411 |       WallTimeInSeconds() - strategy_start_time;
412 |   iteration_summary_.linear_solver_iterations = strategy_summary.num_iterations;
413 | 
414 |   if (strategy_summary.termination_type ==
415 |       LinearSolverTerminationType::FAILURE) {
416 |     return true;
417 |   }
418 | 
419 |   // new_model_cost
420 |   //  = 1/2 [f + J * step]^2
421 |   //  = 1/2 [ f'f + 2f'J * step + step' * J' * J * step ]
422 |   // model_cost_change
423 |   //  = cost - new_model_cost
424 |   //  = f'f/2  - 1/2 [ f'f + 2f'J * step + step' * J' * J * step]
425 |   //  = -f'J * step - step' * J' * J * step / 2
426 |   //  = -(J * step)'(f + J * step / 2)
427 |   ParallelSetZero(options_.context, options_.num_threads, model_residuals_);
428 |   jacobian_->RightMultiplyAndAccumulate(trust_region_step_.data(),
429 |                                         model_residuals_.data(),
430 |                                         options_.context,
431 |                                         options_.num_threads);
432 |   model_cost_change_ = -Dot(model_residuals_,
433 |                             residuals_ + model_residuals_ / 2.0,
434 |                             options_.context,
435 |                             options_.num_threads);
436 | 
437 |   // TODO(sameeragarwal)
438 |   //
439 |   //  1. What happens if model_cost_change_ = 0
440 |   //  2. What happens if -epsilon <= model_cost_change_ < 0 for some
441 |   //     small epsilon due to round off error.
442 |   iteration_summary_.step_is_valid = (model_cost_change_ > 0.0);
443 |   if (iteration_summary_.step_is_valid) {
444 |     // Undo the Jacobian column scaling.
445 |     ParallelAssign(options_.context,
446 |                    options_.num_threads,
447 |                    delta_,
448 |                    (trust_region_step_.array() * jacobian_scaling_.array()));
449 |     num_consecutive_invalid_steps_ = 0;
450 |   }
451 | 
452 |   if (is_not_silent_ && !iteration_summary_.step_is_valid) {
453 |     VLOG(1) << "Invalid step: current_cost: " << x_cost_
454 |             << " absolute model cost change: " << model_cost_change_
455 |             << " relative model cost change: "
456 |             << (model_cost_change_ / x_cost_);
457 |   }
458 |   return true;
459 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5

START → 1
1   const double strategy_start_time = WallTimeInSeconds()
    iteration_summary_.step_is_valid = false
    per_solve_options.eta = options_.eta                           → 2
2   if (find(options_.trust_region_minimizer_iterations_to_dump.begin(), options_.trust_region_minimizer_iterations_to_dump.end(), iteration_summary_.iteration) != options_.trust_region_minimizer_iterations_to_dump.end())   đúng → 3   sai → 4
3   per_solve_options.dump_format_type = options_.trust_region_problem_dump_format_type
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    per_solve_options.dump_filename_base = JoinPath(options_.trust_region_problem_dump_directory, StringPrintf("ceres_solver_iteration_%03d", iteration_summary_.iteration))   → 4
4   strategy_->ComputeStep(per_solve_options, jacobian_, residuals_.data(), trust_region_step_.data())   → 5
5   if (strategy_summary.termination_type == LinearSolverTerminationType::FATAL_ERROR)   đúng → 6   sai → 7
6   solver_summary_->message = "Linear solver failed due to unrecoverable non-numeric causes. Please see the error log for clues. "
    solver_summary_->termination_type = FAILURE
    return false                                                   → END
7   iteration_summary_.step_solver_time_in_seconds = WallTimeInSeconds() - strategy_start_time
    iteration_summary_.linear_solver_iterations = strategy_summary.num_iterations   → 8
8   if (strategy_summary.termination_type == LinearSolverTerminationType::FAILURE)   đúng → 9   sai → 10
9   return true                                                    → END
10  ParallelSetZero(options_.context, options_.num_threads, model_residuals_)
    jacobian_->RightMultiplyAndAccumulate(trust_region_step_.data(), model_residuals_.data(), options_.context, options_.num_threads)
    model_cost_change_ = -Dot(model_residuals_, residuals_ + model_residuals_ / 2., options_.context, options_.num_threads)
    iteration_summary_.step_is_valid = (model_cost_change_ > 0.)   → 11
11  if (iteration_summary_.step_is_valid)                          đúng → 12   sai → 13
12  ParallelAssign(options_.context, options_.num_threads, delta_, (trust_region_step_.array() * jacobian_scaling_.array()))
    num_consecutive_invalid_steps_ = 0                             → 13
13  if (is_not_silent_ && !iteration_summary_.step_is_valid)       đúng → 14   sai → 14
14  return true                                                    → END
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
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::TrustRegionMinimizer`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `TrustRegionMinimizer`:
Các constructor:
```cpp
  TrustRegionMinimizer()
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1377_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
