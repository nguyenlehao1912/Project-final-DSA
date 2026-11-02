#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono> 
#include <algorithm>
#include <random>
#include <sstream>
#include <cstdio>
// Nhúng các file header 
#include "suffix_array.h"
#include "pattern_search.h"

using namespace std;
using namespace std::chrono;
using Clock = chrono::steady_clock;

double msSince(Clock::time_point t0) {
    return chrono::duration<double, milli>(Clock::now() - t0).count();
}
double median(vector<double> v) {
    sort(v.begin(), v.end());
    return v[v.size() / 2];
}
void bench(const string& full, int n, int Q) {
    if (n < 25) return; // tranhs n - m + 1 <= 0
    string s = full.substr(0, n);
    mt19937 rng(42);
    vector<string> qs;
    for (int i = 0; i < Q; i++) {
        int m = 5 + rng() % 16;
        string q;
        if (i % 10 == 9) for (int j = 0; j < m; j++) q += char('a' + rng() % 26);
        else q = s.substr(rng() % (n - m + 1), m);
        qs.push_back(q);
    }
    const int REP = 7;
    size_t sink = 0;
    vector<double> vB, vS, vN;

    vector<int> sa = buildSuffixArray(s);
    for(auto &q : qs) sink += BinarySearch(s, q, sa).size();
    for(auto &q : qs) sink += naiveSearch(s, q).size();
    for (int rep = 0; rep < REP; rep++) {
        auto t0 = Clock::now();
        sa = buildSuffixArray(s);
        vB.push_back(msSince(t0));

        t0 = Clock::now();
        for (auto& q : qs) sink += BinarySearch(s, q, sa).size();
        vS.push_back(msSince(t0)/Q);

        t0 = Clock::now();
        for (auto& q : qs) sink += BinarySearch(s, q, sa).size();
        vN.push_back(msSince(t0)/Q);
    }
    double B = median(vB), S = median(vS), N = median(vN);
    int bad = 0;
    for (auto& q : qs) {
        auto a = BinarySearch(s, q, sa), b = naiveSearch(s, q);
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if (a != b) bad++;
    }
    printf("%d,%.3f,%.6f,%.6f,%.1f,%s\n", n, B, S, N, N > S ? B / (N - S) : -1.0, bad ? "MISMATCH" : "OK");
    fprintf(stderr, "sink=%zu\n", sink);
}
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
void runAutomatedBenchmark() {
    cout << "\n--- 2. CHAY BENCHMARK (Sinh du lieu & tinh Crossover) ---\n" << endl;
    
    ifstream f("large_text.txt", ios::binary);
    if (!f.is_open()) {
        cout << "[Loi] Khong doc duoc file large_text.txt" << endl;
        return;
    }
    
    stringstream ss; 
    ss << f.rdbuf();
    string s = ss.str();
    
    if (s.empty()) { 
        cout << "[Loi] File van ban rong!" << endl; 
        return; 
    }
    
    // In Header của bảng CSV
    printf("n,B_ms,S_ms,N_ms,crossover_q,check\n");
    
    // Chạy vòng lặp test với các kích thước văn bản tăng dần
    for (int n : {1000, 10000, 50000}) {
        if (n < (int)s.size()) bench(s, n, 2000);
    }
    // Chạy test với toàn bộ độ dài văn bản
    bench(s, s.size(), 2000);
    cout << "\n[Hoan tat Benchmark. Ban co the copy du lieu tren vao Excel de ve bieu do.]" << endl;
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
            runAutomatedBenchmark();
        }
    } while (choice != 0);

    return 0;
}