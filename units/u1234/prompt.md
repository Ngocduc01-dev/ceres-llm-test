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

- Hàm: `EvaluateGradientAndJacobian(bool new_evaluation_point)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::TrustRegionMinimizer`
- Vị trí: `internal/ceres/trust_region_minimizer.cc`, dòng 244–302

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
244 | bool TrustRegionMinimizer::EvaluateGradientAndJacobian(
245 |     bool new_evaluation_point) {
246 |   Evaluator::EvaluateOptions evaluate_options;
247 |   evaluate_options.new_evaluation_point = new_evaluation_point;
248 |   if (!evaluator_->Evaluate(evaluate_options,
249 |                             x_.data(),
250 |                             &x_cost_,
251 |                             residuals_.data(),
252 |                             gradient_.data(),
253 |                             jacobian_)) {
254 |     solver_summary_->message = "Residual and Jacobian evaluation failed.";
255 |     solver_summary_->termination_type = FAILURE;
256 |     return false;
257 |   }
258 | 
259 |   iteration_summary_.cost = x_cost_ + solver_summary_->fixed_cost;
260 | 
261 |   if (options_.jacobi_scaling) {
262 |     if (iteration_summary_.iteration == 0) {
263 |       // Compute a scaling vector that is used to improve the
264 |       // conditioning of the Jacobian.
265 |       //
266 |       // jacobian_scaling_ = diag(J'J)^{-1}
267 |       jacobian_->SquaredColumnNorm(jacobian_scaling_.data());
268 |       for (int i = 0; i < jacobian_->num_cols(); ++i) {
269 |         // Add one to the denominator to prevent division by zero.
270 |         jacobian_scaling_[i] = 1.0 / (1.0 + sqrt(jacobian_scaling_[i]));
271 |       }
272 |     }
273 | 
274 |     // jacobian = jacobian * diag(J'J) ^{-1}
275 |     jacobian_->ScaleColumns(
276 |         jacobian_scaling_.data(), options_.context, options_.num_threads);
277 |   }
278 | 
279 |   // The gradient exists in the local tangent space. To account for
280 |   // the bounds constraints correctly, instead of just computing the
281 |   // norm of the gradient vector, we compute
282 |   //
283 |   // |Plus(x, -gradient) - x|
284 |   //
285 |   // Where the Plus operator lifts the negative gradient to the
286 |   // ambient space, adds it to x and projects it on the hypercube
287 |   // defined by the bounds.
288 |   negative_gradient_ = -gradient_;
289 |   if (!evaluator_->Plus(x_.data(),
290 |                         negative_gradient_.data(),
291 |                         projected_gradient_step_.data())) {
292 |     solver_summary_->message =
293 |         "projected_gradient_step = Plus(x, -gradient) failed.";
294 |     solver_summary_->termination_type = FAILURE;
295 |     return false;
296 |   }
297 | 
298 |   iteration_summary_.gradient_max_norm =
299 |       (x_ - projected_gradient_step_).lpNorm<Eigen::Infinity>();
300 |   iteration_summary_.gradient_norm = (x_ - projected_gradient_step_).norm();
301 |   return true;
302 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5

START → 1
1   evaluate_options.new_evaluation_point = new_evaluation_point   → 2
2   if (!evaluator_->Evaluate(evaluate_options, x_.data(), &x_cost_, residuals_.data(), gradient_.data(), jacobian_))   đúng → 3   sai → 4
3   solver_summary_->message = "Residual and Jacobian evaluation failed."
    solver_summary_->termination_type = FAILURE
    return false                                                   → END
4   iteration_summary_.cost = x_cost_ + solver_summary_->fixed_cost   → 5
5   if (options_.jacobi_scaling)                                   đúng → 6   sai → 12
6   if (iteration_summary_.iteration == 0)                         đúng → 7   sai → 11
7   jacobian_->SquaredColumnNorm(jacobian_scaling_.data())
    int i = 0                                                      → 8
8   vòng for, điều kiện: i < jacobian_->num_cols()                 đúng → 9   sai → 11
9   jacobian_scaling_[i] = 1. / (1. + sqrt(jacobian_scaling_[i]))   → 10
10  ++i                                                            → 8
11  jacobian_->ScaleColumns(jacobian_scaling_.data(), options_.context, options_.num_threads)   → 12
12  negative_gradient_ = - gradient_                               → 13
13  if (!evaluator_->Plus(x_.data(), negative_gradient_.data(), projected_gradient_step_.data()))   đúng → 14   sai → 15
14  solver_summary_->message = "projected_gradient_step = Plus(x, -gradient) failed."
    solver_summary_->termination_type = FAILURE
    return false                                                   → END
15  iteration_summary_.gradient_max_norm = (x_ - projected_gradient_step_).lpNorm<Eigen::Infinity>()
    iteration_summary_.gradient_norm = (x_ - projected_gradient_step_).norm()
    return true                                                    → END
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
#include "ceres/evaluator.h"
#include "ceres/sparse_matrix.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1234_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
