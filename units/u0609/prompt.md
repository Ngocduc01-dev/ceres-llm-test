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
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `MVM_mat4x1(const int col_a, const double * a, const int col_stride_a, const double * b, double * c, const int kOperation)`, trả về `void`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/small_blas_generic.h`, dòng 211–245

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
211 | static inline void MVM_mat4x1(const int col_a,
212 |                               const double* a,
213 |                               const int col_stride_a,
214 |                               const double* b,
215 |                               double* c,
216 |                               const int kOperation) {
217 |   CERES_GEMM_OPT_NAIVE_HEADER
218 |   double bv = 0.0;
219 | 
220 |   // clang-format off
221 | #define CERES_GEMM_OPT_MVM_MAT4X1_MUL       \
222 |   bv = *pb;                                 \
223 |   cvec4[0] += *(pa                   ) * bv; \
224 |   cvec4[1] += *(pa + col_stride_a    ) * bv; \
225 |   cvec4[2] += *(pa + col_stride_a * 2) * bv; \
226 |   cvec4[3] += *(pa + col_stride_a * 3) * bv; \
227 |   pa++;                                     \
228 |   pb++;
229 |   // clang-format on
230 | 
231 |   for (int k = 0; k < col_m; k += span) {
232 |     CERES_GEMM_OPT_MVM_MAT4X1_MUL
233 |     CERES_GEMM_OPT_MVM_MAT4X1_MUL
234 |     CERES_GEMM_OPT_MVM_MAT4X1_MUL
235 |     CERES_GEMM_OPT_MVM_MAT4X1_MUL
236 |   }
237 | 
238 |   for (int k = col_m; k < col_a; k++) {
239 |     CERES_GEMM_OPT_MVM_MAT4X1_MUL
240 |   }
241 | 
242 |   CERES_GEMM_OPT_STORE_MAT1X4
243 | 
244 | #undef CERES_GEMM_OPT_MVM_MAT4X1_MUL
245 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4

START → 1
1   double cvec4[4] = {0., 0., 0., 0.}
    const double *pa = a
    const double *pb = b
    const int span = 4
    int col_r = col_a & (span - 1)
    int col_m = col_a - col_r
    double bv = 0.
    int k = 0                                                      → 2
2   vòng for, điều kiện: k < col_m                                 đúng → 3   sai → 5
3   bv = *pb
    cvec4[0] += *(pa) * bv
    cvec4[1] += *(pa + col_stride_a) * bv
    cvec4[2] += *(pa + col_stride_a * 2) * bv
    cvec4[3] += *(pa + col_stride_a * 3) * bv
    pa++
    pb++
    bv = *pb
    cvec4[0] += *(pa) * bv
    cvec4[1] += *(pa + col_stride_a) * bv
    cvec4[2] += *(pa + col_stride_a * 2) * bv
    cvec4[3] += *(pa + col_stride_a * 3) * bv
    pa++
    pb++
    bv = *pb
    cvec4[0] += *(pa) * bv
    cvec4[1] += *(pa + col_stride_a) * bv
    cvec4[2] += *(pa + col_stride_a * 2) * bv
    cvec4[3] += *(pa + col_stride_a * 3) * bv
    pa++
    pb++
    bv = *pb
    cvec4[0] += *(pa) * bv
    cvec4[1] += *(pa + col_stride_a) * bv
    cvec4[2] += *(pa + col_stride_a * 2) * bv
    cvec4[3] += *(pa + col_stride_a * 3) * bv
    pa++
    pb++                                                           → 4
4   k += span                                                      → 2
5   int k = col_m                                                  → 6
6   vòng for, điều kiện: k < col_a                                 đúng → 7   sai → 9
7   bv = *pb
    cvec4[0] += *(pa) * bv
    cvec4[1] += *(pa + col_stride_a) * bv
    cvec4[2] += *(pa + col_stride_a * 2) * bv
    cvec4[3] += *(pa + col_stride_a * 3) * bv
    pa++
    pb++                                                           → 8
8   k++                                                            → 6
9   if (kOperation > 0)                                            đúng → 10   sai → 12
10  c[0] += cvec4[0]
    c[1] += cvec4[1]
    c[2] += cvec4[2]
    c[3] += cvec4[3]                                               → 11
11  c += 4                                                         → END
12  if (kOperation < 0)                                            đúng → 13   sai → 14
13  c[0] -= cvec4[0]
    c[1] -= cvec4[1]
    c[2] -= cvec4[2]
    c[3] -= cvec4[3]                                               → 11
14  c[0] = cvec4[0]
    c[1] = cvec4[1]
    c[2] = cvec4[2]
    c[3] = cvec4[3]                                                → 11
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
#include "ceres/small_blas_generic.h"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/small_blas_generic.h` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/small_blas_generic.h"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0609_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
