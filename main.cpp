#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono> // Thư viện bắt buộc để đo thời gian

// Nhúng các file header 
#include "suffix_array.h"
#include "pattern_search.h"

using namespace std;
using namespace std::chrono;

// ==========================================
// HÀM 1: CHẠY TEST NHỎ (Kiểm tra tính đúng đắn)
// ==========================================
void runSmallTest() {
    cout << "\n--- 1. CHAY SMALL TEST (Kiem tra dung sai) ---" << endl;
    string text = "banana";
    cout << "Text: " << text << endl;

    vector<int> sa = buildSuffixArray(text);
    cout << "Suffix Array: ";
    for (int idx : sa) cout << idx << " ";
    cout << endl;

    string pattern = "ana";
    cout << "Tim pattern '" << pattern << "' bang Binary Search: ";
    vector<int> pos1 = BinarySearch(text, pattern, sa);
    for (int p : pos1) cout << p << " ";
    cout << endl;

    cout << "Tim pattern '" << pattern << "' bang Naive Search: ";
    vector<int> pos2 = naiveSearch(text, pattern);
    for (int p : pos2) cout << p << " ";
    cout << endl;
}

// ==========================================
// HÀM 2: CHẠY BENCHMARK (Đo hiệu năng và Crossover point)
// ==========================================
void runBenchmark() {
    cout << "\n--- 2. CHAY BENCHMARK (So sanh hieu nang) ---" << endl;
    
    // GHI CHÚ: Bạn cần tự tạo file large_text.txt (nội dung dài) 
    // và queries.txt (chứa nhiều pattern, mỗi pattern 1 dòng) trong thư mục data/
    ifstream textFile("data/large_text.txt");
    ifstream queryFile("data/queries.txt");

    if (!textFile.is_open() || !queryFile.is_open()) {
        cout << "[Canh bao] Khong tim thay file data/large_text.txt hoac data/queries.txt!" << endl;
        cout << "Vui long tao file de chay tinh nang Benchmark." << endl;
        return;
    }

    // Đọc text lớn
    string text((istreambuf_iterator<char>(textFile)), istreambuf_iterator<char>());
    textFile.close();
    
    // Đọc danh sách 100+ truy vấn
    vector<string> queries;
    string q;
    while (queryFile >> q) {
        queries.push_back(q);
    }
    queryFile.close();

    cout << "Do dai van ban: " << text.length() << " ky tu." << endl;
    cout << "So luong truy van: " << queries.size() << " mau." << endl;

    // ----- ĐO THỜI GIAN SUFFIX ARRAY -----
    auto startSA = high_resolution_clock::now();
    
    // Tiền xử lý (Build SA)
    vector<int> sa = buildSuffixArray(text);
    
    // Tìm kiếm
    int totalMatchesSA = 0;
    for (const string& pattern : queries) {
        totalMatchesSA += BinarySearch(text, pattern, sa).size();
    }
    
    auto endSA = high_resolution_clock::now();
    auto durationSA = duration_cast<milliseconds>(endSA - startSA).count();

    // ----- ĐO THỜI GIAN NAIVE SEARCH -----
    auto startNaive = high_resolution_clock::now();
    
    int totalMatchesNaive = 0;
    for (const string& pattern : queries) {
        totalMatchesNaive += naiveSearch(text, pattern).size();
    }
    
    auto endNaive = high_resolution_clock::now();
    auto durationNaive = duration_cast<milliseconds>(endNaive - startNaive).count();

    // ----- IN KẾT QUẢ -----
    cout << "\n[KET QUA BENCHMARK]" << endl;
    cout << "Suffix Array (Tien xu ly + Tim " << queries.size() << " lan): " << durationSA << " ms" << endl;
    cout << "Naive Search (Tim " << queries.size() << " lan): " << durationNaive << " ms" << endl;
    
    if (durationSA < durationNaive) {
        cout << "=> Suffix Array NHANH HON! Day la minh chung cho viec tien xu ly (O(n log^2 n)) rat xung dang khi co nhieu truy van." << endl;
    } else {
        cout << "=> Naive Search dang nhanh hon. Can tang so luong truy van (queries) len nua de thay Crossover point." << endl;
    }
}

int main() {
    cout << "=========================================" << endl;
    cout << " DSA Project: Suffix Array Pattern Search" << endl;
    cout << "=========================================" << endl;

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Chay Small Test (Kiem tra dung sai)" << endl;
        cout << "2. Chay Benchmark (Kiem tra toc do & Crossover point)" << endl;
        cout << "0. Thoat" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        if (choice == 1) {
            runSmallTest();
        } else if (choice == 2) {
            runBenchmark();
        }
    } while (choice != 0);

    return 0;
}