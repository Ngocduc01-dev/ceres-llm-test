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

- Hàm: `EvaluateCostFunction(const CostFunction * function, const double *const * parameters, const std::vector<const Manifold *> & manifolds, Vector * residuals, std::vector<Matrix> * jacobians, std::vector<Matrix> * local_jacobians)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::(namespace không tên)`
- Vị trí: `internal/ceres/gradient_checker.cc`, dòng 55–113

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 55 | bool EvaluateCostFunction(const CostFunction* function,
 56 |                           double const* const* parameters,
 57 |                           const std::vector<const Manifold*>& manifolds,
 58 |                           Vector* residuals,
 59 |                           std::vector<Matrix>* jacobians,
 60 |                           std::vector<Matrix>* local_jacobians) {
 61 |   CHECK(residuals != nullptr);
 62 |   CHECK(jacobians != nullptr);
 63 |   CHECK(local_jacobians != nullptr);
 64 | 
 65 |   const std::vector<int32_t>& block_sizes = function->parameter_block_sizes();
 66 |   const int num_parameter_blocks = block_sizes.size();
 67 | 
 68 |   // Allocate Jacobian matrices in tangent space.
 69 |   local_jacobians->resize(num_parameter_blocks);
 70 |   std::vector<double*> local_jacobian_data(num_parameter_blocks);
 71 |   for (int i = 0; i < num_parameter_blocks; ++i) {
 72 |     int block_size = block_sizes.at(i);
 73 |     if (manifolds.at(i) != nullptr) {
 74 |       block_size = manifolds.at(i)->TangentSize();
 75 |     }
 76 |     local_jacobians->at(i).resize(function->num_residuals(), block_size);
 77 |     local_jacobians->at(i).setZero();
 78 |     local_jacobian_data.at(i) = local_jacobians->at(i).data();
 79 |   }
 80 | 
 81 |   // Allocate Jacobian matrices in ambient space.
 82 |   jacobians->resize(num_parameter_blocks);
 83 |   std::vector<double*> jacobian_data(num_parameter_blocks);
 84 |   for (int i = 0; i < num_parameter_blocks; ++i) {
 85 |     jacobians->at(i).resize(function->num_residuals(), block_sizes.at(i));
 86 |     jacobians->at(i).setZero();
 87 |     jacobian_data.at(i) = jacobians->at(i).data();
 88 |   }
 89 | 
 90 |   // Compute residuals & jacobians.
 91 |   CHECK_NE(0, function->num_residuals());
 92 |   residuals->resize(function->num_residuals());
 93 |   residuals->setZero();
 94 |   if (!function->Evaluate(
 95 |           parameters, residuals->data(), jacobian_data.data())) {
 96 |     return false;
 97 |   }
 98 | 
 99 |   // Convert Jacobians from ambient to local space.
100 |   for (size_t i = 0; i < local_jacobians->size(); ++i) {
101 |     if (manifolds.at(i) == nullptr) {
102 |       local_jacobians->at(i) = jacobians->at(i);
103 |     } else {
104 |       int ambient_size = manifolds.at(i)->AmbientSize();
105 |       int tangent_size = manifolds.at(i)->TangentSize();
106 |       CHECK_EQ(jacobians->at(i).cols(), ambient_size);
107 |       Matrix ambient_J_tangent(ambient_size, tangent_size);
108 |       manifolds.at(i)->PlusJacobian(parameters[i], ambient_J_tangent.data());
109 |       local_jacobians->at(i).noalias() = jacobians->at(i) * ambient_J_tangent;
110 |     }
111 |   }
112 |   return true;
113 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 6 (và 5 lệnh CHECK)

START → 1
1   CHECK(residuals != nullptr)                                    đúng → 2   sai → DỪNG
2   CHECK(jacobians != nullptr)                                    đúng → 3   sai → DỪNG
3   CHECK(local_jacobians != nullptr)                              đúng → 4   sai → DỪNG
4   vòng for, điều kiện: i < num_parameter_blocks                  đúng → 5   sai → 10
5   int block_size = block_sizes.at(i)                             → 6
6   if (manifolds.at(i) != nullptr)                                đúng → 7   sai → 8
7   block_size = manifolds.at(i)->TangentSize()                    → 8
8   local_jacobians->at(i).resize(function->num_residuals(), block_size)
    local_jacobians->at(i).setZero()
    local_jacobian_data.at(i) = local_jacobians->at(i).data()      → 9
9   ++i                                                            → 4
10  jacobians->resize(num_parameter_blocks)
    int i = 0                                                      → 11
11  vòng for, điều kiện: i < num_parameter_blocks                  đúng → 12   sai → 14
12  jacobians->at(i).resize(function->num_residuals(), block_sizes.at(i))
    jacobians->at(i).setZero()
    jacobian_data.at(i) = jacobians->at(i).data()                  → 13
13  ++i                                                            → 11
14  CHECK_NE(0, function->num_residuals())                         đúng → 15   sai → DỪNG
15  residuals->resize(function->num_residuals())
    residuals->setZero()                                           → 16
16  if (!function->Evaluate(parameters, residuals->data(), jacobian_data.data()))   đúng → 17   sai → 18
17  return false                                                   → END
18  size_t i = 0                                                   → 19
19  vòng for, điều kiện: i < local_jacobians->size()               đúng → 20   sai → 26
20  if (manifolds.at(i) == nullptr)                                đúng → 21   sai → 23
21  local_jacobians->at(i) = jacobians->at(i)                      → 22
22  ++i                                                            → 19
23  int ambient_size = manifolds.at(i)->AmbientSize()
    int tangent_size = manifolds.at(i)->TangentSize()              → 24
24  CHECK_EQ(jacobians->at(i).cols(), ambient_size)                đúng → 25   sai → DỪNG
25  ambient_size, tangent_size
    manifolds.at(i)->PlusJacobian(parameters[i], ambient_J_tangent.data())
    local_jacobians->at(i).noalias() = jacobians->at(i) * ambient_J_tangent   → 22
26  return true                                                    → END
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
#include "ceres/manifold.h"
#include "ceres/gradient_checker.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/gradient_checker.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/gradient_checker.cc"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1238_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
