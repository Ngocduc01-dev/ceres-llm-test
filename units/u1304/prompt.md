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

- Hàm: `MinimizePolynomial(const Vector & polynomial, const double x_min, const double x_max, double * optimal_x, double * optimal_value)`, trả về `void`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/polynomial.cc`, dòng 272–324

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
272 | void MinimizePolynomial(const Vector& polynomial,
273 |                         const double x_min,
274 |                         const double x_max,
275 |                         double* optimal_x,
276 |                         double* optimal_value) {
277 |   // Find the minimum of the polynomial at the two ends.
278 |   //
279 |   // We start by inspecting the middle of the interval. Technically
280 |   // this is not needed, but we do this to make this code as close to
281 |   // the minFunc package as possible.
282 |   *optimal_x = (x_min + x_max) / 2.0;
283 |   *optimal_value = EvaluatePolynomial(polynomial, *optimal_x);
284 | 
285 |   const double x_min_value = EvaluatePolynomial(polynomial, x_min);
286 |   if (x_min_value < *optimal_value) {
287 |     *optimal_value = x_min_value;
288 |     *optimal_x = x_min;
289 |   }
290 | 
291 |   const double x_max_value = EvaluatePolynomial(polynomial, x_max);
292 |   if (x_max_value < *optimal_value) {
293 |     *optimal_value = x_max_value;
294 |     *optimal_x = x_max;
295 |   }
296 | 
297 |   // If the polynomial is linear or constant, we are done.
298 |   if (polynomial.rows() <= 2) {
299 |     return;
300 |   }
301 | 
302 |   const Vector derivative = DifferentiatePolynomial(polynomial);
303 |   Vector roots_real;
304 |   if (!FindPolynomialRoots(derivative, &roots_real, nullptr)) {
305 |     LOG(WARNING) << "Unable to find the critical points of "
306 |                  << "the interpolating polynomial.";
307 |     return;
308 |   }
309 | 
310 |   // This is a bit of an overkill, as some of the roots may actually
311 |   // have a complex part, but its simpler to just check these values.
312 |   for (int i = 0; i < roots_real.rows(); ++i) {
313 |     const double root = roots_real(i);
314 |     if ((root < x_min) || (root > x_max)) {
315 |       continue;
316 |     }
317 | 
318 |     const double value = EvaluatePolynomial(polynomial, root);
319 |     if (value < *optimal_value) {
320 |       *optimal_value = value;
321 |       *optimal_x = root;
322 |     }
323 |   }
324 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 7

START → 1
1   *optimal_x = (x_min + x_max) / 2.
    *optimal_value = EvaluatePolynomial(polynomial, *optimal_x)
    const double x_min_value = EvaluatePolynomial(polynomial, x_min)   → 2
2   if (x_min_value < *optimal_value)                              đúng → 3   sai → 4
3   *optimal_value = x_min_value
    *optimal_x = x_min                                             → 4
4   const double x_max_value = EvaluatePolynomial(polynomial, x_max)   → 5
5   if (x_max_value < *optimal_value)                              đúng → 6   sai → 7
6   *optimal_value = x_max_value
    *optimal_x = x_max                                             → 7
7   if (polynomial.rows() <= 2)                                    đúng → 8   sai → 9
8   return                                                         → END
9   DifferentiatePolynomial(polynomial)                            → 10
10  if (!FindPolynomialRoots(derivative, &roots_real, nullptr))    đúng → END   sai → 11
11  int i = 0                                                      → 12
12  vòng for, điều kiện: i < roots_real.rows()                     đúng → 13   sai → END
13  const double root = roots_real(i)                              → 14
14  if (root < x_min) || (root > x_max)                            đúng → 15   sai → 17
15  continue                                                       → 16
16  ++i                                                            → 12
17  const double value = EvaluatePolynomial(polynomial, root)      → 18
18  if (value < *optimal_value)                                    đúng → 19   sai → 16
19  *optimal_value = value
    *optimal_x = root                                              → 16
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
#include "ceres/polynomial.h"
```

- Hàm gọi trực tiếp được.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1304_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
