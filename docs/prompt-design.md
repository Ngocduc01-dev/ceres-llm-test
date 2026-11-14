# Thiết kế prompt chung (CFT – C2)

Prompt: [`prompts/master_prompt.md`](../prompts/master_prompt.md). Tài liệu này giải thích **bố cục** và **vì sao**.

## 1. Bố cục 7 mục

| # | Mục | Nội dung | Ứng với yêu cầu của nhóm |
|---|---|---|---|
| 1 | Nhiệm vụ | LLM làm gì, cho dự án nào; không có kết quả đúng để so (không có EO) | "Trình bày prompt" |
| 2 | Khái niệm cần dùng | Giải thích ngắn: CFG, điểm rẽ nhánh, **C2 + công thức**, test path, điều kiện đường đi, nhánh không thể đi tới, vòng lặp (có giới hạn / không), `CHECK` | "Giải thích khái niệm", "độ đo là gì" |
| 3 | Đầu vào | 3.1 thông tin + mã nguồn của unit · 3.2 **CFG dựng sẵn** (hoặc yêu cầu tự dựng) + cách đọc · 3.3 cách gọi unit (`#include`, lưu ý private/static/template) | "Đưa CFG hoặc yêu cầu tạo CFG" |
| 4 | Yêu cầu đối với bộ test | Mỗi test phải thoả gì để đạt C2; chọn đầu vào ngẫu nhiên trong khoảng hợp lệ | "Tiêu chí cho mỗi test case để đạt C2" |
| 5 | Các bước thực hiện | Đọc → liệt kê nhánh → chọn test path → khoảng giá trị → viết code → kiểm tra | "Từng bước thực hiện" |
| 6 | Kết quả cần trả về | A. test paths · B. test case · C. nhánh không test + C2 dự kiến · D. 1 file GoogleTest | "Kết quả cần có" |
| 7 | Lưu ý | Không bịa hàm, không sửa Ceres, code đầy đủ | (chống ảo giác) |

**Vì sao "Khái niệm" (2) đứng trước:** các mục sau dùng các từ của mục 2 (node, nhánh đúng/sai, C2…). Giải thích trước thì LLM hiểu yêu cầu đúng một nghĩa. Phần lớn các nhóm trong lớp cũng sắp xếp như vậy.

**Vì sao "Yêu cầu" (4) đứng trước "Các bước" (5):** 4 nói *đích đến* (bộ test phải thoả gì), 5 nói *cách đi*; bước cuối LLM tự đối chiếu với đích.

**Vì sao kết quả không có bảng CFG:** CFG đã dựng sẵn ở mục 3.2 (bằng Clang) và lưu ở `units/<id>/cfg.txt` – không cần LLM chép lại. LLM chỉ trả về phần cần cho CFT: **test paths**, **test case**, nhánh không test, và **file code**. Câu trả lời ngắn hơn, ít chỗ sai hơn.

**Vì sao chỉ đưa ngữ cảnh của chính unit:** mã nguồn, CFG và cách gọi unit là đủ để thiết kế test path. Bỏ phần ngữ cảnh tham khảo (khai báo class, các hàm được gọi, test mẫu…) giúp prompt ngắn còn ~1/3 (trung vị ~7.9 KB thay vì ~19 KB).
> Rủi ro cần theo dõi khi chạy thử: thiếu khai báo class, LLM có thể không biết cách tạo object (constructor nào, tham số gì) → lỗi compile. Nếu tỉ lệ lỗi cao, cân nhắc thêm lại riêng phần constructor của class.

**Viết đơn giản:** tránh từ chuyên ngành hẹp; mỗi khái niệm giải thích 1–2 câu; không đưa ví dụ code khó hiểu vào phần yêu cầu.

## 2. Học được gì từ prompt của các nhóm khác (discussion "UPLOAD PROMPTS")

Đã đọc prompt của các nhóm 1, 3, 4, 5, 6, 11. Những điểm chung, đã đưa vào prompt của nhóm:
- **Vai trò → khái niệm → yêu cầu theo bước → định dạng đầu ra bắt buộc** (bảng có cột cố định).
- Test path viết dạng dãy node có ghi nhánh; **điều kiện đường đi → khoảng giá trị → chọn giá trị ngẫu nhiên trong khoảng**.
- Ghi rõ **nhánh không thể đi tới** và vẫn tính vào tổng số nhánh.
- Không tuyên bố đã chạy / đã đạt độ phủ nếu chưa đo thật (ghi "dự kiến").

Khác với các nhóm khác (bài của nhóm là project ~100k dòng, không có đặc tả):
- **Không có EO**: không có cột kết quả mong đợi, không kiểm tra kết quả trả về.
- **CFG do tool dựng sẵn** thay vì để LLM vẽ.
- **Đầu ra phải là file GoogleTest compile được**, không chỉ bảng test case.
- Thêm lưu ý riêng cho Ceres: `CHECK` của glog, cách gọi hàm `static`/`private`, template.

## 3. Ý kiến của thầy trong discussion (cần bám theo)

- "Đây là bài tập về nhà, các em cứ tìm mọi cách để AI xử lý được. Nhớ là ta chỉ làm Unit testing." → được phép tiền xử lý (AST, CFG) trước khi đưa vào prompt; test phải là **unit test**.
- "Không có Unit nào lớn đến mức AI không xử lý hết." → **1 prompt xử lý trọn 1 unit**, không chia nhỏ theo từng path.

## 4. Cách dùng

1. `scripts/build_cfg.py` dựng CFG → `units/<id>/cfg.txt` (Phase 4).
2. `scripts/render_prompt.py` điền các chỗ `{{...}}`: thông tin unit (`units/<id>/info.json`), mã nguồn đánh số dòng, CFG, `#include` (từ context Phase 3), cách gọi unit → `units/<id>/prompt.md`.
3. `scripts/generate.mjs` gửi prompt cho Claude Sonnet 5.5 (effort low) qua Claude Code CLI, lưu nguyên văn câu trả lời `units/<id>/response.md`, tách khối code có dòng `// FILE:` → `units/<id>/<id>_test.cc`.
4. Phase 6 compile, chạy, đo độ phủ thật bằng gcov → so với C2 dự kiến (mục C của câu trả lời).

## 5. Đã chốt

- **1 prompt = 1 unit** (1 hàm / 1 method) → 1540 prompt, chạy bằng script.
- **CFG do tool dựng** (Clang), node đánh số 1, 2, 3… riêng cho từng unit theo thứ tự chạy; `START`, `END`, `DỪNG`. LLM dùng đúng số node này. Unit không có CFG (49) → prompt yêu cầu tự dựng.
- **Vòng lặp:** có giới hạn (0, 1, 2, ở giữa, n−1, n, n+1) / không có giới hạn (0, 1, 2 + mỗi cách thoát).
- **Lưu trữ:** mỗi unit 1 thư mục `units/<id>/`: `info.json`, `source.cc` (mã nguồn unit, để xem), `cfg.txt`, `prompt.md`, `response.md`, `<id>_test.cc`.
- **Tiếp theo:** chạy thử 20 unit smoke test; xem LLM có dùng đúng số node, test có compile được không, so C2 dự kiến với C2 đo bằng gcov.
