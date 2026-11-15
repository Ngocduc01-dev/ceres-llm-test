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

- Hàm: `ComputeSubspaceDoglegStep(double * dogleg)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::DoglegStrategy`
- Vị trí: `internal/ceres/dogleg_strategy.cc`, dòng 265–365

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
265 | void DoglegStrategy::ComputeSubspaceDoglegStep(double* dogleg) {
266 |   VectorRef dogleg_step(dogleg, gradient_.rows());
267 | 
268 |   // The Gauss-Newton point is inside the trust region if |GN| <= radius_.
269 |   // This test is valid even though radius_ is a length in the two-dimensional
270 |   // subspace while gauss_newton_step_ is expressed in the (scaled)
271 |   // higher dimensional original space. This is because
272 |   //
273 |   //   1. gauss_newton_step_ by definition lies in the subspace, and
274 |   //   2. the subspace basis is orthonormal.
275 |   //
276 |   // As a consequence, the norm of the gauss_newton_step_ in the subspace is
277 |   // the same as its norm in the original space.
278 |   const double gauss_newton_norm = gauss_newton_step_.norm();
279 |   if (gauss_newton_norm <= radius_) {
280 |     dogleg_step = gauss_newton_step_;
281 |     dogleg_step_norm_ = gauss_newton_norm;
282 |     dogleg_step.array() /= diagonal_.array();
283 |     VLOG(3) << "GaussNewton step size: " << dogleg_step_norm_
284 |             << " radius: " << radius_;
285 |     return;
286 |   }
287 | 
288 |   // The optimum lies on the boundary of the trust region. The above problem
289 |   // therefore becomes
290 |   //
291 |   //   min. 1/2 x^T B^T H B x + g^T B x
292 |   //   s.t. || B x ||^2 = r^2
293 |   //
294 |   // Notice the equality in the constraint.
295 |   //
296 |   // This can be solved by forming the Lagrangian, solving for x(y), where
297 |   // y is the Lagrange multiplier, using the gradient of the objective, and
298 |   // putting x(y) back into the constraint. This results in a fourth order
299 |   // polynomial in y, which can be solved using e.g. the companion matrix.
300 |   // See the description of MakePolynomialForBoundaryConstrainedProblem for
301 |   // details. The result is up to four real roots y*, not all of which
302 |   // correspond to feasible points. The feasible points x(y*) have to be
303 |   // tested for optimality.
304 | 
305 |   if (subspace_is_one_dimensional_) {
306 |     // The subspace is one-dimensional, so both the gradient and
307 |     // the Gauss-Newton step point towards the same direction.
308 |     // In this case, we move along the gradient until we reach the trust
309 |     // region boundary.
310 |     dogleg_step = -(radius_ / gradient_.norm()) * gradient_;
311 |     dogleg_step_norm_ = radius_;
312 |     dogleg_step.array() /= diagonal_.array();
313 |     VLOG(3) << "Dogleg subspace step size (1D): " << dogleg_step_norm_
314 |             << " radius: " << radius_;
315 |     return;
316 |   }
317 | 
318 |   Vector2d minimum(0.0, 0.0);
319 |   if (!FindMinimumOnTrustRegionBoundary(&minimum)) {
320 |     // For the positive semi-definite case, a traditional dogleg step
321 |     // is taken in this case.
322 |     LOG(WARNING) << "Failed to compute polynomial roots. "
323 |                  << "Taking traditional dogleg step instead.";
324 |     ComputeTraditionalDoglegStep(dogleg);
325 |     return;
326 |   }
327 | 
328 |   // Test first order optimality at the minimum.
329 |   // The first order KKT conditions state that the minimum x*
330 |   // has to satisfy either || x* ||^2 < r^2 (i.e. has to lie within
331 |   // the trust region), or
332 |   //
333 |   //   (B x* + g) + y x* = 0
334 |   //
335 |   // for some positive scalar y.
336 |   // Here, as it is already known that the minimum lies on the boundary, the
337 |   // latter condition is tested. To allow for small imprecisions, we test if
338 |   // the angle between (B x* + g) and -x* is smaller than acos(0.99).
339 |   // The exact value of the cosine is arbitrary but should be close to 1.
340 |   //
341 |   // This condition should not be violated. If it is, the minimum was not
342 |   // correctly determined.
343 |   const double kCosineThreshold = 0.99;
344 |   const Vector2d grad_minimum = subspace_B_ * minimum + subspace_g_;
345 |   const double cosine_angle =
346 |       -minimum.dot(grad_minimum) / (minimum.norm() * grad_minimum.norm());
347 |   if (cosine_angle < kCosineThreshold) {
348 |     LOG(WARNING) << "First order optimality seems to be violated "
349 |                  << "in the subspace method!\n"
350 |                  << "Cosine of angle between x and B x + g is " << cosine_angle
351 |                  << ".\n"
352 |                  << "Taking a regular dogleg step instead.\n"
353 |                  << "Please consider filing a bug report if this "
354 |                  << "happens frequently or consistently.\n";
355 |     ComputeTraditionalDoglegStep(dogleg);
356 |     return;
357 |   }
358 | 
359 |   // Create the full step from the optimal 2d solution.
360 |   dogleg_step = subspace_basis_ * minimum;
361 |   dogleg_step_norm_ = radius_;
362 |   dogleg_step.array() /= diagonal_.array();
363 |   VLOG(3) << "Dogleg subspace step size: " << dogleg_step_norm_
364 |           << " radius: " << radius_;
365 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4

START → 1
1   dogleg, gradient_.rows()
    const double gauss_newton_norm = gauss_newton_step_.norm()     → 2
2   if (gauss_newton_norm <= radius_)                              đúng → 3   sai → 4
3   dogleg_step = gauss_newton_step_
    dogleg_step_norm_ = gauss_newton_norm
    dogleg_step.array() /= diagonal_.array()                       → END
4   if (subspace_is_one_dimensional_)                              đúng → 5   sai → 6
5   dogleg_step = -(radius_ / gradient_.norm()) * gradient_
    dogleg_step_norm_ = radius_
    dogleg_step.array() /= diagonal_.array()                       → END
6   0., 0.                                                         → 7
7   if (!FindMinimumOnTrustRegionBoundary(&minimum))               đúng → END   sai → 8
8   const double kCosineThreshold = 0.98999999999999999
    subspace_B_ * minimum + subspace_g_
    const double cosine_angle = -minimum.dot(grad_minimum) / (minimum.norm() * grad_minimum.norm())   → 9
9   if (cosine_angle < kCosineThreshold)                           đúng → END   sai → 10
10  dogleg_step = subspace_basis_ * minimum
    dogleg_step_norm_ = radius_
    dogleg_step.array() /= diagonal_.array()                       → END
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
#include "ceres/dogleg_strategy.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::DoglegStrategy`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `DoglegStrategy`:
Các constructor:
```cpp
  DoglegStrategy(const TrustRegionStrategy::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1395_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
