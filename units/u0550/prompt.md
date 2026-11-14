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

- Hàm: `RightMultiplyAndAccumulate(const double * x_ptr, double * y_ptr) const`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::LowRankInverseHessian`
- Vị trí: `internal/ceres/low_rank_inverse_hessian.cc`, dòng 117–177

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
117 | void LowRankInverseHessian::RightMultiplyAndAccumulate(const double* x_ptr,
118 |                                                        double* y_ptr) const {
119 |   ConstVectorRef gradient(x_ptr, num_parameters_);
120 |   VectorRef search_direction(y_ptr, num_parameters_);
121 | 
122 |   search_direction = gradient;
123 | 
124 |   const int num_corrections = indices_.size();
125 |   Vector alpha(num_corrections);
126 | 
127 |   for (auto it = indices_.rbegin(); it != indices_.rend(); ++it) {
128 |     const double alpha_i = delta_x_history_.col(*it).dot(search_direction) /
129 |                            delta_x_dot_delta_gradient_(*it);
130 |     search_direction -= alpha_i * delta_gradient_history_.col(*it);
131 |     alpha(*it) = alpha_i;
132 |   }
133 | 
134 |   if (use_approximate_eigenvalue_scaling_) {
135 |     // Rescale the initial inverse Hessian approximation (H_0) to be iteratively
136 |     // updated so that it is of similar 'size' to the true inverse Hessian along
137 |     // the most recent search direction.  As shown in [1]:
138 |     //
139 |     //   \gamma_k = (delta_gradient_{k-1}' * delta_x_{k-1}) /
140 |     //              (delta_gradient_{k-1}' * delta_gradient_{k-1})
141 |     //
142 |     // Satisfies:
143 |     //
144 |     //   (1 / \lambda_m) <= \gamma_k <= (1 / \lambda_1)
145 |     //
146 |     // Where \lambda_1 & \lambda_m are the smallest and largest eigenvalues of
147 |     // the true Hessian (not the inverse) along the most recent search direction
148 |     // respectively.  Thus \gamma is an approximate eigenvalue of the true
149 |     // inverse Hessian, and choosing: H_0 = I * \gamma will yield a starting
150 |     // point that has a similar scale to the true inverse Hessian.  This
151 |     // technique is widely reported to often improve convergence, however this
152 |     // is not universally true, particularly if there are errors in the initial
153 |     // jacobians, or if there are significant differences in the sensitivity
154 |     // of the problem to the parameters (i.e. the range of the magnitudes of
155 |     // the components of the gradient is large).
156 |     //
157 |     // The original origin of this rescaling trick is somewhat unclear, the
158 |     // earliest reference appears to be Oren [1], however it is widely discussed
159 |     // without specific attribution in various texts including [2] (p143/178).
160 |     //
161 |     // [1] Oren S.S., Self-scaling variable metric (SSVM) algorithms Part II:
162 |     //     Implementation and experiments, Management Science,
163 |     //     20(5), 863-874, 1974.
164 |     // [2] Nocedal J., Wright S., Numerical Optimization, Springer, 1999.
165 |     search_direction *= approximate_eigenvalue_scale_;
166 | 
167 |     VLOG(4) << "Applying approximate_eigenvalue_scale: "
168 |             << approximate_eigenvalue_scale_ << " to initial inverse Hessian "
169 |             << "approximation.";
170 |   }
171 | 
172 |   for (const int i : indices_) {
173 |     const double beta = delta_gradient_history_.col(i).dot(search_direction) /
174 |                         delta_x_dot_delta_gradient_(i);
175 |     search_direction += delta_x_history_.col(i) * (alpha(i) - beta);
176 |   }
177 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3

START → 1
1   x_ptr, num_parameters_
    y_ptr, num_parameters_
    search_direction = gradient
    const int num_corrections = indices_.size()
    indices_.rbegin()                                              → 2
2   vòng for, điều kiện: it != indices_.rend()                     đúng → 3   sai → 5
3   const double alpha_i = delta_x_history_.col(* it).dot(search_direction) / delta_x_dot_delta_gradient_(* it)
    search_direction -= alpha_i * delta_gradient_history_.col(* it)
    alpha(* it) = alpha_i                                          → 4
4   ++ it                                                          → 2
5   if (use_approximate_eigenvalue_scaling_)                       đúng → 6   sai → 7
6   search_direction *= approximate_eigenvalue_scale_              → 7
7   for (const int i : indices_)                                   đúng → 8   sai → END
8   const int i
    const double beta = delta_gradient_history_.col(i).dot(search_direction) / delta_x_dot_delta_gradient_(i)
    search_direction += delta_x_history_.col(i) * (alpha(i) - beta)   → 9
9   ++ (bước tiếp của vòng for)                                    → 7
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
#include "ceres/low_rank_inverse_hessian.h"
```

- Đây là method của class `ceres::internal::LowRankInverseHessian`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0550_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
