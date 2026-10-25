#include "search.h"
#include <iostream>

using namespace std;

// Hàm phụ trợ: So sánh chuỗi mẫu (pattern) với hậu tố tại một vị trí cụ thể
// Trả về: 0 nếu khớp, -1 nếu text < pattern, 1 nếu text > pattern
int comparePattern(const string& text, int suffixIndex, const string& pattern) {
    int m = pattern.length();
    // Trích xuất tiền tố của hậu tố có độ dài bằng với pattern
    string sub = text.substr(suffixIndex, m); 
    
    if (sub == pattern) return 0;
    if (sub < pattern) return -1;
    return 1;
}

// ---------------------------------------------------------
// YÊU CẦU 2: Cài đặt Binary Search trên Suffix Array
// Độ phức tạp: O(m * log n)
// ---------------------------------------------------------
vector<int> searchPattern(const string& text, const string& pattern, const vector<int>& suffixArr) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) return positions;

    int left = 0, right = n - 1;
    int firstMatch = -1;

    // BƯỚC 1: Tìm vị trí xuất hiện ĐẦU TIÊN (Lower Bound) của mẫu
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = comparePattern(text, suffixArr[mid], pattern);

        if (cmp == 0) {
            firstMatch = mid;
            right = mid - 1; // Tiếp tục ép giới hạn tìm kiếm về phía bên trái
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Nếu không tìm thấy bất kỳ kết quả nào
    if (firstMatch == -1) return positions; 

    // BƯỚC 2: Tìm vị trí xuất hiện CUỐI CÙNG (Upper Bound) của mẫu
    left = firstMatch; 
    right = n - 1;
    int lastMatch = firstMatch;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = comparePattern(text, suffixArr[mid], pattern);

        if (cmp == 0) {
            lastMatch = mid;
            left = mid + 1; // Tiếp tục ép giới hạn tìm kiếm về phía bên phải
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // BƯỚC 3: Thu thập tất cả các vị trí thực tế trong văn bản gốc
    for (int i = firstMatch; i <= lastMatch; i++) {
        positions.push_back(suffixArr[i]);
    }

    return positions;
}

// ---------------------------------------------------------
// YÊU CẦU BỔ SUNG: Cài đặt Naive Search để phục vụ Benchmark
// Độ phức tạp: O(n * m)
// ---------------------------------------------------------
vector<int> naiveSearch(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) return positions;

    // Quét toàn bộ văn bản từ trái sang phải
    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            positions.push_back(i);
        }
    }
    return positions;
}