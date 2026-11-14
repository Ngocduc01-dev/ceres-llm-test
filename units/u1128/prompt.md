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

- Hàm: `Solve(const Function & function, Parameters * x_and_min)`, trả về `const Summary &`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::TinySolver` (class template)
- Vị trí: `include/ceres/tiny_solver.h`, dòng 220–330

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
220 |   const Summary& Solve(const Function& function, Parameters* x_and_min) {
221 |     Initialize<NUM_RESIDUALS, NUM_PARAMETERS>(function);
222 |     assert(x_and_min);
223 |     Parameters& x = *x_and_min;
224 |     summary = Summary();
225 |     summary.iterations = 0;
226 | 
227 |     // TODO(sameeragarwal): Deal with failure here.
228 |     Update(function, x);
229 |     summary.initial_cost = cost_;
230 |     summary.final_cost = cost_;
231 | 
232 |     if (summary.gradient_max_norm < options.gradient_tolerance) {
233 |       summary.status = GRADIENT_TOO_SMALL;
234 |       return summary;
235 |     }
236 | 
237 |     if (cost_ < options.cost_threshold) {
238 |       summary.status = COST_TOO_SMALL;
239 |       return summary;
240 |     }
241 | 
242 |     Scalar u = 1.0 / options.initial_trust_region_radius;
243 |     Scalar v = 2;
244 | 
245 |     for (summary.iterations = 1;
246 |          summary.iterations < options.max_num_iterations;
247 |          summary.iterations++) {
248 |       jtj_regularized_ = jtj_;
249 |       const Scalar min_diagonal = 1e-6;
250 |       const Scalar max_diagonal = 1e32;
251 |       for (int i = 0; i < dx_.rows(); ++i) {
252 |         jtj_regularized_(i, i) +=
253 |             u * (std::min)((std::max)(jtj_(i, i), min_diagonal), max_diagonal);
254 |       }
255 | 
256 |       // TODO(sameeragarwal): Check for failure and deal with it.
257 |       linear_solver_.compute(jtj_regularized_);
258 |       lm_step_ = linear_solver_.solve(g_);
259 |       dx_ = jacobi_scaling_.asDiagonal() * lm_step_;
260 | 
261 |       // Adding parameter_tolerance to x.norm() ensures that this
262 |       // works if x is near zero.
263 |       const Scalar parameter_tolerance =
264 |           options.parameter_tolerance *
265 |           (x.norm() + options.parameter_tolerance);
266 |       if (dx_.norm() < parameter_tolerance) {
267 |         summary.status = RELATIVE_STEP_SIZE_TOO_SMALL;
268 |         break;
269 |       }
270 |       x_new_ = x + dx_;
271 | 
272 |       // TODO(keir): Add proper handling of errors from user eval of cost
273 |       // functions.
274 |       function(&x_new_[0], &f_x_new_[0], nullptr);
275 | 
276 |       const Scalar cost_change = (2 * cost_ - f_x_new_.squaredNorm());
277 |       // TODO(sameeragarwal): Better more numerically stable evaluation.
278 |       const Scalar model_cost_change = lm_step_.dot(2 * g_ - jtj_ * lm_step_);
279 | 
280 |       // rho is the ratio of the actual reduction in error to the reduction
281 |       // in error that would be obtained if the problem was linear. See [1]
282 |       // for details.
283 |       Scalar rho(cost_change / model_cost_change);
284 |       if (rho > 0) {
285 |         // Accept the Levenberg-Marquardt step because the linear
286 |         // model fits well.
287 |         x = x_new_;
288 | 
289 |         if (std::abs(cost_change) < options.function_tolerance) {
290 |           cost_ = f_x_new_.squaredNorm() / 2;
291 |           summary.status = COST_CHANGE_TOO_SMALL;
292 |           break;
293 |         }
294 | 
295 |         // TODO(sameeragarwal): Deal with failure.
296 |         Update(function, x);
297 |         if (summary.gradient_max_norm < options.gradient_tolerance) {
298 |           summary.status = GRADIENT_TOO_SMALL;
299 |           break;
300 |         }
301 | 
302 |         if (cost_ < options.cost_threshold) {
303 |           summary.status = COST_TOO_SMALL;
304 |           break;
305 |         }
306 | 
307 |         Scalar tmp = Scalar(2 * rho - 1);
308 |         u = u * (std::max)(Scalar(1 / 3.), Scalar(1) - tmp * tmp * tmp);
309 |         v = 2;
310 | 
311 |       } else {
312 |         // Reject the update because either the normal equations failed to solve
313 |         // or the local linear model was not good (rho < 0).
314 | 
315 |         // Additionally if the cost change is too small, then terminate.
316 |         if (std::abs(cost_change) < options.function_tolerance) {
317 |           // Terminate
318 |           summary.status = COST_CHANGE_TOO_SMALL;
319 |           break;
320 |         }
321 | 
322 |         // Reduce the size of the trust region.
323 |         u *= v;
324 |         v *= 2;
325 |       }
326 |     }
327 | 
328 |     summary.final_cost = cost_;
329 |     return summary;
330 |   }
```

## 3.2. CFG của unit

Chưa có CFG dựng sẵn cho unit này. Hãy **tự dựng CFG** từ mã nguồn ở 3.1: đánh số node 1, 2, 3… theo thứ tự chạy, ghi rõ `đúng → / sai →` ở mỗi điểm rẽ nhánh, dùng `START`, `END`.

## 3.3. Cách gọi unit trong file test

Các dòng `#include` được dùng:
```cpp
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"
```

- Đây là method của class `ceres::TinySolver`: tạo một object của class rồi gọi method trên object đó.
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1128_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
