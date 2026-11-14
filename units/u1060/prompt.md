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

- Hàm: `MatrixTransposeVectorMultiply(const double* A, const int num_row_a, const int num_col_a, const double* b, double* c)`, trả về `void`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/small_blas.h`, dòng 470–554

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
470 | template <int kRowA, int kColA, int kOperation>
471 | inline void MatrixTransposeVectorMultiply(const double* A,
472 |                                           const int num_row_a,
473 |                                           const int num_col_a,
474 |                                           const double* b,
475 |                                           double* c) {
476 | #ifdef CERES_NO_CUSTOM_BLAS
477 |   const typename EigenTypes<kRowA, kColA>::ConstMatrixRef Aref(
478 |       A, num_row_a, num_col_a);
479 |   const typename EigenTypes<kRowA>::ConstVectorRef bref(b, num_row_a);
480 |   typename EigenTypes<kColA>::VectorRef cref(c, num_col_a);
481 | 
482 |   // lazyProduct works better than .noalias() for matrix-vector
483 |   // products.
484 |   if (kOperation > 0) {
485 |     cref += Aref.transpose().lazyProduct(bref);
486 |   } else if (kOperation < 0) {
487 |     cref -= Aref.transpose().lazyProduct(bref);
488 |   } else {
489 |     cref = Aref.transpose().lazyProduct(bref);
490 |   }
491 | #else
492 | 
493 |   DCHECK_GT(num_row_a, 0);
494 |   DCHECK_GT(num_col_a, 0);
495 |   DCHECK((kRowA == Eigen::Dynamic) || (kRowA == num_row_a));
496 |   DCHECK((kColA == Eigen::Dynamic) || (kColA == num_col_a));
497 | 
498 |   const int NUM_ROW_A = (kRowA != Eigen::Dynamic ? kRowA : num_row_a);
499 |   const int NUM_COL_A = (kColA != Eigen::Dynamic ? kColA : num_col_a);
500 |   const int span = 4;
501 | 
502 |   // Calculate the remainder part first.
503 | 
504 |   // Process the last odd column if present.
505 |   if (NUM_COL_A & 1) {
506 |     int row = NUM_COL_A - 1;
507 |     const double* pa = &A[row];
508 |     const double* pb = &b[0];
509 |     double tmp = 0.0;
510 |     for (int col = 0; col < NUM_ROW_A; ++col) {
511 |       tmp += *pa * (*pb++);
512 |       pa += NUM_COL_A;
513 |     }
514 |     CERES_GEMM_STORE_SINGLE(c, row, tmp);
515 | 
516 |     // Return directly for efficiency of extremely small matrix multiply.
517 |     if (NUM_COL_A == 1) {
518 |       return;
519 |     }
520 |   }
521 | 
522 |   // Process the couple columns in remainder if present.
523 |   if (NUM_COL_A & 2) {
524 |     int row = NUM_COL_A & (~(span - 1));
525 |     const double* pa = &A[row];
526 |     const double* pb = &b[0];
527 |     double tmp1 = 0.0, tmp2 = 0.0;
528 |     for (int col = 0; col < NUM_ROW_A; ++col) {
529 |       // clang-format off
530 |       double bv = *pb++;
531 |       tmp1 += *(pa    ) * bv;
532 |       tmp2 += *(pa + 1) * bv;
533 |       pa += NUM_COL_A;
534 |       // clang-format on
535 |     }
536 |     CERES_GEMM_STORE_PAIR(c, row, tmp1, tmp2);
537 | 
538 |     // Return directly for efficiency of extremely small matrix multiply.
539 |     if (NUM_COL_A < span) {
540 |       return;
541 |     }
542 |   }
543 | 
544 |   // Calculate the main part with multiples of 4.
545 |   int row_m = NUM_COL_A & (~(span - 1));
546 |   for (int row = 0; row < row_m; row += span) {
547 |     // clang-format off
548 |     MTV_mat4x1(NUM_ROW_A, &A[row], NUM_COL_A,
549 |                &b[0], &c[row], kOperation);
550 |     // clang-format on
551 |   }
552 | 
553 | #endif  // CERES_NO_CUSTOM_BLAS
554 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp MatrixTransposeVectorMultiply<-1, -1, 1>.

Số điểm rẽ nhánh: 7 (và 2 lệnh CHECK)

START → 1
1   DCHECK_GT(num_row_a, 0)                                        đúng → 2   sai → DỪNG
2   DCHECK_GT(num_col_a, 0)                                        đúng → 3   sai → DỪNG
3   (-1 == Eigen::Dynamic) || ...                                  → 4
4   !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_row_a)), 0))) ? ... : ...   → 5
5   !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_col_a)), 0))) ? ... : ...   → 6
6   const int NUM_ROW_A = (-1 != Eigen::Dynamic ? -1 : num_row_a)
    -1 != Eigen::Dynamic ? ... : ...                               → 7
7   const int NUM_COL_A = (-1 != Eigen::Dynamic ? -1 : num_col_a)
    const int span = 4                                             → 8
8   if (NUM_COL_A & 1)                                             đúng → 9   sai → 17
9   int row = NUM_COL_A - 1
    const double *pa = &A[row]
    const double *pb = &b[0]
    double tmp = 0.
    int col = 0                                                    → 10
10  vòng for, điều kiện: col < NUM_ROW_A                           đúng → 11   sai → 13
11  tmp += *pa * (*pb++)
    pa += NUM_COL_A                                                → 12
12  ++col                                                          → 10
13  if 1 > 0                                                       → 14
14  c[row] += tmp                                                  → 15
15  if (NUM_COL_A == 1)                                            đúng → 16   sai → 17
16  return                                                         → END
17  if (NUM_COL_A & 2)                                             đúng → 18   sai → 26
18  int row = NUM_COL_A & (~(span - 1))
    const double *pa = &A[row]
    const double *pb = &b[0]
    double tmp1 = 0.
    double tmp2 = 0.
    int col = 0                                                    → 19
19  vòng for, điều kiện: col < NUM_ROW_A                           đúng → 20   sai → 22
20  double bv = *pb++
    tmp1 += *(pa) * bv
    tmp2 += *(pa + 1) * bv
    pa += NUM_COL_A                                                → 21
21  ++col                                                          → 19
22  if 1 > 0                                                       → 23
23  c[row] += tmp1
    c[row + 1] += tmp2                                             → 24
24  if (NUM_COL_A < span)                                          đúng → 25   sai → 26
25  return                                                         → END
26  int row_m = NUM_COL_A & (~(span - 1))
    int row = 0                                                    → 27
27  vòng for, điều kiện: row < row_m                               đúng → 28   sai → END
28  MTV_mat4x1(NUM_ROW_A, &A[row], NUM_COL_A, &b[0], &c[row], 1)   → 29
29  row += span                                                    → 27
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

- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1060_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
