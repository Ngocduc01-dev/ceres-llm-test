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

- Hàm: `ComputeTraditionalDoglegStep(double * dogleg)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::DoglegStrategy`
- Vị trí: `internal/ceres/dogleg_strategy.cc`, dòng 200–254

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
200 | void DoglegStrategy::ComputeTraditionalDoglegStep(double* dogleg) {
201 |   VectorRef dogleg_step(dogleg, gradient_.rows());
202 | 
203 |   // Case 1. The Gauss-Newton step lies inside the trust region, and
204 |   // is therefore the optimal solution to the trust-region problem.
205 |   const double gradient_norm = gradient_.norm();
206 |   const double gauss_newton_norm = gauss_newton_step_.norm();
207 |   if (gauss_newton_norm <= radius_) {
208 |     dogleg_step = gauss_newton_step_;
209 |     dogleg_step_norm_ = gauss_newton_norm;
210 |     dogleg_step.array() /= diagonal_.array();
211 |     VLOG(3) << "GaussNewton step size: " << dogleg_step_norm_
212 |             << " radius: " << radius_;
213 |     return;
214 |   }
215 | 
216 |   // Case 2. The Cauchy point and the Gauss-Newton steps lie outside
217 |   // the trust region. Rescale the Cauchy point to the trust region
218 |   // and return.
219 |   if (gradient_norm * alpha_ >= radius_) {
220 |     dogleg_step = -(radius_ / gradient_norm) * gradient_;
221 |     dogleg_step_norm_ = radius_;
222 |     dogleg_step.array() /= diagonal_.array();
223 |     VLOG(3) << "Cauchy step size: " << dogleg_step_norm_
224 |             << " radius: " << radius_;
225 |     return;
226 |   }
227 | 
228 |   // Case 3. The Cauchy point is inside the trust region and the
229 |   // Gauss-Newton step is outside. Compute the line joining the two
230 |   // points and the point on it which intersects the trust region
231 |   // boundary.
232 | 
233 |   // a = alpha * -gradient
234 |   // b = gauss_newton_step
235 |   const double b_dot_a = -alpha_ * gradient_.dot(gauss_newton_step_);
236 |   const double a_squared_norm = pow(alpha_ * gradient_norm, 2.0);
237 |   const double b_minus_a_squared_norm =
238 |       a_squared_norm - 2 * b_dot_a + pow(gauss_newton_norm, 2);
239 | 
240 |   // c = a' (b - a)
241 |   //   = alpha * -gradient' gauss_newton_step - alpha^2 |gradient|^2
242 |   const double c = b_dot_a - a_squared_norm;
243 |   const double d = sqrt(c * c + b_minus_a_squared_norm *
244 |                                     (pow(radius_, 2.0) - a_squared_norm));
245 | 
246 |   double beta = (c <= 0) ? (d - c) / b_minus_a_squared_norm
247 |                          : (radius_ * radius_ - a_squared_norm) / (d + c);
248 |   dogleg_step =
249 |       (-alpha_ * (1.0 - beta)) * gradient_ + beta * gauss_newton_step_;
250 |   dogleg_step_norm_ = dogleg_step.norm();
251 |   dogleg_step.array() /= diagonal_.array();
252 |   VLOG(3) << "Dogleg step size: " << dogleg_step_norm_
253 |           << " radius: " << radius_;
254 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3

START → 1
1   dogleg, gradient_.rows()
    const double gradient_norm = gradient_.norm()
    const double gauss_newton_norm = gauss_newton_step_.norm()     → 2
2   if (gauss_newton_norm <= radius_)                              đúng → 3   sai → 4
3   dogleg_step = gauss_newton_step_
    dogleg_step_norm_ = gauss_newton_norm
    dogleg_step.array() /= diagonal_.array()                       → END
4   if (gradient_norm * alpha_ >= radius_)                         đúng → 5   sai → 6
5   dogleg_step = -(radius_ / gradient_norm) * gradient_
    dogleg_step_norm_ = radius_
    dogleg_step.array() /= diagonal_.array()                       → END
6   const double b_dot_a = -alpha_ * gradient_.dot(gauss_newton_step_)
    const double a_squared_norm = pow(alpha_ * gradient_norm, 2.)
    const double b_minus_a_squared_norm = a_squared_norm - 2 * b_dot_a + pow(gauss_newton_norm, 2)
    const double c = b_dot_a - a_squared_norm
    const double d = sqrt(c * c + b_minus_a_squared_norm * (pow(radius_, 2.) - a_squared_norm))   → 7
7   (c <= 0) ? ... : ...                                           đúng → 8   sai → 8
8   double beta = (c <= 0) ? (d - c) / b_minus_a_squared_norm : (radius_ * radius_ - a_squared_norm) / (d + c)
    dogleg_step = (-alpha_ * (1. - beta)) * gradient_ + beta * gauss_newton_step_
    dogleg_step_norm_ = dogleg_step.norm()
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0612_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
