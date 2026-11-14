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

- Hàm: `NextDirection(const LineSearchMinimizer::State & previous, const LineSearchMinimizer::State & current, Vector * search_direction)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::BFGS`
- Vị trí: `internal/ceres/line_search_direction.cc`, dòng 164–329

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
164 |   bool NextDirection(const LineSearchMinimizer::State& previous,
165 |                      const LineSearchMinimizer::State& current,
166 |                      Vector* search_direction) override {
167 |     CHECK(is_positive_definite_)
168 |         << "Ceres bug: NextDirection() called on BFGS after inverse Hessian "
169 |         << "approximation has become indefinite, please contact the "
170 |         << "developers!";
171 | 
172 |     const Vector delta_x = previous.search_direction * previous.step_size;
173 |     const Vector delta_gradient = current.gradient - previous.gradient;
174 |     const double delta_x_dot_delta_gradient = delta_x.dot(delta_gradient);
175 | 
176 |     // The (L)BFGS algorithm explicitly requires that the secant equation:
177 |     //
178 |     //   B_{k+1} * s_k = y_k
179 |     //
180 |     // Is satisfied at each iteration, where B_{k+1} is the approximated
181 |     // Hessian at the k+1-th iteration, s_k = (x_{k+1} - x_{k}) and
182 |     // y_k = (grad_{k+1} - grad_{k}). As the approximated Hessian must be
183 |     // positive definite, this is equivalent to the condition:
184 |     //
185 |     //   s_k^T * y_k > 0     [s_k^T * B_{k+1} * s_k = s_k^T * y_k > 0]
186 |     //
187 |     // This condition would always be satisfied if the function was strictly
188 |     // convex, alternatively, it is always satisfied provided that a Wolfe line
189 |     // search is used (even if the function is not strictly convex).  See [1]
190 |     // (p138) for a proof.
191 |     //
192 |     // Although Ceres will always use a Wolfe line search when using (L)BFGS,
193 |     // practical implementation considerations mean that the line search
194 |     // may return a point that satisfies only the Armijo condition, and thus
195 |     // could violate the Secant equation.  As such, we will only use a step
196 |     // to update the Hessian approximation if:
197 |     //
198 |     //   s_k^T * y_k > tolerance
199 |     //
200 |     // It is important that tolerance is very small (and >=0), as otherwise we
201 |     // might skip the update too often and fail to capture important curvature
202 |     // information in the Hessian.  For example going from 1e-10 -> 1e-14
203 |     // improves the NIST benchmark score from 43/54 to 53/54.
204 |     //
205 |     // [1] Nocedal J, Wright S, Numerical Optimization, 2nd Ed. Springer, 1999.
206 |     //
207 |     // TODO(alexs.mac): Consider using Damped BFGS update instead of
208 |     // skipping update.
209 |     const double kBFGSSecantConditionHessianUpdateTolerance = 1e-14;
210 |     if (delta_x_dot_delta_gradient <=
211 |         kBFGSSecantConditionHessianUpdateTolerance) {
212 |       VLOG(2) << "Skipping BFGS Update, delta_x_dot_delta_gradient too "
213 |               << "small: " << delta_x_dot_delta_gradient
214 |               << ", tolerance: " << kBFGSSecantConditionHessianUpdateTolerance
215 |               << " (Secant condition).";
216 |     } else {
217 |       // Update dense inverse Hessian approximation.
218 | 
219 |       if (!initialized_ && use_approximate_eigenvalue_scaling_) {
220 |         // Rescale the initial inverse Hessian approximation (H_0) to be
221 |         // iteratively updated so that it is of similar 'size' to the true
222 |         // inverse Hessian at the start point.  As shown in [1]:
223 |         //
224 |         //   \gamma = (delta_gradient_{0}' * delta_x_{0}) /
225 |         //            (delta_gradient_{0}' * delta_gradient_{0})
226 |         //
227 |         // Satisfies:
228 |         //
229 |         //   (1 / \lambda_m) <= \gamma <= (1 / \lambda_1)
230 |         //
231 |         // Where \lambda_1 & \lambda_m are the smallest and largest eigenvalues
232 |         // of the true initial Hessian (not the inverse) respectively. Thus,
233 |         // \gamma is an approximate eigenvalue of the true inverse Hessian, and
234 |         // choosing: H_0 = I * \gamma will yield a starting point that has a
235 |         // similar scale to the true inverse Hessian.  This technique is widely
236 |         // reported to often improve convergence, however this is not
237 |         // universally true, particularly if there are errors in the initial
238 |         // gradients, or if there are significant differences in the sensitivity
239 |         // of the problem to the parameters (i.e. the range of the magnitudes of
240 |         // the components of the gradient is large).
241 |         //
242 |         // The original origin of this rescaling trick is somewhat unclear, the
243 |         // earliest reference appears to be Oren [1], however it is widely
244 |         // discussed without specific attribution in various texts including
245 |         // [2] (p143).
246 |         //
247 |         // [1] Oren S.S., Self-scaling variable metric (SSVM) algorithms
248 |         //     Part II: Implementation and experiments, Management Science,
249 |         //     20(5), 863-874, 1974.
250 |         // [2] Nocedal J., Wright S., Numerical Optimization, Springer, 1999.
251 |         const double approximate_eigenvalue_scale =
252 |             delta_x_dot_delta_gradient / delta_gradient.dot(delta_gradient);
253 |         inverse_hessian_ *= approximate_eigenvalue_scale;
254 | 
255 |         VLOG(4) << "Applying approximate_eigenvalue_scale: "
256 |                 << approximate_eigenvalue_scale << " to initial inverse "
257 |                 << "Hessian approximation.";
258 |       }
259 |       initialized_ = true;
260 | 
261 |       // Efficient O(num_parameters^2) BFGS update [2].
262 |       //
263 |       // Starting from dense BFGS update detailed in Nocedal [2] p140/177 and
264 |       // using: y_k = delta_gradient, s_k = delta_x:
265 |       //
266 |       //   \rho_k = 1.0 / (s_k' * y_k)
267 |       //   V_k = I - \rho_k * y_k * s_k'
268 |       //   H_k = (V_k' * H_{k-1} * V_k) + (\rho_k * s_k * s_k')
269 |       //
270 |       // This update involves matrix, matrix products which naively O(N^3),
271 |       // however we can exploit our knowledge that H_k is positive definite
272 |       // and thus by defn. symmetric to reduce the cost of the update:
273 |       //
274 |       // Expanding the update above yields:
275 |       //
276 |       //   H_k = H_{k-1} +
277 |       //         \rho_k * ( (1.0 + \rho_k * y_k' * H_k * y_k) * s_k * s_k' -
278 |       //                    (s_k * y_k' * H_k + H_k * y_k * s_k') )
279 |       //
280 |       // Using: A = (s_k * y_k' * H_k), and the knowledge that H_k = H_k', the
281 |       // last term simplifies to (A + A'). Note that although A is not symmetric
282 |       // (A + A') is symmetric. For ease of construction we also define
283 |       // B = (1 + \rho_k * y_k' * H_k * y_k) * s_k * s_k', which is by defn
284 |       // symmetric due to construction from: s_k * s_k'.
285 |       //
286 |       // Now we can write the BFGS update as:
287 |       //
288 |       //   H_k = H_{k-1} + \rho_k * (B - (A + A'))
289 | 
290 |       // For efficiency, as H_k is by defn. symmetric, we will only maintain the
291 |       // *lower* triangle of H_k (and all intermediary terms).
292 | 
293 |       const double rho_k = 1.0 / delta_x_dot_delta_gradient;
294 | 
295 |       // Calculate: A = s_k * y_k' * H_k
296 |       Matrix A = delta_x * (delta_gradient.transpose() *
297 |                             inverse_hessian_.selfadjointView<Eigen::Lower>());
298 | 
299 |       // Calculate scalar: (1 + \rho_k * y_k' * H_k * y_k)
300 |       const double delta_x_times_delta_x_transpose_scale_factor =
301 |           (1.0 +
302 |            (rho_k * delta_gradient.transpose() *
303 |             inverse_hessian_.selfadjointView<Eigen::Lower>() * delta_gradient));
304 |       // Calculate: B = (1 + \rho_k * y_k' * H_k * y_k) * s_k * s_k'
305 |       Matrix B = Matrix::Zero(num_parameters_, num_parameters_);
306 |       B.selfadjointView<Eigen::Lower>().rankUpdate(
307 |           delta_x, delta_x_times_delta_x_transpose_scale_factor);
308 | 
309 |       // Finally, update inverse Hessian approximation according to:
310 |       // H_k = H_{k-1} + \rho_k * (B - (A + A')).  Note that (A + A') is
311 |       // symmetric, even though A is not.
312 |       inverse_hessian_.triangularView<Eigen::Lower>() +=
313 |           rho_k * (B - A - A.transpose());
314 |     }
315 | 
316 |     *search_direction = inverse_hessian_.selfadjointView<Eigen::Lower>() *
317 |                         (-1.0 * current.gradient);
318 | 
319 |     if (search_direction->dot(current.gradient) >= 0.0) {
320 |       LOG(WARNING) << "Numerical failure in BFGS update: inverse Hessian "
321 |                    << "approximation is not positive definite, and thus "
322 |                    << "initial gradient for search direction is positive: "
323 |                    << search_direction->dot(current.gradient);
324 |       is_positive_definite_ = false;
325 |       return false;
326 |     }
327 | 
328 |     return true;
329 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3 (và 1 lệnh CHECK)

START → 1
1   CHECK(is_positive_definite_)                                   đúng → 2   sai → DỪNG
2   previous.search_direction * previous.step_size
    current.gradient - previous.gradient
    const double delta_x_dot_delta_gradient = delta_x.dot(delta_gradient)
    const double kBFGSSecantConditionHessianUpdateTolerance = 9.9999999999999999E-15   → 3
3   if (delta_x_dot_delta_gradient <= kBFGSSecantConditionHessianUpdateTolerance)   đúng → 4   sai → 7
4   *search_direction = inverse_hessian_.selfadjointView<Eigen::Lower>() * (-1. * current.gradient)   → 5
5   if (search_direction->dot(current.gradient) >= 0.)             đúng → END   sai → 6
6   return true                                                    → END
7   if (!initialized_ && use_approximate_eigenvalue_scaling_)      đúng → 8   sai → 9
8   const double approximate_eigenvalue_scale = delta_x_dot_delta_gradient / delta_gradient.dot(delta_gradient)
    inverse_hessian_ *= approximate_eigenvalue_scale               → 9
9   initialized_ = true
    const double rho_k = 1. / delta_x_dot_delta_gradient
    delta_x * (delta_gradient.transpose() * inverse_hessian_.selfadjointView<Eigen::Lower>())
    const double delta_x_times_delta_x_transpose_scale_factor = (1. + (rho_k * delta_gradient.transpose() * inverse_hessian_.selfadjointView<Eigen::Lower>() * delta_gradient))
    Matrix::Zero(num_parameters_, num_parameters_)
    B.selfadjointView<Eigen::Lower>().rankUpdate(delta_x, delta_x_times_delta_x_transpose_scale_factor)
    inverse_hessian_.triangularView<Eigen::Lower>() += rho_k * (B - A - A.transpose())   → 4
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
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"
```

- Đây là method của class `ceres::internal::BFGS`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0779_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
