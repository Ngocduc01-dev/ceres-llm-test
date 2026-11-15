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

- Hàm: `EvaluateJacobianForParameterBlock(const CostFunctor * functor, const double * residuals_at_eval_point, const NumericDiffOptions & options, int num_residuals, int parameter_block_index, int parameter_block_size, double ** parameters, double * jacobian)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::NumericDiff` (class template)
- Vị trí: `include/ceres/internal/numeric_diff.h`, dòng 63–170

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 63 |   static bool EvaluateJacobianForParameterBlock(
 64 |       const CostFunctor* functor,
 65 |       const double* residuals_at_eval_point,
 66 |       const NumericDiffOptions& options,
 67 |       int num_residuals,
 68 |       int parameter_block_index,
 69 |       int parameter_block_size,
 70 |       double** parameters,
 71 |       double* jacobian) {
 72 |     using Eigen::ColMajor;
 73 |     using Eigen::Map;
 74 |     using Eigen::Matrix;
 75 |     using Eigen::RowMajor;
 76 | 
 77 |     DCHECK(jacobian);
 78 | 
 79 |     const int num_residuals_internal =
 80 |         (kNumResiduals != ceres::DYNAMIC ? kNumResiduals : num_residuals);
 81 |     const int parameter_block_index_internal =
 82 |         (kParameterBlock != ceres::DYNAMIC ? kParameterBlock
 83 |                                            : parameter_block_index);
 84 |     const int parameter_block_size_internal =
 85 |         (kParameterBlockSize != ceres::DYNAMIC ? kParameterBlockSize
 86 |                                                : parameter_block_size);
 87 | 
 88 |     using ResidualVector = Matrix<double, kNumResiduals, 1>;
 89 |     using ParameterVector = Matrix<double, kParameterBlockSize, 1>;
 90 | 
 91 |     // The convoluted reasoning for choosing the Row/Column major
 92 |     // ordering of the matrix is an artifact of the restrictions in
 93 |     // Eigen that prevent it from creating RowMajor matrices with a
 94 |     // single column. In these cases, we ask for a ColMajor matrix.
 95 |     using JacobianMatrix =
 96 |         Matrix<double,
 97 |                kNumResiduals,
 98 |                kParameterBlockSize,
 99 |                (kParameterBlockSize == 1) ? ColMajor : RowMajor>;
100 | 
101 |     Map<JacobianMatrix> parameter_jacobian(
102 |         jacobian, num_residuals_internal, parameter_block_size_internal);
103 | 
104 |     Map<ParameterVector> x_plus_delta(
105 |         parameters[parameter_block_index_internal],
106 |         parameter_block_size_internal);
107 |     ParameterVector x(x_plus_delta);
108 |     ParameterVector step_size =
109 |         x.array().abs() * ((kMethod == RIDDERS)
110 |                                ? options.ridders_relative_initial_step_size
111 |                                : options.relative_step_size);
112 | 
113 |     // It is not a good idea to make the step size arbitrarily
114 |     // small. This will lead to problems with round off and numerical
115 |     // instability when dividing by the step size. The general
116 |     // recommendation is to not go down below sqrt(epsilon).
117 |     double min_step_size = std::sqrt(std::numeric_limits<double>::epsilon());
118 | 
119 |     // For Ridders' method, the initial step size is required to be large,
120 |     // thus ridders_relative_initial_step_size is used.
121 |     if (kMethod == RIDDERS) {
122 |       min_step_size =
123 |           (std::max)(min_step_size, options.ridders_relative_initial_step_size);
124 |     }
125 | 
126 |     // For each parameter in the parameter block, use finite differences to
127 |     // compute the derivative for that parameter.
128 |     FixedArray<double> temp_residual_array(num_residuals_internal);
129 |     FixedArray<double> residual_array(num_residuals_internal);
130 |     Map<ResidualVector> residuals(residual_array.data(),
131 |                                   num_residuals_internal);
132 | 
133 |     for (int j = 0; j < parameter_block_size_internal; ++j) {
134 |       const double delta = (std::max)(min_step_size, step_size(j));
135 | 
136 |       if (kMethod == RIDDERS) {
137 |         if (!EvaluateRiddersJacobianColumn(functor,
138 |                                            j,
139 |                                            delta,
140 |                                            options,
141 |                                            num_residuals_internal,
142 |                                            parameter_block_size_internal,
143 |                                            x.data(),
144 |                                            residuals_at_eval_point,
145 |                                            parameters,
146 |                                            x_plus_delta.data(),
147 |                                            temp_residual_array.data(),
148 |                                            residual_array.data())) {
149 |           return false;
150 |         }
151 |       } else {
152 |         if (!EvaluateJacobianColumn(functor,
153 |                                     j,
154 |                                     delta,
155 |                                     num_residuals_internal,
156 |                                     parameter_block_size_internal,
157 |                                     x.data(),
158 |                                     residuals_at_eval_point,
159 |                                     parameters,
160 |                                     x_plus_delta.data(),
161 |                                     temp_residual_array.data(),
162 |                                     residual_array.data())) {
163 |           return false;
164 |         }
165 |       }
166 | 
167 |       parameter_jacobian.col(j).matrix() = residuals;
168 |     }
169 |     return true;
170 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp NumericDiff<PlusFunctor, RIDDERS, -1, ParameterDims<true>, -1, -1>.

Số điểm rẽ nhánh: 2 (và 1 lệnh CHECK)

START → 1
1   DCHECK(jacobian)                                               đúng → 2   sai → DỪNG
2   const int num_residuals_internal = (-1 != ceres::DYNAMIC ? -1 : num_residuals)
    -1 != ceres::DYNAMIC ? ... : ...                               → 3
3   const int parameter_block_index_internal = (-1 != ceres::DYNAMIC ? -1 : parameter_block_index)
    -1 != ceres::DYNAMIC ? ... : ...                               → 4
4   const int parameter_block_size_internal = (-1 != ceres::DYNAMIC ? -1 : parameter_block_size)
    jacobian, num_residuals_internal, parameter_block_size_internal
    parameters[parameter_block_index_internal], parameter_block_size_internal
    ((ceres::NumericDiffMethodType)2U == RIDDERS) ? ... : ...      → 5
5   x.array().abs() * (((ceres::NumericDiffMethodType)2U == RIDDERS) ? options.ridders_relative_initial_step_size : options.relative_step_size)
    double min_step_size = std::sqrt(std::numeric_limits<double>::epsilon())
    if (ceres::NumericDiffMethodType)2U == RIDDERS                 → 6
6   min_step_size = (std::max)(min_step_size, options.ridders_relative_initial_step_size)   → 7
7   residual_array.data(), num_residuals_internal
    int j = 0                                                      → 8
8   vòng for, điều kiện: j < parameter_block_size_internal         đúng → 9   sai → 14
9   const double delta = (std::max)(min_step_size, step_size(j))
    if (ceres::NumericDiffMethodType)2U == RIDDERS                 → 10
10  if (!EvaluateRiddersJacobianColumn(functor, j, delta, options, num_residuals_internal, parameter_block_size_internal, x.data(), residuals_at_eval_point, parameters, x_plus_delta.data(), temp_residual_array.data(), residual_array.data()))   đúng → 11   sai → 12
11  return false                                                   → END
12  parameter_jacobian.col(j).matrix() = residuals                 → 13
13  ++j                                                            → 8
14  return true                                                    → END
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
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"
```

- Đây là method của class `ceres::internal::NumericDiff`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

Cách tạo object của class `NumericDiff`:
- Class không tự khai báo constructor → tạo bằng constructor mặc định: `NumericDiff obj;`

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1305_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
