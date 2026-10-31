#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <random>
#include <sstream>
#include "suffix_array.h"
#include "pattern_search.h"
using namespace std;
using Clock = chrono::steady_clock;

double msSince(Clock::time_point t0) {
    return chrono::duration<double, milli>(Clock::now() - t0).count();
}

void bench(const string& full, int n, int Q) {
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
    auto t0 = Clock::now();
    vector<int> sa = buildSuffixArray(s);
    double B = msSince(t0);
    size_t sink = 0;

    t0 = Clock::now();
    for (auto& q : qs) sink += BinarySearch(s, q, sa).size();
    double S = msSince(t0) / Q;

    t0 = Clock::now();
    for (auto& q : qs) sink += naiveSearch(s, q).size();
    double N = msSince(t0) / Q;

    int bad = 0;
    for (auto& q : qs) {
        auto a = BinarySearch(s, q, sa), b = naiveSearch(s, q);
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if (a != b) bad++;
    }
    printf("%d,%.3f,%.6f,%.6f,%.1f,%s\n", n, B, S, N,
           N > S ? B / (N - S) : -1.0, bad ? "MISMATCH" : "OK");
}

int main(int argc, char** argv) {
    ifstream f(argc > 1 ? argv[1] : "big_text.txt", ios::binary);
    stringstream ss; ss << f.rdbuf();
    string s = ss.str();
    if (s.empty()) { printf("Khong doc duoc file\n"); return 1; }
    printf("n,B_ms,S_ms,N_ms,crossover_q,check\n");
    for (int n : {1000, 10000, 50000}) if (n < (int)s.size()) bench(s, n, 200);
    bench(s, s.size(), 200);
}