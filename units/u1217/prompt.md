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

- Hàm: `GetCovarianceBlockInTangentOrAmbientSpace(const double * original_parameter_block1, const double * original_parameter_block2, bool lift_covariance_to_ambient_space, double * covariance_block) const`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CovarianceImpl`
- Vị trí: `internal/ceres/covariance_impl.cc`, dòng 128–274

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
128 | bool CovarianceImpl::GetCovarianceBlockInTangentOrAmbientSpace(
129 |     const double* original_parameter_block1,
130 |     const double* original_parameter_block2,
131 |     bool lift_covariance_to_ambient_space,
132 |     double* covariance_block) const {
133 |   CHECK(is_computed_)
134 |       << "Covariance::GetCovarianceBlock called before Covariance::Compute";
135 |   CHECK(is_valid_)
136 |       << "Covariance::GetCovarianceBlock called when Covariance::Compute "
137 |       << "returned false.";
138 | 
139 |   // If either of the two parameter blocks is constant, then the
140 |   // covariance block is also zero.
141 |   if (constant_parameter_blocks_.count(original_parameter_block1) > 0 ||
142 |       constant_parameter_blocks_.count(original_parameter_block2) > 0) {
143 |     const ProblemImpl::ParameterMap& parameter_map = problem_->parameter_map();
144 |     ParameterBlock* block1 = FindOrDie(
145 |         parameter_map, const_cast<double*>(original_parameter_block1));
146 | 
147 |     ParameterBlock* block2 = FindOrDie(
148 |         parameter_map, const_cast<double*>(original_parameter_block2));
149 | 
150 |     const int block1_size = block1->Size();
151 |     const int block2_size = block2->Size();
152 |     const int block1_tangent_size = block1->TangentSize();
153 |     const int block2_tangent_size = block2->TangentSize();
154 |     if (!lift_covariance_to_ambient_space) {
155 |       MatrixRef(covariance_block, block1_tangent_size, block2_tangent_size)
156 |           .setZero();
157 |     } else {
158 |       MatrixRef(covariance_block, block1_size, block2_size).setZero();
159 |     }
160 |     return true;
161 |   }
162 | 
163 |   const double* parameter_block1 = original_parameter_block1;
164 |   const double* parameter_block2 = original_parameter_block2;
165 |   const bool transpose = parameter_block1 > parameter_block2;
166 |   if (transpose) {
167 |     std::swap(parameter_block1, parameter_block2);
168 |   }
169 | 
170 |   // Find where in the covariance matrix the block is located.
171 |   const int row_begin =
172 |       FindOrDie(parameter_block_to_row_index_, parameter_block1);
173 |   const int col_begin =
174 |       FindOrDie(parameter_block_to_row_index_, parameter_block2);
175 |   const int* rows = covariance_matrix_->rows();
176 |   const int* cols = covariance_matrix_->cols();
177 |   const int row_size = rows[row_begin + 1] - rows[row_begin];
178 |   const int* cols_begin = cols + rows[row_begin];
179 | 
180 |   // The only part that requires work is walking the compressed column
181 |   // vector to determine where the set of columns corresponding to the
182 |   // covariance block begin.
183 |   int offset = 0;
184 |   while (cols_begin[offset] != col_begin && offset < row_size) {
185 |     ++offset;
186 |   }
187 | 
188 |   if (offset == row_size) {
189 |     LOG(ERROR) << "Unable to find covariance block for "
190 |                << original_parameter_block1 << " " << original_parameter_block2;
191 |     return false;
192 |   }
193 | 
194 |   const ProblemImpl::ParameterMap& parameter_map = problem_->parameter_map();
195 |   ParameterBlock* block1 =
196 |       FindOrDie(parameter_map, const_cast<double*>(parameter_block1));
197 |   ParameterBlock* block2 =
198 |       FindOrDie(parameter_map, const_cast<double*>(parameter_block2));
199 |   const Manifold* manifold1 = block1->manifold();
200 |   const Manifold* manifold2 = block2->manifold();
201 |   const int block1_size = block1->Size();
202 |   const int block1_tangent_size = block1->TangentSize();
203 |   const int block2_size = block2->Size();
204 |   const int block2_tangent_size = block2->TangentSize();
205 | 
206 |   ConstMatrixRef cov(covariance_matrix_->values() + rows[row_begin],
207 |                      block1_tangent_size,
208 |                      row_size);
209 | 
210 |   // Fast path when there are no manifolds or if the user does not want it
211 |   // lifted to the ambient space.
212 |   if ((manifold1 == nullptr && manifold2 == nullptr) ||
213 |       !lift_covariance_to_ambient_space) {
214 |     if (transpose) {
215 |       MatrixRef(covariance_block, block2_tangent_size, block1_tangent_size) =
216 |           cov.block(0, offset, block1_tangent_size, block2_tangent_size)
217 |               .transpose();
218 |     } else {
219 |       MatrixRef(covariance_block, block1_tangent_size, block2_tangent_size) =
220 |           cov.block(0, offset, block1_tangent_size, block2_tangent_size);
221 |     }
222 |     return true;
223 |   }
224 | 
225 |   // If manifolds are used then the covariance that has been computed is in the
226 |   // tangent space and it needs to be lifted back to the ambient space.
227 |   //
228 |   // This is given by the formula
229 |   //
230 |   //  C'_12 = J_1 C_12 J_2'
231 |   //
232 |   // Where C_12 is the local tangent space covariance for parameter
233 |   // blocks 1 and 2. J_1 and J_2 are respectively the local to global
234 |   // jacobians for parameter blocks 1 and 2.
235 |   //
236 |   // See Result 5.11 on page 142 of Hartley & Zisserman (2nd Edition)
237 |   // for a proof.
238 |   //
239 |   // TODO(sameeragarwal): Add caching the manifold plus_jacobian, so that they
240 |   // are computed just once per parameter block.
241 |   Matrix block1_jacobian(block1_size, block1_tangent_size);
242 |   if (manifold1 == nullptr) {
243 |     block1_jacobian.setIdentity();
244 |   } else {
245 |     manifold1->PlusJacobian(parameter_block1, block1_jacobian.data());
246 |   }
247 | 
248 |   Matrix block2_jacobian(block2_size, block2_tangent_size);
249 |   // Fast path if the user is requesting a diagonal block.
250 |   if (parameter_block1 == parameter_block2) {
251 |     block2_jacobian = block1_jacobian;
252 |   } else {
253 |     if (manifold2 == nullptr) {
254 |       block2_jacobian.setIdentity();
255 |     } else {
256 |       manifold2->PlusJacobian(parameter_block2, block2_jacobian.data());
257 |     }
258 |   }
259 | 
260 |   if (transpose) {
261 |     MatrixRef(covariance_block, block2_size, block1_size) =
262 |         block2_jacobian *
263 |         cov.block(0, offset, block1_tangent_size, block2_tangent_size)
264 |             .transpose() *
265 |         block1_jacobian.transpose();
266 |   } else {
267 |     MatrixRef(covariance_block, block1_size, block2_size) =
268 |         block1_jacobian *
269 |         cov.block(0, offset, block1_tangent_size, block2_tangent_size) *
270 |         block2_jacobian.transpose();
271 |   }
272 | 
273 |   return true;
274 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 11 (và 2 lệnh CHECK)

START → 1
1   CHECK(is_computed_)                                            đúng → 2   sai → DỪNG
2   CHECK(is_valid_)                                               đúng → 3   sai → DỪNG
3   if (constant_parameter_blocks_.count(original_parameter_block1) > 0 || constant_parameter_blocks_.count(original_parameter_block2) > 0)   đúng → 4   sai → 9
4   const ProblemImpl::ParameterMap &parameter_map = problem_->parameter_map()
    FindOrDie(parameter_map, const_cast<double *>(original_parameter_block1) (CXXConstCastExpr, NoOp, double *))
    ParameterBlock *block1 = FindOrDie(parameter_map, const_cast<double *>(original_parameter_block1))
    FindOrDie(parameter_map, const_cast<double *>(original_parameter_block2) (CXXConstCastExpr, NoOp, double *))
    ParameterBlock *block2 = FindOrDie(parameter_map, const_cast<double *>(original_parameter_block2))
    const int block1_size = block1->Size()
    const int block2_size = block2->Size()
    const int block1_tangent_size = block1->TangentSize()
    const int block2_tangent_size = block2->TangentSize()          → 5
5   if (!lift_covariance_to_ambient_space)                         đúng → 6   sai → 8
6   MatrixRef(covariance_block, block1_tangent_size, block2_tangent_size).setZero()   → 7
7   return true                                                    → END
8   MatrixRef(covariance_block, block1_size, block2_size).setZero()   → 7
9   const double *parameter_block1 = original_parameter_block1
    const double *parameter_block2 = original_parameter_block2
    const bool transpose = parameter_block1 > parameter_block2     → 10
10  if (transpose)                                                 đúng → 11   sai → 12
11  std::swap(parameter_block1, parameter_block2)                  → 12
12  const int row_begin = FindOrDie(parameter_block_to_row_index_, parameter_block1)
    const int col_begin = FindOrDie(parameter_block_to_row_index_, parameter_block2)
    const int *rows = covariance_matrix_->rows()
    const int *cols = covariance_matrix_->cols()
    const int row_size = rows[row_begin + 1] - rows[row_begin]
    const int *cols_begin = cols + rows[row_begin]
    int offset = 0                                                 → 13
13  while (cols_begin[offset] != col_begin && offset < row_size)   đúng → 14   sai → 15
14  ++offset                                                       → 13
15  if (offset == row_size)                                        đúng → END   sai → 16
16  const ProblemImpl::ParameterMap &parameter_map = problem_->parameter_map()
    FindOrDie(parameter_map, const_cast<double *>(parameter_block1) (CXXConstCastExpr, NoOp, double *))
    ParameterBlock *block1 = FindOrDie(parameter_map, const_cast<double *>(parameter_block1))
    FindOrDie(parameter_map, const_cast<double *>(parameter_block2) (CXXConstCastExpr, NoOp, double *))
    ParameterBlock *block2 = FindOrDie(parameter_map, const_cast<double *>(parameter_block2))
    const Manifold *manifold1 = block1->manifold()
    const Manifold *manifold2 = block2->manifold()
    const int block1_size = block1->Size()
    const int block1_tangent_size = block1->TangentSize()
    const int block2_size = block2->Size()
    const int block2_tangent_size = block2->TangentSize()
    covariance_matrix_->values() + rows[row_begin], block1_tangent_size, row_size   → 17
17  if (manifold1 == nullptr && manifold2 == nullptr) || !lift_covariance_to_ambient_space   đúng → 18   sai → 22
18  if (transpose)                                                 đúng → 19   sai → 21
19  MatrixRef(covariance_block, block2_tangent_size, block1_tangent_size) = cov.block(0, offset, block1_tangent_size, block2_tangent_size).transpose()   → 20
20  return true                                                    → END
21  MatrixRef(covariance_block, block1_tangent_size, block2_tangent_size) = cov.block(0, offset, block1_tangent_size, block2_tangent_size)   → 20
22  block1_size, block1_tangent_size                               → 23
23  if (manifold1 == nullptr)                                      đúng → 24   sai → 35
24  block1_jacobian.setIdentity()                                  → 25
25  block2_size, block2_tangent_size                               → 26
26  if (parameter_block1 == parameter_block2)                      đúng → 27   sai → 32
27  block2_jacobian = block1_jacobian                              → 28
28  if (transpose)                                                 đúng → 29   sai → 31
29  MatrixRef(covariance_block, block2_size, block1_size) = block2_jacobian * cov.block(0, offset, block1_tangent_size, block2_tangent_size).transpose() * block1_jacobian.transpose()   → 30
30  return true                                                    → END
31  MatrixRef(covariance_block, block1_size, block2_size) = block1_jacobian * cov.block(0, offset, block1_tangent_size, block2_tangent_size) * block2_jacobian.transpose()   → 30
32  if (manifold2 == nullptr)                                      đúng → 33   sai → 34
33  block2_jacobian.setIdentity()                                  → 28
34  manifold2->PlusJacobian(parameter_block2, block2_jacobian.data())   → 28
35  manifold1->PlusJacobian(parameter_block1, block1_jacobian.data())   → 25
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
#include "ceres/manifold.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
```

- Đây là method của class `ceres::internal::CovarianceImpl`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `CovarianceImpl`:
Các constructor:
```cpp
  CovarianceImpl(const Covariance::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1217_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
