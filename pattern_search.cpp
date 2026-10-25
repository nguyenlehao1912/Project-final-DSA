#include "search.h"
#include <iostream>
#include <vector>

using namespace std;

//Hàm phụ trợ cho binary search, so sánh pattern với suffix tại vị trí suffixIndex trong text
int comparePattern(const string& text, int suffixIndex, const string& pattern) {
    int m = pattern.length();

    string sub = text.substr(suffixIndex, m); 
    
    if (sub == pattern) return 0;
    if (sub < pattern) return -1;
    return 1;
}
//Hàm BinarySearch để tìm tất cả các vị trí xuất hiện của pattern trong text dựa trên suffix array
vector<int> BinarySearch(const string& text, const string& pattern, const vector<int>& suffixArr) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) return positions;

    int left = 0, right = n - 1;
    int firstMatch = -1;

    //Tìm vị trí xuất hiện ĐẦU TIÊN (Lower Bound) của mẫu
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = comparePattern(text, suffixArr[mid], pattern);

        if (cmp == 0) {
            firstMatch = mid;
            right = mid - 1; 
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (firstMatch == -1) return positions; 

    //Tìm vị trí xuất hiện CUỐI CÙNG (Upper Bound) của mẫu
    left = firstMatch; 
    right = n - 1;
    int lastMatch = firstMatch;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = comparePattern(text, suffixArr[mid], pattern);

        if (cmp == 0) {
            lastMatch = mid;
            left = mid + 1; 
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Thu thập tất cả các vị trí xuất hiện của mẫu trong text
    for (int i = firstMatch; i <= lastMatch; i++) {
        positions.push_back(suffixArr[i]);
    }

    return positions;
}

//Naive Search
vector<int> naiveSearch(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    if (m == 0 || m > n) return positions;

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