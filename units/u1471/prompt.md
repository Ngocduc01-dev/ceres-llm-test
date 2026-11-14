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

- Hàm: `Evaluate(const bool apply_loss_function, double * cost, double * residuals, double ** jacobians, double * scratch) const`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::ResidualBlock`
- Vị trí: `internal/ceres/residual_block.cc`, dòng 68–196

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 68 | bool ResidualBlock::Evaluate(const bool apply_loss_function,
 69 |                              double* cost,
 70 |                              double* residuals,
 71 |                              double** jacobians,
 72 |                              double* scratch) const {
 73 |   const int num_parameter_blocks = NumParameterBlocks();
 74 |   const int num_residuals = cost_function_->num_residuals();
 75 | 
 76 |   // Collect the parameters from their blocks. This will rarely allocate, since
 77 |   // residuals taking more than 8 parameter block arguments are rare.
 78 |   FixedArray<const double*, 8> parameters(num_parameter_blocks);
 79 |   for (int i = 0; i < num_parameter_blocks; ++i) {
 80 |     parameters[i] = parameter_blocks_[i]->state();
 81 |   }
 82 | 
 83 |   // Put pointers into the scratch space into global_jacobians as appropriate.
 84 |   FixedArray<double*, 8> global_jacobians(num_parameter_blocks);
 85 |   if (jacobians != nullptr) {
 86 |     for (int i = 0; i < num_parameter_blocks; ++i) {
 87 |       const ParameterBlock* parameter_block = parameter_blocks_[i];
 88 |       if (jacobians[i] != nullptr &&
 89 |           parameter_block->PlusJacobian() != nullptr) {
 90 |         global_jacobians[i] = scratch;
 91 |         scratch += num_residuals * parameter_block->Size();
 92 |       } else {
 93 |         global_jacobians[i] = jacobians[i];
 94 |       }
 95 |     }
 96 |   }
 97 | 
 98 |   // If the caller didn't request residuals, use the scratch space for them.
 99 |   bool outputting_residuals = (residuals != nullptr);
100 |   if (!outputting_residuals) {
101 |     residuals = scratch;
102 |   }
103 | 
104 |   // Invalidate the evaluation buffers so that we can check them after
105 |   // the CostFunction::Evaluate call, to see if all the return values
106 |   // that were required were written to and that they are finite.
107 |   double** eval_jacobians =
108 |       (jacobians != nullptr) ? global_jacobians.data() : nullptr;
109 | 
110 |   InvalidateEvaluation(*this, cost, residuals, eval_jacobians);
111 | 
112 |   if (!cost_function_->Evaluate(parameters.data(), residuals, eval_jacobians)) {
113 |     return false;
114 |   }
115 | 
116 |   if (!IsEvaluationValid(*this, parameters.data(), residuals, eval_jacobians)) {
117 |     // clang-format off
118 |     std::string message =
119 |         "\n\n"
120 |         "Error in evaluating the ResidualBlock.\n\n"
121 |         "There are two possible reasons. Either the CostFunction did not evaluate and fill all    \n"  // NOLINT
122 |         "residual and jacobians that were requested or there was a non-finite value (nan/infinite)\n"  // NOLINT
123 |         "generated during the or jacobian computation. \n\n" +
124 |         EvaluationToString(
125 |             *this, parameters.data(), cost, residuals, eval_jacobians);
126 |     // clang-format on
127 |     LOG(WARNING) << message;
128 |     return false;
129 |   }
130 | 
131 |   double squared_norm = VectorRef(residuals, num_residuals).squaredNorm();
132 | 
133 |   // Update the plus_jacobian for the manifolds.
134 |   if (jacobians != nullptr) {
135 |     for (int i = 0; i < num_parameter_blocks; ++i) {
136 |       if (jacobians[i] != nullptr) {
137 |         const ParameterBlock* parameter_block = parameter_blocks_[i];
138 | 
139 |         // Apply the Manifold::PlusJacobian to the ambient jacobians.
140 |         if (parameter_block->PlusJacobian() != nullptr) {
141 |           // jacobians[i] = global_jacobians[i] * global_to_local_jacobian.
142 |           MatrixMatrixMultiply<Dynamic, Dynamic, Dynamic, Dynamic, 0>(
143 |               global_jacobians[i],
144 |               num_residuals,
145 |               parameter_block->Size(),
146 |               parameter_block->PlusJacobian(),
147 |               parameter_block->Size(),
148 |               parameter_block->TangentSize(),
149 |               jacobians[i],
150 |               0,
151 |               0,
152 |               num_residuals,
153 |               parameter_block->TangentSize());
154 |         }
155 |       }
156 |     }
157 |   }
158 | 
159 |   if (loss_function_ == nullptr || !apply_loss_function) {
160 |     *cost = 0.5 * squared_norm;
161 |     return true;
162 |   }
163 | 
164 |   double rho[3];
165 |   loss_function_->Evaluate(squared_norm, rho);
166 |   *cost = 0.5 * rho[0];
167 | 
168 |   // No jacobians and not outputting residuals? All done. Doing an early exit
169 |   // here avoids constructing the "Corrector" object below in a common case.
170 |   if (jacobians == nullptr && !outputting_residuals) {
171 |     return true;
172 |   }
173 | 
174 |   // Correct for the effects of the loss function. The jacobians need to be
175 |   // corrected before the residuals, since they use the uncorrected residuals.
176 |   Corrector correct(squared_norm, rho);
177 |   if (jacobians != nullptr) {
178 |     for (int i = 0; i < num_parameter_blocks; ++i) {
179 |       if (jacobians[i] != nullptr) {
180 |         const ParameterBlock* parameter_block = parameter_blocks_[i];
181 | 
182 |         // Correct the jacobians for the loss function.
183 |         correct.CorrectJacobian(num_residuals,
184 |                                 parameter_block->TangentSize(),
185 |                                 residuals,
186 |                                 jacobians[i]);
187 |       }
188 |     }
189 |   }
190 | 
191 |   // Correct the residuals with the loss function.
192 |   if (outputting_residuals) {
193 |     correct.CorrectResiduals(num_residuals, residuals);
194 |   }
195 |   return true;
196 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 18

START → 1
1   const int num_parameter_blocks = NumParameterBlocks()
    const int num_residuals = cost_function_->num_residuals()
    int i = 0                                                      → 2
2   vòng for, điều kiện: i < num_parameter_blocks                  đúng → 3   sai → 5
3   parameters[i] = parameter_blocks_[i]->state()                  → 4
4   ++i                                                            → 2
5   if (jacobians != nullptr)                                      đúng → 6   sai → 13
6   int i = 0                                                      → 7
7   vòng for, điều kiện: i < num_parameter_blocks                  đúng → 8   sai → 13
8   const ParameterBlock *parameter_block = parameter_blocks_[i]   → 9
9   if (jacobians[i] != nullptr && parameter_block->PlusJacobian() != nullptr)   đúng → 10   sai → 12
10  global_jacobians[i] = scratch
    scratch += num_residuals * parameter_block->Size()             → 11
11  ++i                                                            → 7
12  global_jacobians[i] = jacobians[i]                             → 11
13  bool outputting_residuals = (residuals != nullptr)             → 14
14  if (!outputting_residuals)                                     đúng → 15   sai → 16
15  residuals = scratch                                            → 16
16  (jacobians != nullptr) ? ... : ...                             đúng → 17   sai → 17
17  double **eval_jacobians = (jacobians != nullptr) ? global_jacobians.data() : nullptr
    InvalidateEvaluation(*this, cost, residuals, eval_jacobians)   → 18
18  if (!cost_function_->Evaluate(parameters.data(), residuals, eval_jacobians))   đúng → 19   sai → 20
19  return false                                                   → END
20  if (!IsEvaluationValid(*this, parameters.data(), residuals, eval_jacobians))   đúng → END   sai → 21
21  double squared_norm = VectorRef(residuals, num_residuals).squaredNorm()   → 22
22  if (jacobians != nullptr)                                      đúng → 23   sai → 30
23  int i = 0                                                      → 24
24  vòng for, điều kiện: i < num_parameter_blocks                  đúng → 25   sai → 30
25  if (jacobians[i] != nullptr)                                   đúng → 26   sai → 29
26  const ParameterBlock *parameter_block = parameter_blocks_[i]   → 27
27  if (parameter_block->PlusJacobian() != nullptr)                đúng → 28   sai → 29
28  MatrixMatrixMultiply<Dynamic, Dynamic, Dynamic, Dynamic, 0>(global_jacobians[i], num_residuals, parameter_block->Size(), parameter_block->PlusJacobian(), parameter_block->Size(), parameter_block->TangentSize(), jacobians[i], 0, 0, num_residuals, parameter_block->TangentSize())   → 29
29  ++i                                                            → 24
30  if (loss_function_ == nullptr || !apply_loss_function)         đúng → 31   sai → 32
31  *cost = 0.5 * squared_norm
    return true                                                    → END
32  double rho[3]
    loss_function_->Evaluate(squared_norm, rho)
    *cost = 0.5 * rho[0]                                           → 33
33  if (jacobians == nullptr && !outputting_residuals)             đúng → 34   sai → 35
34  return true                                                    → END
35  squared_norm, rho                                              → 36
36  if (jacobians != nullptr)                                      đúng → 37   sai → 42
37  int i = 0                                                      → 38
38  vòng for, điều kiện: i < num_parameter_blocks                  đúng → 39   sai → 42
39  if (jacobians[i] != nullptr)                                   đúng → 40   sai → 41
40  const ParameterBlock *parameter_block = parameter_blocks_[i]
    correct.CorrectJacobian(num_residuals, parameter_block->TangentSize(), residuals, jacobians[i])   → 41
41  ++i                                                            → 38
42  if (outputting_residuals)                                      đúng → 43   sai → 44
43  correct.CorrectResiduals(num_residuals, residuals)             → 44
44  return true                                                    → END
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
#include "ceres/internal/fixed_array.h"
#include "ceres/loss_function.h"
#include "ceres/corrector.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/small_blas.h"
```

- Đây là method của class `ceres::internal::ResidualBlock`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1471_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
