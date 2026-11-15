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

- Hàm: `operator()(JetT const* const* inputs, JetT* output) const`, trả về `bool`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Thuộc class: `ceres::DynamicCostFunctionToFunctor`
- Vị trí: `include/ceres/dynamic_cost_function_to_functor.h`, dòng 117–184

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
117 |   template <typename JetT>
118 |   bool operator()(JetT const* const* inputs, JetT* output) const {
119 |     const std::vector<int32_t>& parameter_block_sizes =
120 |         cost_function_->parameter_block_sizes();
121 |     const int num_parameter_blocks =
122 |         static_cast<int>(parameter_block_sizes.size());
123 |     const int num_residuals = cost_function_->num_residuals();
124 |     const int num_parameters = std::accumulate(
125 |         parameter_block_sizes.begin(), parameter_block_sizes.end(), 0);
126 | 
127 |     internal::FixedArray<double> parameters(num_parameters);
128 |     internal::FixedArray<double*> parameter_blocks(num_parameter_blocks);
129 |     internal::FixedArray<double> jacobians(num_residuals * num_parameters);
130 |     internal::FixedArray<double*> jacobian_blocks(num_parameter_blocks);
131 |     internal::FixedArray<double> residuals(num_residuals);
132 | 
133 |     // Build a set of arrays to get the residuals and jacobians from
134 |     // the CostFunction wrapped by this functor.
135 |     double* parameter_ptr = parameters.data();
136 |     double* jacobian_ptr = jacobians.data();
137 |     for (int i = 0; i < num_parameter_blocks; ++i) {
138 |       parameter_blocks[i] = parameter_ptr;
139 |       jacobian_blocks[i] = jacobian_ptr;
140 |       for (int j = 0; j < parameter_block_sizes[i]; ++j) {
141 |         *parameter_ptr++ = inputs[i][j].a;
142 |       }
143 |       jacobian_ptr += num_residuals * parameter_block_sizes[i];
144 |     }
145 | 
146 |     if (!cost_function_->Evaluate(parameter_blocks.data(),
147 |                                   residuals.data(),
148 |                                   jacobian_blocks.data())) {
149 |       return false;
150 |     }
151 | 
152 |     // Now that we have the incoming Jets, which are carrying the
153 |     // partial derivatives of each of the inputs w.r.t to some other
154 |     // underlying parameters. The derivative of the outputs of the
155 |     // cost function w.r.t to the same underlying parameters can now
156 |     // be computed by applying the chain rule.
157 |     //
158 |     //  d output[i]               d output[i]   d input[j]
159 |     //  --------------  = sum_j   ----------- * ------------
160 |     //  d parameter[k]            d input[j]    d parameter[k]
161 |     //
162 |     // d input[j]
163 |     // --------------  = inputs[j], so
164 |     // d parameter[k]
165 |     //
166 |     //  outputJet[i]  = sum_k jacobian[i][k] * inputJet[k]
167 |     //
168 |     // The following loop, iterates over the residuals, computing one
169 |     // output jet at a time.
170 |     for (int i = 0; i < num_residuals; ++i) {
171 |       output[i].a = residuals[i];
172 |       output[i].v.setZero();
173 | 
174 |       for (int j = 0; j < num_parameter_blocks; ++j) {
175 |         const int32_t block_size = parameter_block_sizes[j];
176 |         for (int k = 0; k < parameter_block_sizes[j]; ++k) {
177 |           output[i].v +=
178 |               jacobian_blocks[j][i * block_size + k] * inputs[j][k].v;
179 |         }
180 |       }
181 |     }
182 | 
183 |     return true;
184 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp operator()<Jet<double, 2>>.

Số điểm rẽ nhánh: 6

START → 1
1   const std::vector<int32_t> &parameter_block_sizes = cost_function_->parameter_block_sizes()
    const int num_parameter_blocks = static_cast<int>(parameter_block_sizes.size())
    const int num_residuals = cost_function_->num_residuals()
    const int num_parameters = std::accumulate(parameter_block_sizes.begin(), parameter_block_sizes.end(), 0)
    num_residuals * num_parameters
    double *parameter_ptr = parameters.data()
    double *jacobian_ptr = jacobians.data()
    int i = 0                                                      → 2
2   vòng for, điều kiện: i < num_parameter_blocks                  đúng → 3   sai → 9
3   parameter_blocks[i] = parameter_ptr
    jacobian_blocks[i] = jacobian_ptr
    int j = 0                                                      → 4
4   vòng for, điều kiện: j < parameter_block_sizes[i]              đúng → 5   sai → 7
5   *parameter_ptr++ = inputs[i][j].a                              → 6
6   ++j                                                            → 4
7   jacobian_ptr += num_residuals * parameter_block_sizes[i]       → 8
8   ++i                                                            → 2
9   if (!cost_function_->Evaluate(parameter_blocks.data(), residuals.data(), jacobian_blocks.data()))   đúng → 10   sai → 11
10  return false                                                   → END
11  int i = 0                                                      → 12
12  vòng for, điều kiện: i < num_residuals                         đúng → 13   sai → 21
13  output[i].a = residuals[i]
    output[i].v.setZero()
    int j = 0                                                      → 14
14  vòng for, điều kiện: j < num_parameter_blocks                  đúng → 15   sai → 20
15  const int32_t block_size = parameter_block_sizes[j]
    int k = 0                                                      → 16
16  vòng for, điều kiện: k < parameter_block_sizes[j]              đúng → 17   sai → 19
17  output[i].v += jacobian_blocks[j][i * block_size + k] * inputs[j][k].v   → 18
18  ++k                                                            → 16
19  ++j                                                            → 14
20  ++i                                                            → 12
21  return true                                                    → END
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
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function_to_functor.h"
#include "ceres/internal/fixed_array.h"
```

- Đây là method của class `ceres::DynamicCostFunctionToFunctor`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

Cách tạo object của class `DynamicCostFunctionToFunctor`:
Các constructor:
```cpp
  DynamicCostFunctionToFunctor(CostFunction * cost_function)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1121_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
