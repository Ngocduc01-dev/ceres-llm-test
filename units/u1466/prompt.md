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

- Hàm: `DoInnerIterationsIfNeeded()`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::TrustRegionMinimizer`
- Vị trí: `internal/ceres/trust_region_minimizer.cc`, dòng 506–578

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
506 | void TrustRegionMinimizer::DoInnerIterationsIfNeeded() {
507 |   inner_iterations_were_useful_ = false;
508 |   if (!inner_iterations_are_enabled_ ||
509 |       candidate_cost_ >= std::numeric_limits<double>::max()) {
510 |     return;
511 |   }
512 | 
513 |   double inner_iteration_start_time = WallTimeInSeconds();
514 |   ++solver_summary_->num_inner_iteration_steps;
515 |   inner_iteration_x_ = candidate_x_;
516 |   Solver::Summary inner_iteration_summary;
517 |   options_.inner_iteration_minimizer->Minimize(
518 |       options_, inner_iteration_x_.data(), &inner_iteration_summary);
519 |   double inner_iteration_cost;
520 |   if (!evaluator_->Evaluate(inner_iteration_x_.data(),
521 |                             &inner_iteration_cost,
522 |                             nullptr,
523 |                             nullptr,
524 |                             nullptr)) {
525 |     if (is_not_silent_) {
526 |       VLOG(2) << "Inner iteration failed.";
527 |     }
528 |     return;
529 |   }
530 | 
531 |   if (is_not_silent_) {
532 |     VLOG(2) << "Inner iteration succeeded; Current cost: " << x_cost_
533 |             << " Trust region step cost: " << candidate_cost_
534 |             << " Inner iteration cost: " << inner_iteration_cost;
535 |   }
536 |   candidate_x_ = inner_iteration_x_;
537 | 
538 |   // Normally, the quality of a trust region step is measured by
539 |   // the ratio
540 |   //
541 |   //              cost_change
542 |   //    r =    -----------------
543 |   //           model_cost_change
544 |   //
545 |   // All the change in the nonlinear objective is due to the trust
546 |   // region step so this ratio is a good measure of the quality of
547 |   // the trust region radius. However, when inner iterations are
548 |   // being used, cost_change includes the contribution of the
549 |   // inner iterations and its not fair to credit it all to the
550 |   // trust region algorithm. So we change the ratio to be
551 |   //
552 |   //                              cost_change
553 |   //    r =    ------------------------------------------------
554 |   //           (model_cost_change + inner_iteration_cost_change)
555 |   //
556 |   // Practically we do this by increasing model_cost_change by
557 |   // inner_iteration_cost_change.
558 | 
559 |   const double inner_iteration_cost_change =
560 |       candidate_cost_ - inner_iteration_cost;
561 |   model_cost_change_ += inner_iteration_cost_change;
562 |   inner_iterations_were_useful_ = inner_iteration_cost < x_cost_;
563 |   const double inner_iteration_relative_progress =
564 |       1.0 - inner_iteration_cost / candidate_cost_;
565 | 
566 |   // Disable inner iterations once the relative improvement
567 |   // drops below tolerance.
568 |   inner_iterations_are_enabled_ =
569 |       (inner_iteration_relative_progress > options_.inner_iteration_tolerance);
570 |   if (is_not_silent_ && !inner_iterations_are_enabled_) {
571 |     VLOG(2) << "Disabling inner iterations. Progress : "
572 |             << inner_iteration_relative_progress;
573 |   }
574 |   candidate_cost_ = inner_iteration_cost;
575 | 
576 |   solver_summary_->inner_iteration_time_in_seconds +=
577 |       WallTimeInSeconds() - inner_iteration_start_time;
578 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5

START → 1
1   inner_iterations_were_useful_ = false                          → 2
2   if (!inner_iterations_are_enabled_ || candidate_cost_ >= std::numeric_limits<double>::max())   đúng → 3   sai → 4
3   return                                                         → END
4   double inner_iteration_start_time = WallTimeInSeconds()
    ++solver_summary_->num_inner_iteration_steps
    inner_iteration_x_ = candidate_x_
    options_.inner_iteration_minimizer->Minimize(options_, inner_iteration_x_.data(), &inner_iteration_summary)
    double inner_iteration_cost                                    → 5
5   if (!evaluator_->Evaluate(inner_iteration_x_.data(), &inner_iteration_cost, nullptr, nullptr, nullptr))   đúng → 6   sai → 8
6   if (is_not_silent_)                                            đúng → 7   sai → 7
7   return                                                         → END
8   if (is_not_silent_)                                            đúng → 9   sai → 9
9   candidate_x_ = inner_iteration_x_
    const double inner_iteration_cost_change = candidate_cost_ - inner_iteration_cost
    model_cost_change_ += inner_iteration_cost_change
    inner_iterations_were_useful_ = inner_iteration_cost < x_cost_
    const double inner_iteration_relative_progress = 1. - inner_iteration_cost / candidate_cost_
    inner_iterations_are_enabled_ = (inner_iteration_relative_progress > options_.inner_iteration_tolerance)   → 10
10  if (is_not_silent_ && !inner_iterations_are_enabled_)          đúng → 11   sai → 11
11  candidate_cost_ = inner_iteration_cost
    solver_summary_->inner_iteration_time_in_seconds += WallTimeInSeconds() - inner_iteration_start_time   → END
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
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/trust_region_minimizer.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1466_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
