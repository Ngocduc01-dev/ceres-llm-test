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

- Hàm: `EvaluateRiddersJacobianColumn(const CostFunctor * functor, int parameter_index, double delta, const NumericDiffOptions & options, int num_residuals, int parameter_block_size, const double * x_ptr, const double * residuals_at_eval_point, double ** parameters, double * x_plus_delta_ptr, double * temp_residuals_ptr, double * residuals_ptr)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::NumericDiff` (class template)
- Vị trí: `include/ceres/internal/numeric_diff.h`, dòng 245–383

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
245 |   static bool EvaluateRiddersJacobianColumn(
246 |       const CostFunctor* functor,
247 |       int parameter_index,
248 |       double delta,
249 |       const NumericDiffOptions& options,
250 |       int num_residuals,
251 |       int parameter_block_size,
252 |       const double* x_ptr,
253 |       const double* residuals_at_eval_point,
254 |       double** parameters,
255 |       double* x_plus_delta_ptr,
256 |       double* temp_residuals_ptr,
257 |       double* residuals_ptr) {
258 |     using Eigen::aligned_allocator;
259 |     using Eigen::Map;
260 |     using Eigen::Matrix;
261 | 
262 |     using ResidualVector = Matrix<double, kNumResiduals, 1>;
263 |     using ResidualCandidateMatrix =
264 |         Matrix<double, kNumResiduals, Eigen::Dynamic>;
265 |     using ParameterVector = Matrix<double, kParameterBlockSize, 1>;
266 | 
267 |     Map<const ParameterVector> x(x_ptr, parameter_block_size);
268 |     Map<ParameterVector> x_plus_delta(x_plus_delta_ptr, parameter_block_size);
269 | 
270 |     Map<ResidualVector> residuals(residuals_ptr, num_residuals);
271 |     Map<ResidualVector> temp_residuals(temp_residuals_ptr, num_residuals);
272 | 
273 |     // In order for the algorithm to converge, the step size should be
274 |     // initialized to a value that is large enough to produce a significant
275 |     // change in the function.
276 |     // As the derivative is estimated, the step size decreases.
277 |     // By default, the step sizes are chosen so that the middle column
278 |     // of the Romberg tableau uses the input delta.
279 |     double current_step_size =
280 |         delta * pow(options.ridders_step_shrink_factor,
281 |                     options.max_num_ridders_extrapolations / 2);
282 | 
283 |     // Double-buffering temporary differential candidate vectors
284 |     // from previous step size.
285 |     ResidualCandidateMatrix stepsize_candidates_a(
286 |         num_residuals, options.max_num_ridders_extrapolations);
287 |     ResidualCandidateMatrix stepsize_candidates_b(
288 |         num_residuals, options.max_num_ridders_extrapolations);
289 |     ResidualCandidateMatrix* current_candidates = &stepsize_candidates_a;
290 |     ResidualCandidateMatrix* previous_candidates = &stepsize_candidates_b;
291 | 
292 |     // Represents the computational error of the derivative. This variable is
293 |     // initially set to a large value, and is set to the difference between
294 |     // current and previous finite difference extrapolations.
295 |     // norm_error is supposed to decrease as the finite difference tableau
296 |     // generation progresses, serving both as an estimate for differentiation
297 |     // error and as a measure of differentiation numerical stability.
298 |     double norm_error = (std::numeric_limits<double>::max)();
299 | 
300 |     // Loop over decreasing step sizes until:
301 |     //  1. Error is smaller than a given value (ridders_epsilon),
302 |     //  2. Maximal order of extrapolation reached, or
303 |     //  3. Extrapolation becomes numerically unstable.
304 |     for (int i = 0; i < options.max_num_ridders_extrapolations; ++i) {
305 |       // Compute the numerical derivative at this step size.
306 |       if (!EvaluateJacobianColumn(functor,
307 |                                   parameter_index,
308 |                                   current_step_size,
309 |                                   num_residuals,
310 |                                   parameter_block_size,
311 |                                   x.data(),
312 |                                   residuals_at_eval_point,
313 |                                   parameters,
314 |                                   x_plus_delta.data(),
315 |                                   temp_residuals.data(),
316 |                                   current_candidates->col(0).data())) {
317 |         // Something went wrong; bail.
318 |         return false;
319 |       }
320 | 
321 |       // Store initial results.
322 |       if (i == 0) {
323 |         residuals = current_candidates->col(0);
324 |       }
325 | 
326 |       // Shrink differentiation step size.
327 |       current_step_size /= options.ridders_step_shrink_factor;
328 | 
329 |       // Extrapolation factor for Richardson acceleration method (see below).
330 |       double richardson_factor = options.ridders_step_shrink_factor *
331 |                                  options.ridders_step_shrink_factor;
332 |       for (int k = 1; k <= i; ++k) {
333 |         // Extrapolate the various orders of finite differences using
334 |         // the Richardson acceleration method.
335 |         current_candidates->col(k) =
336 |             (richardson_factor * current_candidates->col(k - 1) -
337 |              previous_candidates->col(k - 1)) /
338 |             (richardson_factor - 1.0);
339 | 
340 |         richardson_factor *= options.ridders_step_shrink_factor *
341 |                              options.ridders_step_shrink_factor;
342 | 
343 |         // Compute the difference between the previous value and the current.
344 |         double candidate_error = (std::max)(
345 |             (current_candidates->col(k) - current_candidates->col(k - 1))
346 |                 .norm(),
347 |             (current_candidates->col(k) - previous_candidates->col(k - 1))
348 |                 .norm());
349 | 
350 |         // If the error has decreased, update results.
351 |         if (candidate_error <= norm_error) {
352 |           norm_error = candidate_error;
353 |           residuals = current_candidates->col(k);
354 | 
355 |           // If the error is small enough, stop.
356 |           if (norm_error < options.ridders_epsilon) {
357 |             break;
358 |           }
359 |         }
360 |       }
361 | 
362 |       // After breaking out of the inner loop, declare convergence.
363 |       if (norm_error < options.ridders_epsilon) {
364 |         break;
365 |       }
366 | 
367 |       // Check to see if the current gradient estimate is numerically unstable.
368 |       // If so, bail out and return the last stable result.
369 |       if (i > 0) {
370 |         double tableau_error =
371 |             (current_candidates->col(i) - previous_candidates->col(i - 1))
372 |                 .norm();
373 | 
374 |         // Compare current error to the chosen candidate's error.
375 |         if (tableau_error >= 2 * norm_error) {
376 |           break;
377 |         }
378 |       }
379 | 
380 |       std::swap(current_candidates, previous_candidates);
381 |     }
382 |     return true;
383 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp NumericDiff<PlusFunctor, RIDDERS, -1, ParameterDims<true>, -1, -1> (lấy từ một chỗ Ceres dùng thật).

Số điểm rẽ nhánh: 9

START → 1
1   x_ptr, parameter_block_size
    x_plus_delta_ptr, parameter_block_size
    temp_residuals_ptr, num_residuals
    double current_step_size = delta * pow(options.ridders_step_shrink_factor, options.max_num_ridders_extrapolations / 2)
    num_residuals, options.max_num_ridders_extrapolations
    num_residuals, options.max_num_ridders_extrapolations
    ResidualCandidateMatrix *current_candidates = &stepsize_candidates_a
    ResidualCandidateMatrix *previous_candidates = &stepsize_candidates_b
    double norm_error = (std::numeric_limits<double>::max)()
    int i = 0                                                      → 2
2   vòng for, điều kiện: i < options.max_num_ridders_extrapolations   đúng → 3   sai → 16
3   if (!EvaluateJacobianColumn(functor, parameter_index, current_step_size, num_residuals, parameter_block_size, x.data(), residuals_at_eval_point, parameters, x_plus_delta.data(), temp_residuals.data(), current_candidates->col(0).data()))   đúng → 4   sai → 5
4   return false                                                   → END
5   if (i == 0)                                                    đúng → 6   sai → 7
6   residuals = current_candidates->col(0)                         → 7
7   current_step_size /= options.ridders_step_shrink_factor
    double richardson_factor = options.ridders_step_shrink_factor * options.ridders_step_shrink_factor
    int k = 1                                                      → 8
8   vòng for, điều kiện: k <= i                                    đúng → 9   sai → 14
9   current_candidates->col(k) = (richardson_factor * current_candidates->col(k - 1) - previous_candidates->col(k - 1)) / (richardson_factor - 1.)
    richardson_factor *= options.ridders_step_shrink_factor * options.ridders_step_shrink_factor
    double candidate_error = (std::max)((current_candidates->col(k) - current_candidates->col(k - 1)).norm(), (current_candidates->col(k) - previous_candidates->col(k - 1)).norm())   → 10
10  if (candidate_error <= norm_error)                             đúng → 11   sai → 23
11  norm_error = candidate_error
    residuals = current_candidates->col(k)                         → 12
12  if (norm_error < options.ridders_epsilon)                      đúng → 13   sai → 23
13  break                                                          → 14
14  if (norm_error < options.ridders_epsilon)                      đúng → 15   sai → 17
15  break                                                          → 16
16  return true                                                    → END
17  if (i > 0)                                                     đúng → 18   sai → 21
18  double tableau_error = (current_candidates->col(i) - previous_candidates->col(i - 1)).norm()   → 19
19  if (tableau_error >= 2 * norm_error)                           đúng → 20   sai → 21
20  break                                                          → 16
21  std::swap(current_candidates, previous_candidates)             → 22
22  ++i                                                            → 2
23  ++k                                                            → 8
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
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"
```

- Đây là method của class `ceres::internal::NumericDiff`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp (xem ví dụ chỗ dùng trong Ceres ở ghi chú của CFG, nếu có).

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1127_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
