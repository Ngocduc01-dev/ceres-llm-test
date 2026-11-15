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

- Hàm: `DoSearch(const double step_size_estimate, const double initial_cost, const double initial_gradient, Summary * summary) const`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::WolfeLineSearch`
- Vị trí: `internal/ceres/line_search.cc`, dòng 370–481

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
370 | void WolfeLineSearch::DoSearch(const double step_size_estimate,
371 |                                const double initial_cost,
372 |                                const double initial_gradient,
373 |                                Summary* summary) const {
374 |   // All parameters should have been validated by the Solver, but as
375 |   // invalid values would produce crazy nonsense, hard check them here.
376 |   CHECK_GE(step_size_estimate, 0.0);
377 |   CHECK_GT(options().sufficient_decrease, 0.0);
378 |   CHECK_GT(options().sufficient_curvature_decrease,
379 |            options().sufficient_decrease);
380 |   CHECK_LT(options().sufficient_curvature_decrease, 1.0);
381 |   CHECK_GT(options().max_step_expansion, 1.0);
382 | 
383 |   // Note initial_cost & initial_gradient are evaluated at step_size = 0,
384 |   // not step_size_estimate, which is our starting guess.
385 |   FunctionSample initial_position(0.0, initial_cost, initial_gradient);
386 |   initial_position.vector_x = options().function->position();
387 |   initial_position.vector_x_is_valid = true;
388 |   bool do_zoom_search = false;
389 |   // Important: The high/low in bracket_high & bracket_low refer to their
390 |   // _function_ values, not their step sizes i.e. it is _not_ required that
391 |   // bracket_low.x < bracket_high.x.
392 |   FunctionSample solution, bracket_low, bracket_high;
393 | 
394 |   // Wolfe bracketing phase: Increases step_size until either it finds a point
395 |   // that satisfies the (strong) Wolfe conditions, or an interval that brackets
396 |   // step sizes which satisfy the conditions.  From Nocedal & Wright [1] p61 the
397 |   // interval: (step_size_{k-1}, step_size_{k}) contains step lengths satisfying
398 |   // the strong Wolfe conditions if one of the following conditions are met:
399 |   //
400 |   //   1. step_size_{k} violates the sufficient decrease (Armijo) condition.
401 |   //   2. f(step_size_{k}) >= f(step_size_{k-1}).
402 |   //   3. f'(step_size_{k}) >= 0.
403 |   //
404 |   // Caveat: If f(step_size_{k}) is invalid, then step_size is reduced, ignoring
405 |   // this special case, step_size monotonically increases during bracketing.
406 |   if (!this->BracketingPhase(initial_position,
407 |                              step_size_estimate,
408 |                              &bracket_low,
409 |                              &bracket_high,
410 |                              &do_zoom_search,
411 |                              summary)) {
412 |     // Failed to find either a valid point, a valid bracket satisfying the Wolfe
413 |     // conditions, or even a step size > minimum tolerance satisfying the Armijo
414 |     // condition.
415 |     return;
416 |   }
417 | 
418 |   if (!do_zoom_search) {
419 |     // Either: Bracketing phase already found a point satisfying the strong
420 |     // Wolfe conditions, thus no Zoom required.
421 |     //
422 |     // Or: Bracketing failed to find a valid bracket or a point satisfying the
423 |     // strong Wolfe conditions within max_num_iterations, or whilst searching
424 |     // shrank the bracket width until it was below our minimum tolerance.
425 |     // As these are 'artificial' constraints, and we would otherwise fail to
426 |     // produce a valid point when ArmijoLineSearch would succeed, we return the
427 |     // point with the lowest cost found thus far which satisfies the Armijo
428 |     // condition (but not the Wolfe conditions).
429 |     summary->optimal_point = bracket_low;
430 |     summary->success = true;
431 |     return;
432 |   }
433 | 
434 |   VLOG(3) << std::scientific << std::setprecision(kErrorMessageNumericPrecision)
435 |           << "Starting line search zoom phase with bracket_low: " << bracket_low
436 |           << ", bracket_high: " << bracket_high
437 |           << ", bracket width: " << fabs(bracket_low.x - bracket_high.x)
438 |           << ", bracket abs delta cost: "
439 |           << fabs(bracket_low.value - bracket_high.value);
440 | 
441 |   // Wolfe Zoom phase: Called when the Bracketing phase finds an interval of
442 |   // non-zero, finite width that should bracket step sizes which satisfy the
443 |   // (strong) Wolfe conditions (before finding a step size that satisfies the
444 |   // conditions).  Zoom successively decreases the size of the interval until a
445 |   // step size which satisfies the Wolfe conditions is found.  The interval is
446 |   // defined by bracket_low & bracket_high, which satisfy:
447 |   //
448 |   //   1. The interval bounded by step sizes: bracket_low.x & bracket_high.x
449 |   //      contains step sizes that satisfy the strong Wolfe conditions.
450 |   //   2. bracket_low.x is of all the step sizes evaluated *which satisfied the
451 |   //      Armijo sufficient decrease condition*, the one which generated the
452 |   //      smallest function value, i.e. bracket_low.value <
453 |   //      f(all other steps satisfying Armijo).
454 |   //        - Note that this does _not_ (necessarily) mean that initially
455 |   //          bracket_low.value < bracket_high.value (although this is typical)
456 |   //          e.g. when bracket_low = initial_position, and bracket_high is the
457 |   //          first sample, and which does not satisfy the Armijo condition,
458 |   //          but still has bracket_high.value < initial_position.value.
459 |   //   3. bracket_high is chosen after bracket_low, s.t.
460 |   //      bracket_low.gradient * (bracket_high.x - bracket_low.x) < 0.
461 |   if (!this->ZoomPhase(
462 |           initial_position, bracket_low, bracket_high, &solution, summary) &&
463 |       !solution.value_is_valid) {
464 |     // Failed to find a valid point (given the specified decrease parameters)
465 |     // within the specified bracket.
466 |     return;
467 |   }
468 |   // Ensure that if we ran out of iterations whilst zooming the bracket, or
469 |   // shrank the bracket width to < tolerance and failed to find a point which
470 |   // satisfies the strong Wolfe curvature condition, that we return the point
471 |   // amongst those found thus far, which minimizes f() and satisfies the Armijo
472 |   // condition.
473 | 
474 |   if (!solution.value_is_valid || solution.value > bracket_low.value) {
475 |     summary->optimal_point = bracket_low;
476 |   } else {
477 |     summary->optimal_point = solution;
478 |   }
479 | 
480 |   summary->success = true;
481 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4 (và 5 lệnh CHECK)

START → 1
1   CHECK_GE(step_size_estimate, 0.0)                              đúng → 2   sai → DỪNG
2   CHECK_GT(options().sufficient_decrease, 0.0)                   đúng → 3   sai → DỪNG
3   options().sufficient_decrease)                                 đúng → 4   sai → DỪNG
4   CHECK_LT(options().sufficient_curvature_decrease, 1.0)         đúng → 5   sai → DỪNG
5   CHECK_GT(options().max_step_expansion, 1.0)                    đúng → 6   sai → DỪNG
6   0., initial_cost, initial_gradient
    initial_position.vector_x = options().function->position()
    initial_position.vector_x_is_valid = true
    bool do_zoom_search = false                                    → 7
7   if (!BracketingPhase(initial_position, step_size_estimate, &bracket_low, &bracket_high, &do_zoom_search, summary))   đúng → 8   sai → 9
8   return                                                         → END
9   if (!do_zoom_search)                                           đúng → 10   sai → 11
10  summary->optimal_point = bracket_low
    summary->success = true
    return                                                         → END
11  if (!ZoomPhase(initial_position, bracket_low, bracket_high, &solution, summary) && !solution.value_is_valid)   đúng → 12   sai → 13
12  return                                                         → END
13  if (!solution.value_is_valid || solution.value > bracket_low.value)   đúng → 14   sai → 16
14  summary->optimal_point = bracket_low                           → 15
15  summary->success = true                                        → END
16  summary->optimal_point = solution                              → 15
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
#include "ceres/function_sample.h"
#include "ceres/line_search.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::WolfeLineSearch`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `WolfeLineSearch`:
Các constructor:
```cpp
  WolfeLineSearch(const LineSearch::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1522_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
