# Nhật ký sử dụng AI (AI Usage Log)
## Tuần 1
| Ngày | Lời nhắc (Prompt/Question) | Công cụ AI | Cách nhóm áp dụng vào dự án |
| :--- | :--- | :--- | :--- |
| 10/10/2026 | "Bạn hãy xác định những yêu cầu cần đạt và gợi ý cấu trúc cho dự án Suffix Array cho nhóm 2 người." | Gemini 3.1 Pro | Lấy ý tưởng cấu trúc thư mục chuẩn (src, data, docs), khung file C++ ban đầu và gợi ý phân công nhiệm vụ cho 2 thành viên. |
| 11/10/2026 | "Giảng viên yêu cầu bổ sung algorithm choice + timeline trước khi duyệt. Gợi ý giúp tôi." | Gemini 3.1 Pro | Quyết định chọn thuật toán Prefix Doubling để xây dựng Suffix Array đạt $O(n \log^2 n)$ và Binary Search. Tham khảo khung thời gian 4 tuần để báo cáo giảng viên. |
| 12/10/2026 | "file pattern_search và suffix array để làm gì" | Gemini 3.1 Pro| Hiểu rõ chức năng phân tách file: `suffix_array.cpp` dùng cho tiền xử lý, còn `search.cpp` dùng để xử lý các truy vấn tìm kiếm. |
| 14/10/2026 | "Tôi chưa hiểu link blob/commit cụ thể thể hiện công việc đã làm là gì." | Gemini 3.1 Pro | Phân biệt được link thư mục gốc (repo root) và link trỏ đến từng file (blob/commit) để nộp lại link báo cáo công việc cho đúng. |
----------------------
## Tuần 2
# Nhật ký sử dụng AI (AI Usage Log)

| Ngày | Lời nhắc (Prompt/Question) | Công cụ AI | Cách nhóm áp dụng vào dự án |
| :--- | :--- | :--- | :--- |
| 14/10/2026 | "Bạn hãy xác định những yêu cầu cần đạt và gợi ý cấu trúc cho dự án Suffix Array cho nhóm 2 người." | Gemini 3.1 Pro | Lấy ý tưởng cấu trúc thư mục chuẩn (src, data, docs), khung file C++ boilerplate và chia đầu việc cho 2 thành viên. |
| 14/10/2026 | "Giảng viên yêu cầu bổ sung algorithm choice + timeline trước khi duyệt. Gợi ý giúp tôi." | Gemini 3.1 Pro | Quyết định chọn thuật toán Prefix Doubling ($O(n \log^2 n)$) và Binary Search. Tham khảo khung thời gian 4 tuần để cập nhật plan với GVHD. |
| 14/10/2026 | "file pattern_search và suffix array để làm gì" | Gemini | Hiểu rõ chức năng phân tách module: `suffix_array.cpp` chuyên xử lý tiền kỳ (preprocessing), còn `search.cpp` chuyên xử lý truy vấn tìm kiếm. |
| 14/10/2026 | "Tôi chưa hiểu link blob/commit cụ thể thể hiện công việc đã làm là gì." | Gemini 3.1 Pro | Phân biệt được link repo root với link blob/commit. Áp dụng để lấy đúng đường dẫn file cụ thể trên GitHub nhằm khắc phục lỗi nộp báo cáo. |
| 25/10/2026 | "bây giờ tới tôi làm pattern_search", "hàm comparePattern để làm gì", "ví dụ mẫu" | Gemini 3.1 Pro | Nắm được logic của hàm so sánh tiền tố (comparePattern) để điều hướng không gian tìm kiếm trong Binary Search. Tham khảo ví dụ trace tay để hiểu luồng chạy. |
| 25/10/2026 | "Vậy 2 file đó làm sao để kết hợp đưa vào file main.cpp", "tại sao các biến phải có dấu &" | Gemini 3.1 Pro | Tạo các file header (`.h`) để liên kết các hàm từ nhiều file `.cpp` khác nhau vào `main.cpp`. Ứng dụng kỹ thuật truyền tham chiếu (`&`) kết hợp `const` để tối ưu hóa hiệu năng, tránh sao chép dữ liệu khi benchmark mảng lớn. |