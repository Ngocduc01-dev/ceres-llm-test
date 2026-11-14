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

- Hàm: `AngleAxisRotatePoint(const T angle_axis[3], const T pt[3], T result[3])`, trả về `void`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres`
- Vị trí: `include/ceres/rotation.h`, dòng 791–857

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
791 | template <typename T>
792 | inline void AngleAxisRotatePoint(const T angle_axis[3],
793 |                                  const T pt[3],
794 |                                  T result[3]) {
795 |   DCHECK_NE(pt, result) << "Inplace rotation is not supported.";
796 |   using std::fpclassify;
797 |   using std::hypot;
798 | 
799 |   const T theta = hypot(angle_axis[0], angle_axis[1], angle_axis[2]);
800 | 
801 |   if (fpclassify(theta) != FP_ZERO) {
802 |     // Away from zero, use the rodriguez formula
803 |     //
804 |     //   result = pt costheta +
805 |     //            (w x pt) * sintheta +
806 |     //            w (w . pt) (1 - costheta)
807 |     //
808 |     // We want to be careful to only evaluate the square root if the
809 |     // norm of the angle_axis vector is greater than zero. Otherwise
810 |     // we get a division by zero.
811 |     //
812 |     const T costheta = cos(theta);
813 |     const T sintheta = sin(theta);
814 |     const T theta_inverse = T(1.0) / theta;
815 | 
816 |     const T w[3] = {angle_axis[0] * theta_inverse,
817 |                     angle_axis[1] * theta_inverse,
818 |                     angle_axis[2] * theta_inverse};
819 | 
820 |     // Explicitly inlined evaluation of the cross product for
821 |     // performance reasons.
822 |     const T w_cross_pt[3] = {w[1] * pt[2] - w[2] * pt[1],
823 |                              w[2] * pt[0] - w[0] * pt[2],
824 |                              w[0] * pt[1] - w[1] * pt[0]};
825 |     const T tmp =
826 |         (w[0] * pt[0] + w[1] * pt[1] + w[2] * pt[2]) * (T(1.0) - costheta);
827 | 
828 |     result[0] = pt[0] * costheta + w_cross_pt[0] * sintheta + w[0] * tmp;
829 |     result[1] = pt[1] * costheta + w_cross_pt[1] * sintheta + w[1] * tmp;
830 |     result[2] = pt[2] * costheta + w_cross_pt[2] * sintheta + w[2] * tmp;
831 |   } else {
832 |     // At zero, the first order Taylor approximation of the rotation
833 |     // matrix R corresponding to a vector w and angle theta is
834 |     //
835 |     //   R = I + hat(w) * sin(theta)
836 |     //
837 |     // But sintheta ~ theta and theta * w = angle_axis, which gives us
838 |     //
839 |     //  R = I + hat(angle_axis)
840 |     //
841 |     // and actually performing multiplication with the point pt, gives us
842 |     // R * pt = pt + angle_axis x pt.
843 |     //
844 |     // Switching to the Taylor expansion at zero provides meaningful
845 |     // derivatives when evaluated using Jets.
846 |     //
847 |     // Explicitly inlined evaluation of the cross product for
848 |     // performance reasons.
849 |     const T w_cross_pt[3] = {angle_axis[1] * pt[2] - angle_axis[2] * pt[1],
850 |                              angle_axis[2] * pt[0] - angle_axis[0] * pt[2],
851 |                              angle_axis[0] * pt[1] - angle_axis[1] * pt[0]};
852 | 
853 |     result[0] = pt[0] + w_cross_pt[0];
854 |     result[1] = pt[1] + w_cross_pt[1];
855 |     result[2] = pt[2] + w_cross_pt[2];
856 |   }
857 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp AngleAxisRotatePoint<double> (lấy từ một chỗ Ceres dùng thật).

Số điểm rẽ nhánh: 1 (và 1 lệnh CHECK)

START → 1
1   DCHECK_NE(pt, result)                                          đúng → 2   sai → DỪNG
2   const double theta = hypot(angle_axis[0], angle_axis[1], angle_axis[2])   → 3
3   if (fpclassify(theta) != 2)                                    đúng → 4   sai → 5
4   const double costheta = cos(theta)
    const double sintheta = sin(theta)
    const double theta_inverse = double(1.) / theta
    const double w[3] = {angle_axis[0] * theta_inverse, angle_axis[1] * theta_inverse, angle_axis[2] * theta_inverse}
    const double w_cross_pt[3] = {w[1] * pt[2] - w[2] * pt[1], w[2] * pt[0] - w[0] * pt[2], w[0] * pt[1] - w[1] * pt[0]}
    const double tmp = (w[0] * pt[0] + w[1] * pt[1] + w[2] * pt[2]) * (double(1.) - costheta)
    result[0] = pt[0] * costheta + w_cross_pt[0] * sintheta + w[0] * tmp
    result[1] = pt[1] * costheta + w_cross_pt[1] * sintheta + w[1] * tmp
    result[2] = pt[2] * costheta + w_cross_pt[2] * sintheta + w[2] * tmp   → END
5   const double w_cross_pt[3] = {angle_axis[1] * pt[2] - angle_axis[2] * pt[1], angle_axis[2] * pt[0] - angle_axis[0] * pt[2], angle_axis[0] * pt[1] - angle_axis[1] * pt[0]}
    result[0] = pt[0] + w_cross_pt[0]
    result[1] = pt[1] + w_cross_pt[1]
    result[2] = pt[2] + w_cross_pt[2]                              → END
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
#include "ceres/rotation.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0501_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
