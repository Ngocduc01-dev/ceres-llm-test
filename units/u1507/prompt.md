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

- Hàm: `DoSearch(const double step_size_estimate, const double initial_cost, const double initial_gradient, Summary * summary) const`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::ArmijoLineSearch`
- Vị trí: `internal/ceres/line_search.cc`, dòng 280–365

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
280 | void ArmijoLineSearch::DoSearch(const double step_size_estimate,
281 |                                 const double initial_cost,
282 |                                 const double initial_gradient,
283 |                                 Summary* summary) const {
284 |   CHECK_GE(step_size_estimate, 0.0);
285 |   CHECK_GT(options().sufficient_decrease, 0.0);
286 |   CHECK_LT(options().sufficient_decrease, 1.0);
287 |   CHECK_GT(options().max_num_iterations, 0);
288 |   LineSearchFunction* function = options().function;
289 | 
290 |   // Note initial_cost & initial_gradient are evaluated at step_size = 0,
291 |   // not step_size_estimate, which is our starting guess.
292 |   FunctionSample initial_position(0.0, initial_cost, initial_gradient);
293 |   initial_position.vector_x = function->position();
294 |   initial_position.vector_x_is_valid = true;
295 | 
296 |   const double descent_direction_max_norm = function->DirectionInfinityNorm();
297 |   FunctionSample previous;
298 |   FunctionSample current;
299 | 
300 |   // As the Armijo line search algorithm always uses the initial point, for
301 |   // which both the function value and derivative are known, when fitting a
302 |   // minimizing polynomial, we can fit up to a quadratic without requiring the
303 |   // gradient at the current query point.
304 |   const bool kEvaluateGradient = options().interpolation_type == CUBIC;
305 | 
306 |   ++summary->num_function_evaluations;
307 |   if (kEvaluateGradient) {
308 |     ++summary->num_gradient_evaluations;
309 |   }
310 | 
311 |   function->Evaluate(step_size_estimate, kEvaluateGradient, &current);
312 |   while (!current.value_is_valid ||
313 |          current.value > (initial_cost + options().sufficient_decrease *
314 |                                              initial_gradient * current.x)) {
315 |     // If current.value_is_valid is false, we treat it as if the cost at that
316 |     // point is not large enough to satisfy the sufficient decrease condition.
317 |     ++summary->num_iterations;
318 |     if (summary->num_iterations >= options().max_num_iterations) {
319 |       summary->error = StringPrintf(
320 |           "Line search failed: Armijo failed to find a point "
321 |           "satisfying the sufficient decrease condition within "
322 |           "specified max_num_iterations: %d.",
323 |           options().max_num_iterations);
324 |       if (!options().is_silent) {
325 |         LOG(WARNING) << summary->error;
326 |       }
327 |       return;
328 |     }
329 | 
330 |     const double polynomial_minimization_start_time = WallTimeInSeconds();
331 |     const double step_size = this->InterpolatingPolynomialMinimizingStepSize(
332 |         options().interpolation_type,
333 |         initial_position,
334 |         previous,
335 |         current,
336 |         (options().max_step_contraction * current.x),
337 |         (options().min_step_contraction * current.x));
338 |     summary->polynomial_minimization_time_in_seconds +=
339 |         (WallTimeInSeconds() - polynomial_minimization_start_time);
340 | 
341 |     if (step_size * descent_direction_max_norm < options().min_step_size) {
342 |       summary->error = StringPrintf(
343 |           "Line search failed: step_size too small: %.5e "
344 |           "with descent_direction_max_norm: %.5e.",
345 |           step_size,
346 |           descent_direction_max_norm);
347 |       if (!options().is_silent) {
348 |         LOG(WARNING) << summary->error;
349 |       }
350 |       return;
351 |     }
352 | 
353 |     previous = current;
354 | 
355 |     ++summary->num_function_evaluations;
356 |     if (kEvaluateGradient) {
357 |       ++summary->num_gradient_evaluations;
358 |     }
359 | 
360 |     function->Evaluate(step_size, kEvaluateGradient, &current);
361 |   }
362 | 
363 |   summary->optimal_point = current;
364 |   summary->success = true;
365 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 7 (và 4 lệnh CHECK)

START → 1
1   CHECK_GE(step_size_estimate, 0.0)                              đúng → 2   sai → DỪNG
2   CHECK_GT(options().sufficient_decrease, 0.0)                   đúng → 3   sai → DỪNG
3   CHECK_LT(options().sufficient_decrease, 1.0)                   đúng → 4   sai → DỪNG
4   CHECK_GT(options().max_num_iterations, 0)                      đúng → 5   sai → DỪNG
5   LineSearchFunction *function = options().function
    0., initial_cost, initial_gradient
    initial_position.vector_x = function->position()
    initial_position.vector_x_is_valid = true
    const double descent_direction_max_norm = function->DirectionInfinityNorm()
    const bool kEvaluateGradient = options().interpolation_type == CUBIC
    ++summary->num_function_evaluations                            → 6
6   if (kEvaluateGradient)                                         đúng → 7   sai → 8
7   ++summary->num_gradient_evaluations                            → 8
8   function->Evaluate(step_size_estimate, kEvaluateGradient, &current)   → 9
9   while (!current.value_is_valid || current.value > (initial_cost + options().sufficient_decrease * initial_gradient * current.x))   đúng → 10   sai → 24
10  ++summary->num_iterations                                      → 11
11  if (summary->num_iterations >= options().max_num_iterations)   đúng → 12   sai → 15
12  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: Armijo failed to find a point satisfying the sufficient decrease condition within specified max_num_iterations: %d.", options().max_num_iterations)   → 13
13  if (!options().is_silent)                                      đúng → 14   sai → 14
14  return                                                         → END
15  const double polynomial_minimization_start_time = WallTimeInSeconds()
    const double step_size = InterpolatingPolynomialMinimizingStepSize(options().interpolation_type, initial_position, previous, current, (options().max_step_contraction * current.x), (options().min_step_contraction * current.x))
    summary->polynomial_minimization_time_in_seconds += (WallTimeInSeconds() - polynomial_minimization_start_time)   → 16
16  if (step_size * descent_direction_max_norm < options().min_step_size)   đúng → 17   sai → 20
17  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: step_size too small: %.5e with descent_direction_max_norm: %.5e.", step_size, descent_direction_max_norm)   → 18
18  if (!options().is_silent)                                      đúng → 19   sai → 19
19  return                                                         → END
20  previous = current
    ++summary->num_function_evaluations                            → 21
21  if (kEvaluateGradient)                                         đúng → 22   sai → 23
22  ++summary->num_gradient_evaluations                            → 23
23  function->Evaluate(step_size, kEvaluateGradient, &current)     → 9
24  summary->optimal_point = current
    summary->success = true                                        → END
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
- Đây là method của class `ceres::internal::ArmijoLineSearch`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `ArmijoLineSearch`:
Các constructor:
```cpp
  ArmijoLineSearch(const LineSearch::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1507_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
