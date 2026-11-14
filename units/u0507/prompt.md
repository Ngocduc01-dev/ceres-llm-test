# 1. VAI TRÒ VÀ MỤC TIÊU

Bạn là kỹ sư kiểm thử hộp trắng (white-box) cho mã nguồn C++.
Nhiệm vụ: với **một unit** cho ở mục 3, áp dụng **kiểm thử luồng điều khiển (Control Flow Testing – CFT)** theo **độ đo C2 (phủ nhánh)** để thiết kế bộ test case, rồi viết **một file GoogleTest compile được** chứa toàn bộ test case đó.

Bối cảnh:
- Dự án: **Ceres Solver 2.2.0** (C++17), dùng Eigen, glog. Không có tài liệu đặc tả.
- Unit = một hàm hoặc method có thân hàm. Chỉ làm **unit testing**: mỗi test gọi trực tiếp unit đang xét.
- **Không có đặc tả nên không có kết quả mong đợi (Expected Output – EO).** Mục tiêu duy nhất là **đi qua được các nhánh**. Không viết assertion so sánh giá trị đúng/sai.

---

# 2. KHÁI NIỆM VÀ QUY ƯỚC (dùng thống nhất trong toàn bộ câu trả lời)

**2.1. Đồ thị dòng điều khiển (Control Flow Graph – CFG)** của một unit là đồ thị có hướng G = (N, E):
- **Node (đỉnh):** một khối lệnh tuần tự liên tiếp (gộp các lệnh không rẽ nhánh), hoặc một **điểm quyết định**. Có 1 node bắt đầu và 1 node kết thúc (các `return` cùng nối tới node kết thúc).
- **Điểm quyết định:** điều kiện của `if`, `else if`, `while`, `for`, `do-while`, `switch/case`, toán tử `?:`.
- **Cạnh (edge):** đường đi từ node này sang node khác. Mỗi điểm quyết định có **2 cạnh ra** gắn nhãn **T (True)** và **F (False)**; `switch` có 1 cạnh cho mỗi `case` và `default`.
- Đặt tên node theo **số dòng** trong mã nguồn mục 3 (vd. `N12`, `D15` cho điểm quyết định ở dòng 15).

**2.2. Độ đo C2 – phủ nhánh (Branch / Decision Coverage):** mọi cạnh ra của mọi điểm quyết định đều phải được thực thi **ít nhất một lần** bởi bộ test.

  **Độ phủ C2 = (số nhánh đã được thực thi) / (tổng số nhánh) × 100%**

- C2 mạnh hơn C1 (phủ câu lệnh – mọi câu lệnh chạy ít nhất 1 lần): đạt C2 thì đạt C1, ngược lại không đúng. Ví dụ `if (x > 0) y = 1;` không có `else`: chỉ cần x > 0 là đạt C1, nhưng C2 cần thêm 1 test với x ≤ 0.
- Với **C2**, điều kiện ghép (`a && b`, `a || b`) giữ nguyên là **một** điểm quyết định, chỉ cần toàn bộ biểu thức nhận cả T và F. (Tách từng điều kiện con là C3 – không yêu cầu ở đây.)

**2.3. Vòng lặp:**

*Liên hệ với C2:* điều kiện lặp là một điểm quyết định. C2 chỉ cần nhánh T (vào thân vòng lặp) và nhánh F (thoát) đều được đi qua. Kiểm thử vòng lặp dưới đây chặt hơn C2, dùng để chọn **số lần lặp** cho các test case.

Chia vòng lặp làm **2 loại**:

| Loại | Ví dụ | Số lần lặp cần test |
|---|---|---|
| **Có cận trên n** (hằng số, kích thước input, tham số số lần lặp tối đa) | `for (i < 3)`, `for (i < size_)`, `iteration < max_num_iterations` | **0, 1, 2, m (ở giữa), n−1, n, n+1** |
| **Không có cận** (thoát khi đạt điều kiện) | `while (!converged)`, `while (true) { ... break; }` | **0, 1, 2** và **mỗi lối thoát** (`break`, `return`, điều kiện sai) ít nhất 1 test |

- **Cận là biến** (kích thước dữ liệu, tham số): chọn giá trị **ngẫu nhiên** trong miền phù hợp với số lần lặp cần đạt (input nhỏ, n ≤ 5 nếu tự chọn được).
- Số lần lặp nào **không đạt được** (vd. n+1 khi vòng lặp chạy đúng bằng kích thước input, 0 khi điều kiện luôn đúng lần đầu): ghi "không áp dụng / bất khả thi" kèm lý do ở A5, **không bỏ qua im lặng**.
- Vòng lặp không có cận: chọn input **hội tụ nhanh** để dừng sau vài vòng; nếu không chắc vòng lặp dừng, ghi "nguy cơ không dừng" ở A5.

**2.4. Test path (đường kiểm thử):** dãy node từ node bắt đầu tới node kết thúc, ghi kèm nhãn nhánh, vd. `N10 → D12(T) → N13 → D15(F) → END`.

**2.5. Điều kiện đường đi (path condition):** hội (AND) các điều kiện của các nhánh trên test path. Input của test phải làm điều kiện này đúng.

**2.6. Nhánh bất khả thi (infeasible):** nhánh không có input nào đi tới được (vd. điều kiện mâu thuẫn, code chết). Phải chỉ rõ và giải thích; **không được xoá khỏi mẫu số** để báo đạt 100%.

**2.7. Đặc thù C++ / Ceres:**
- `CHECK(...)`, `CHECK_EQ(...)`, `DCHECK(...)` của glog: nhánh "điều kiện sai" làm **chương trình dừng** (abort). **Không** cố tình làm CHECK sai; ghi nhánh đó vào mục "Nhánh không thiết kế test" với lý do "nhánh CHECK sai – làm dừng chương trình".
- Đánh giá ngắn mạch (short-circuit): trong `a && b`, nếu `a` sai thì `b` không được đánh giá.
- Ngoại lệ (`throw`) do compiler sinh không tính là nhánh.
- `if constexpr` được quyết định lúc compile → **không** phải điểm quyết định.
- Nếu cần `#define private public`: đặt **sau** các `#include` của gtest, thư viện chuẩn, Eigen và **trước** `#include` header của Ceres (kèm `#define protected public`).

---

# 3. ĐẦU VÀO

**3.0. Quy ước cho file test**

`#include` được phép dùng:
```cpp
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
```

Cách gọi unit:
- Hàm `public`, gọi trực tiếp.

## Unit: `ceres::TolerantLoss::TolerantLoss`  (internal/ceres/loss_function.cc:93–97)

**Mã nguồn (có đánh số dòng):**
```cpp
93 | TolerantLoss::TolerantLoss(double a, double b)
94 |     : a_(a), b_(b), c_(b * log(1.0 + exp(-a / b))) {
95 |   CHECK_GE(a, 0.0);
96 |   CHECK_GT(b, 0.0);
97 | }
```

**CFG:** tool không dựng được cho unit này – hãy **tự dựng** theo mục 2.1 từ mã nguồn trên.

**3.1. Ngữ cảnh tham khảo** (chỉ dùng để viết code đúng, không phải unit cần test):

Khai báo class chứa unit:
```cpp
class CERES_EXPORT TolerantLoss final : public LossFunction {
 public:
  explicit TolerantLoss(double a, double b);
  void Evaluate(double, double*) const override;

 private:
  const double a_, b_, c_;
};
```

Các kiểu dữ liệu được dùng:
```cpp
class CERES_EXPORT TolerantLoss final : public LossFunction {
 public:
  explicit TolerantLoss(double a, double b);
  void Evaluate(double, double*) const override;

 private:
  const double a_, b_, c_;
};
```

Các hàm unit gọi tới (chỉ signature):
```cpp
// (không có)
```

Hàm hỗ trợ tạo input (BẮT BUỘC dùng nếu có):
```cpp
// (không có)
```

Test có sẵn của Ceres để tham khảo cách khởi tạo object:
```cpp
}

TEST(LossFunction, TolerantLoss) {
  AssertLossFunctionIsValid(TolerantLoss(0.7, 0.4), 0.357);
  AssertLossFunctionIsValid(TolerantLoss(0.7, 0.4), 1.792);
  AssertLossFunctionIsValid(TolerantLoss(0.7, 0.4), 55.5);
  AssertLossFunctionIsValid(TolerantLoss(1.3, 0.1), 0.357);
  AssertLossFunctionIsValid(TolerantLoss(1.3, 0.1), 1.792);
  AssertLossFunctionIsValid(TolerantLoss(1.3, 0.1), 55.5);
  // Check the value at zero is actually zero.
  double rho[3];
  TolerantLoss(0.7, 0.4).Evaluate(0.0, rho);
  ASSERT_NEAR(rho[0], 0.0, 1e-6);
  // Check that loss before and after the approximation threshold are good.
  // A threshold of 36.7 is used by the implementation.
  AssertLossFunctionIsValid(TolerantLoss(20.0, 1.0), 20.0 + 36.6);
  AssertLossFunctionIsValid(TolerantLoss(20.0, 1.0), 20.0 + 36.7);
  AssertLossFunctionIsValid(TolerantLoss(20.0, 1.0), 20.0 + 36.8);
  AssertLossFunctionIsValid(TolerantLoss(20.0, 1.0), 20.0 + 1000.0);
}

TEST(LossFunction, TukeyLoss) {
  AssertLossFunctionIsValid(TukeyLoss(0.7), 0.357);
  AssertLossFunctionIsValid(TukeyLoss(0.7), 1.792);
  AssertLossFunctionIsValid(TukeyLoss(1.3), 0.357);
  AssertLossFunctionIsValid(TukeyLoss(1.3), 1.792);
  // Check that at s = 0: rho = [0, 1, -2 / a^2].
  double rho[3];
  TukeyLoss(0.7).Evaluate(0.0, rho);
  ASSERT_NEAR(rho[0], 0.0, 1e-6);
  ASSERT_NEAR(rho[1], 1.0, 1e-6);
  ASSERT_NEAR(rho[2], -2.0 / (0.7 * 0.7), 1e-6);
}

TEST(LossFunction, ComposedLoss) {
  {
    HuberLoss f(0.7);
    CauchyLoss g(1.3);
    ComposedLoss c(&f, DO_NOT_TAKE_OWNERSHIP, &g, DO_NOT_TAKE_OWNERSHIP);
    AssertLossFunctionIsValid(c, 0.357);
    AssertLossFunctionIsValid(c, 1.792);
  }

}

TEST(LossFunction, ScaledLoss) {
  // Wrap a few loss functions, and a few scale factors. This can't combine
  // construction with the call to AssertLossFunctionIsValid() because Apple's
  // GCC is unable to eliminate the copy of ScaledLoss, which is not copyable.
  {
    ScaledLoss scaled_loss(nullptr, 6, TAKE_OWNERSHIP);
    AssertLossFunctionIsValid(scaled_loss, 0.323);
  }
```

---

# 4. YÊU CẦU ĐỐI VỚI BỘ TEST (để đạt C2)

Bộ test case của unit phải thoả mãn:
1. **Mỗi nhánh T và F của mỗi điểm quyết định** được ít nhất một test case đi qua (mục 2.2).
2. **Mỗi vòng lặp** được phân loại (có cận / không có cận) và có test cho các số lần lặp ở bảng mục 2.3.
3. **Mỗi test case gắn với đúng một test path** và ghi rõ các nhánh nó phủ (vd. `D12-T, D15-F`).
4. **Số test case tối thiểu:** một test path nên phủ nhiều nhánh nhất có thể; không tạo test trùng nhánh.
5. **Input:**
   - Giải điều kiện đường đi thành **miền giá trị** cho từng tham số / trạng thái object (vd. `n ∈ [1, 5]`, `x[0] < lower_bound`).
   - **Chọn giá trị ngẫu nhiên trong miền đó**, dùng bộ sinh số ngẫu nhiên có **seed cố định** (`std::mt19937 rng(<số hiệu test>)`) để chạy lại cho cùng kết quả.
   - Kích thước nhỏ (mảng, ma trận ≤ 5 phần tử), không dùng file, mạng, thread.
6. **Nhánh bất khả thi** và **nhánh CHECK sai**: không viết test; liệt kê và giải thích (mục 2.6, 2.7).
7. **Không có EO:** không viết `EXPECT_EQ/ASSERT_*` so sánh kết quả. Chỉ được kiểm tra điều kiện tiền đề để chắc chắn đã đi đúng nhánh (vd. `ASSERT_EQ(pb.Size(), n)` sau khi khởi tạo).

---

# 5. CÁC BƯỚC THỰC HIỆN

1. **Đọc** mã nguồn unit và ngữ cảnh mục 3.1: tham số, trạng thái object (biến thành viên) ảnh hưởng tới điều kiện, các hàm được gọi.
2. **Chuẩn hoá CFG:** đọc CFG dựng sẵn ở mục 3 theo "Cách đọc CFG", đối chiếu với mã nguồn, gộp chuỗi `&&`/`||` và khối `CHECK`, đổi tên node theo số dòng → bảng A1. (Nếu không có CFG dựng sẵn: tự dựng theo mục 2.1.)
3. **Liệt kê nhánh cần phủ** (cặp T/F của từng điểm quyết định) → đây là **mẫu số** của độ phủ C2. Đánh dấu nhánh bất khả thi và nhánh CHECK sai.
4. **Chọn tập test path** ít nhất phủ hết các nhánh khả thi.
5. **Giải điều kiện đường đi** của từng test path → miền giá trị input → chọn input ngẫu nhiên trong miền (mục 4.5).
6. **Viết code GoogleTest:** khởi tạo object/tham số cho từng test path, gọi unit **đúng một lần** cho mỗi test.
7. **Tự kiểm tra** trước khi trả lời: mỗi nhánh khả thi đã có test chưa; mọi tên hàm/kiểu có trong mục 3 không; mọi `#include` có trong danh sách cho phép không; code có compile được không (đủ namespace, đủ dấu `;`).

---

# 6. KẾT QUẢ CẦN TRẢ VỀ (đúng thứ tự, định dạng Markdown)

## Phần A – Phân tích unit

**A1. CFG (đã chuẩn hoá)**
- Bảng node: `| Node | Dòng | Khối Clang tương ứng | Nội dung | Loại (khối lệnh / quyết định / bắt đầu / kết thúc) |`
- Bảng cạnh: `| Từ | Đến | Nhãn (T/F/case) |`
- Sơ đồ Mermaid (`flowchart TD`).
- Độ phức tạp cyclomatic: V(G) = E − N + 2 = (số điểm quyết định) + 1, ghi rõ phép tính.

**A2. Danh sách nhánh (mẫu số C2)**
`| Mã nhánh | Điểm quyết định | Điều kiện | Nhánh | Khả thi? | Ghi chú |`

**A3. Test path**
- Bảng vòng lặp (nếu có): `| Vòng lặp (dòng) | Có cận / không có cận | n | Số lần lặp cần test | Không áp dụng / bất khả thi (lý do) |`
- `| Path | Dãy node | Số lần lặp (nếu đi qua vòng lặp) | Điều kiện đường đi | Nhánh phủ |`

**A4. Bộ test case**
`| Test ID | Path | Miền giá trị input | Input đã chọn (seed) | Nhánh phủ |`

**A5. Độ phủ C2 dự kiến**
- Ma trận `| Mã nhánh | Test phủ |`
- `C2 dự kiến = <số nhánh có test> / <tổng số nhánh> = <x>%` – ghi rõ là **dự kiến**, chưa đo; độ phủ thật sẽ đo bằng gcov.
- Danh sách nhánh không thiết kế test kèm lý do.

## Phần B – File test

Đúng **một** khối code, mở đầu bằng dòng `// FILE: u0507_test.cc`:
```cpp
// FILE: u0507_test.cc
#include "gtest/gtest.h"
// ... include trong danh sách cho phép
namespace ceres::internal {   // hoặc namespace của unit
// Mỗi test case ở A4 là một TEST, tên: TEST(Gen_<Class>_<Unit>, <TestID>_<mã nhánh>)
// Comment ngay trên mỗi TEST: path và các nhánh phủ.
}
```
Trạng thái: **Not Run** (chưa compile/chạy).

---

# 7. RÀNG BUỘC

- Chỉ dùng hàm, kiểu, `#include` có trong mục 3. **Không bịa API.** Nếu thiếu thông tin để gọi được unit, ghi rõ thiếu gì trong A5, không đoán.
- Không sửa mã nguồn Ceres, không mock chính unit đang test.
- Không viết assertion về giá trị kết quả (không có EO).
- Không tuyên bố đã đạt độ phủ đo được; chỉ ghi độ phủ **dự kiến**.
- Không dùng `...` thay cho phần code cần thiết. Code phải đầy đủ, compile được.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
