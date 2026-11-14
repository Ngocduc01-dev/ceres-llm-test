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

- Hàm: `MatrixTransposeMatrixMultiplyNaive(xem mã nguồn – hàm được sinh ra từ macro)`, trả về `void`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/small_blas.h`, dòng 280–351

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
280 | CERES_GEMM_BEGIN(MatrixTransposeMatrixMultiplyNaive) {
281 |   CERES_GEMM_NAIVE_HEADER
282 |   DCHECK_EQ(NUM_ROW_A, NUM_ROW_B);
283 | 
284 |   const int NUM_ROW_C = NUM_COL_A;
285 |   const int NUM_COL_C = NUM_COL_B;
286 |   DCHECK_LE(start_row_c + NUM_ROW_C, row_stride_c);
287 |   DCHECK_LE(start_col_c + NUM_COL_C, col_stride_c);
288 |   const int span = 4;
289 | 
290 |   // Process the remainder part first.
291 | 
292 |   // Process the last odd column if present.
293 |   if (NUM_COL_C & 1) {
294 |     int col = NUM_COL_C - 1;
295 |     for (int row = 0; row < NUM_ROW_C; ++row) {
296 |       const double* pa = &A[row];
297 |       const double* pb = &B[col];
298 |       double tmp = 0.0;
299 |       for (int k = 0; k < NUM_ROW_A; ++k) {
300 |         tmp += pa[0] * pb[0];
301 |         pa += NUM_COL_A;
302 |         pb += NUM_COL_B;
303 |       }
304 | 
305 |       const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
306 |       CERES_GEMM_STORE_SINGLE(C, index, tmp);
307 |     }
308 | 
309 |     // Return directly for efficiency of extremely small matrix multiply.
310 |     if (NUM_COL_C == 1) {
311 |       return;
312 |     }
313 |   }
314 | 
315 |   // Process the couple columns in remainder if present.
316 |   if (NUM_COL_C & 2) {
317 |     int col = NUM_COL_C & (~(span - 1));
318 |     for (int row = 0; row < NUM_ROW_C; ++row) {
319 |       const double* pa = &A[row];
320 |       const double* pb = &B[col];
321 |       double tmp1 = 0.0, tmp2 = 0.0;
322 |       for (int k = 0; k < NUM_ROW_A; ++k) {
323 |         double av = *pa;
324 |         tmp1 += av * pb[0];
325 |         tmp2 += av * pb[1];
326 |         pa += NUM_COL_A;
327 |         pb += NUM_COL_B;
328 |       }
329 | 
330 |       const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
331 |       CERES_GEMM_STORE_PAIR(C, index, tmp1, tmp2);
332 |     }
333 | 
334 |     // Return directly for efficiency of extremely small matrix multiply.
335 |     if (NUM_COL_C < span) {
336 |       return;
337 |     }
338 |   }
339 | 
340 |   // Process the main part with multiples of 4.
341 |   int col_m = NUM_COL_C & (~(span - 1));
342 |   for (int col = 0; col < col_m; col += span) {
343 |     for (int row = 0; row < NUM_ROW_C; ++row) {
344 |       const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
345 |       // clang-format off
346 |       MTM_mat1x4(NUM_ROW_A, &A[row], NUM_COL_A,
347 |                  &B[col], NUM_COL_B, &C[index], kOperation);
348 |       // clang-format on
349 |     }
350 |   }
351 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp MatrixTransposeMatrixMultiplyNaive<-1, -1, -1, -1, 1> (lấy từ một chỗ Ceres dùng thật).

Số điểm rẽ nhánh: 10 (và 11 lệnh CHECK)

START → 1
1   CERES_GEMM_NAIVE_HEADER                                        đúng → 2   sai → DỪNG
2   CERES_GEMM_NAIVE_HEADER                                        đúng → 3   sai → DỪNG
3   CERES_GEMM_NAIVE_HEADER                                        đúng → 4   sai → DỪNG
4   CERES_GEMM_NAIVE_HEADER                                        đúng → 5   sai → DỪNG
5   CERES_GEMM_NAIVE_HEADER                                        đúng → 6   sai → DỪNG
6   CERES_GEMM_NAIVE_HEADER                                        đúng → 7   sai → DỪNG
7   CERES_GEMM_NAIVE_HEADER                                        đúng → 8   sai → DỪNG
8   CERES_GEMM_NAIVE_HEADER                                        đúng → 9   sai → DỪNG
9   (-1 == Eigen::Dynamic) || ...                                  → 10
10  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_row_a)), 0))) ? ... : ...   → 11
11  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_col_a)), 0))) ? ... : ...   → 12
12  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_row_b)), 0))) ? ... : ...   → 13
13  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_col_b)), 0))) ? ... : ...   → 14
14  const int NUM_ROW_A = (-1 != Eigen::Dynamic ? -1 : num_row_a)
    -1 != Eigen::Dynamic ? ... : ...                               → 15
15  const int NUM_COL_A = (-1 != Eigen::Dynamic ? -1 : num_col_a)
    -1 != Eigen::Dynamic ? ... : ...                               → 16
16  const int NUM_ROW_B = (-1 != Eigen::Dynamic ? -1 : num_row_b)
    -1 != Eigen::Dynamic ? ... : ...                               → 17
17  const int NUM_COL_B = (-1 != Eigen::Dynamic ? -1 : num_col_b)   → 18
18  DCHECK_EQ(NUM_ROW_A, NUM_ROW_B)                                đúng → 19   sai → DỪNG
19  const int NUM_ROW_C = NUM_COL_A
    const int NUM_COL_C = NUM_COL_B                                → 20
20  DCHECK_LE(start_row_c + NUM_ROW_C, row_stride_c)               đúng → 21   sai → DỪNG
21  DCHECK_LE(start_col_c + NUM_COL_C, col_stride_c)               đúng → 22   sai → DỪNG
22  const int span = 4                                             → 23
23  if (NUM_COL_C & 1)                                             đúng → 24   sai → 35
24  int col = NUM_COL_C - 1
    int row = 0                                                    → 25
25  vòng for, điều kiện: row < NUM_ROW_C                           đúng → 26   sai → 33
26  const double *pa = &A[row]
    const double *pb = &B[col]
    double tmp = 0.
    int k = 0                                                      → 27
27  vòng for, điều kiện: k < NUM_ROW_A                             đúng → 28   sai → 30
28  tmp += pa[0] * pb[0]
    pa += NUM_COL_A
    pb += NUM_COL_B                                                → 29
29  ++k                                                            → 27
30  const int index = (row + start_row_c) * col_stride_c + start_col_c + col
    if 1 > 0                                                       → 31
31  C[index] += tmp                                                → 32
32  ++row                                                          → 25
33  if (NUM_COL_C == 1)                                            đúng → 34   sai → 35
34  return                                                         → END
35  if (NUM_COL_C & 2)                                             đúng → 36   sai → 47
36  int col = NUM_COL_C & (~(span - 1))
    int row = 0                                                    → 37
37  vòng for, điều kiện: row < NUM_ROW_C                           đúng → 38   sai → 45
38  const double *pa = &A[row]
    const double *pb = &B[col]
    double tmp1 = 0.
    double tmp2 = 0.
    int k = 0                                                      → 39
39  vòng for, điều kiện: k < NUM_ROW_A                             đúng → 40   sai → 42
40  double av = *pa
    tmp1 += av * pb[0]
    tmp2 += av * pb[1]
    pa += NUM_COL_A
    pb += NUM_COL_B                                                → 41
41  ++k                                                            → 39
42  const int index = (row + start_row_c) * col_stride_c + start_col_c + col
    if 1 > 0                                                       → 43
43  C[index] += tmp1
    C[index + 1] += tmp2                                           → 44
44  ++row                                                          → 37
45  if (NUM_COL_C < span)                                          đúng → 46   sai → 47
46  return                                                         → END
47  int col_m = NUM_COL_C & (~(span - 1))
    int col = 0                                                    → 48
48  vòng for, điều kiện: col < col_m                               đúng → 49   sai → END
49  int row = 0                                                    → 50
50  vòng for, điều kiện: row < NUM_ROW_C                           đúng → 51   sai → 53
51  const int index = (row + start_row_c) * col_stride_c + start_col_c + col
    MTM_mat1x4(NUM_ROW_A, &A[row], NUM_COL_A, &B[col], NUM_COL_B, &C[index], 1)   → 52
52  ++row                                                          → 50
53  col += span                                                    → 48
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
#include "ceres/small_blas.h"
#include "ceres/small_blas_generic.h"
```

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1062_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
