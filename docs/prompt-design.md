# Thiết kế prompt chung (CFT – C2)

Prompt: [`prompts/master_prompt.md`](../prompts/master_prompt.md). Tài liệu này giải thích **bố cục** và **vì sao**.

## 1. Bố cục 7 mục

| # | Mục | Trả lời câu hỏi | Ứng với yêu cầu của nhóm |
|---|---|---|---|
| 1 | Vai trò và mục tiêu | LLM là ai, làm gì, cho dự án nào, không có EO | "Trình bày prompt" |
| 2 | Khái niệm và quy ước | CFG, điểm quyết định, **C2 là gì + công thức**, vòng lặp, test path, path condition, nhánh bất khả thi, CHECK | "Giải thích khái niệm", "độ đo là gì" |
| 3 | Đầu vào | Code (đánh số dòng), **CFG dựng sẵn hoặc yêu cầu tự dựng**, context Phase 3 | "Đưa CFG hoặc yêu cầu tạo CFG" |
| 4 | Yêu cầu đối với bộ test | Mỗi test case phải thoả gì để đạt C2; input chọn thế nào | "Tiêu chí cho mỗi test case để đạt C2" |
| 5 | Các bước thực hiện | 7 bước: đọc → CFG → liệt kê nhánh → chọn path → giải điều kiện → viết code → tự kiểm tra | "Từng bước thực hiện" |
| 6 | Kết quả cần trả về | Bảng CFG, nhánh, path, test case, độ phủ dự kiến + 1 file GoogleTest | "Kết quả cần có" |
| 7 | Ràng buộc | Không bịa API, không EO, không tuyên bố độ phủ chưa đo | (chống ảo giác) |

**Vì sao "Khái niệm" (2) đứng trước "Đầu vào" (3) và "Yêu cầu" (4):** các mục sau đều dùng thuật ngữ của mục 2 (node, nhánh T/F, mẫu số C2…). Định nghĩa trước thì LLM hiểu yêu cầu đúng một nghĩa; đây cũng là cách phần lớn các nhóm trong lớp sắp xếp (quy ước → yêu cầu → định dạng đầu ra).

**Vì sao "Yêu cầu" (4) đứng trước "Các bước" (5):** 4 nói *đích đến* (bộ test phải thoả gì), 5 nói *cách đi*. Đặt đích trước giúp LLM tự kiểm tra ở bước 7.

**Vì sao "Kết quả" (6) có bảng trước, code sau:** bắt LLM phân tích (CFG → nhánh → path → input) trước khi viết code; các bảng cũng chính là bằng chứng CFT để đưa vào báo cáo. File code đặt cuối, có dòng `// FILE:` để script tách tự động.

## 2. Học được gì từ prompt của các nhóm khác (discussion "UPLOAD PROMPTS")

Đã đọc prompt của các nhóm 1, 3, 4, 5, 6, 11. Những điểm chung, đã đưa vào prompt của nhóm:
- **Vai trò → quy ước/khái niệm → yêu cầu theo bước → định dạng đầu ra bắt buộc** (bảng Markdown có cột cố định).
- CFG trình bày bằng **bảng node + bảng cạnh + sơ đồ Mermaid**, kèm **V(G)** tính bằng 2 công thức để đối chiếu.
- Test path viết dạng dãy node có nhãn nhánh; **giải điều kiện đường đi → miền giá trị → chọn giá trị ngẫu nhiên trong miền**.
- Ghi rõ **nhánh/đường bất khả thi** và không loại khỏi mẫu số.
- Không tuyên bố đã chạy / đã đạt độ phủ nếu chưa đo thật (trạng thái "Not Run").
- Tách prompt thành phần chung + phần riêng cho từng kỹ thuật (nhóm 11) → prompt của nhóm cũng tách phần chung (mục 1, 2, 7) và phần điền theo unit (mục 3).

Khác với các nhóm khác (do bài của nhóm là project ~100k dòng, không có đặc tả):
- **Không có EO**: bỏ cột Expected Output, không viết assertion so sánh kết quả.
- **Đầu vào là context tự động** (Phase 3) thay vì đặc tả do người dán vào.
- **Đầu ra phải là file GoogleTest compile được**, không chỉ bảng test case.
- Thêm quy ước riêng cho Ceres: `CHECK` của glog, cách gọi hàm `static`/`private`, template.

## 3. Ý kiến của thầy trong discussion (cần bám theo)

- "Đây là bài tập về nhà, các em cứ tìm mọi cách để AI xử lý được. Nhớ là ta chỉ làm Unit testing." → được phép tiền xử lý (AST, CFG, context) trước khi đưa vào prompt; test phải là **unit test**.
- "Không có Unit nào lớn đến mức AI không xử lý hết." → **không cần chia nhỏ 1 unit** thành nhiều prompt theo từng path; 1 prompt xử lý trọn 1 unit (hoặc vài unit cùng class).

## 4. Cách dùng

1. `render_prompt.py` điền các chỗ `{{...}}` từ context Phase 3 (`data/context/<id>.txt`) và CFG (`units/<id>/cfg.txt`) → `units/<id>/prompt.md`.
2. Gửi prompt cho Claude Sonnet 5.5 (effort low) qua Claude Code CLI (`claude -p`), lưu nguyên văn câu trả lời vào `units/<id>/response.md` (bảng nhánh, test path, test case – dùng cho báo cáo).
3. Script tách khối code có dòng `// FILE: ...` → `units/<id>/<id>_test.cc`.
4. Phase 6 compile, chạy, đo độ phủ thật bằng gcov → so với C2 dự kiến ở bảng A5.

## 5. Đã chốt

- **1 prompt = 1 unit** (1 hàm / 1 method) → 1540 prompt, chạy bằng script.
- **CFG do tool dựng:** Clang Static Analyzer (`debug.DumpCFG`), script lọc nhiễu và gắn số dòng (`@L<số>`). Prompt mục 3 có đoạn **"Cách đọc CFG"**; LLM chuẩn hoá CFG (gộp `&&`/`||`, gộp khối `CHECK`, đổi tên node theo số dòng) ở bảng A1. Unit nào Clang không dựng được → prompt tự chuyển sang "LLM tự dựng CFG".
- **Vòng lặp:** 2 loại – có cận (0, 1, 2, m, n−1, n, n+1) / không có cận (0, 1, 2 + mỗi lối thoát); cận là biến → chọn ngẫu nhiên.
- **Lưu trữ:** mỗi unit 1 thư mục `units/<id>/` gồm `prompt.md`, `cfg.txt`, `response.md`, `<id>_test.cc`.
- **Tiếp theo:** chạy thử 20 unit smoke test, so bảng A1 của LLM với source và so C2 dự kiến (A5) với C2 đo bằng gcov để chỉnh prompt.
