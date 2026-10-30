#include <iostream>
#include <vector>
#include <string>
#include "suffix_array.h"
#include "pattern_search.h"
using namespace std;

template <typename Less>
void mergeSort(vector<int>& a, vector<int>& buf, int l, int r, Less less){
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(a, buf, l, mid, less);
    mergeSort(a, buf, mid + 1, r, less);
    int i = l, j = mid + 1, t = l;
    while(i <= mid && j <= r){
        if(less(a[j], a[i])) buf[t++] = a[j++];
        else buf[t++] = a[i++];
    }
    while(i <= mid) buf[t++] = a[i++];
    while(j <= r) buf[t++] = a[j++];
    for(int x = l; x <= r; x++) a[x] = buf[x];
}

int length(const char* s){
    int n = 0;
    while(s[n] != '\0') n++;
    return n;
}

vector<int> buildSuffixArray(const string& text) {
    int n = text.size();
    vector<int> sa(n), rnk(n), tmp(n), buf(n);
    for(int i = 0; i < n; i++){
        sa[i]  = i;
        rnk[i] = (unsigned char)text[i];
    }
    for(int k = 1; ; k <<= 1){
        auto less = [&](int a, int b) {
            if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
            int ra = (a + k < n) ? rnk[a + k] : -1;
            int rb = (b + k < n) ? rnk[b + k] : -1;
            return ra < rb;
        };
        mergeSort(sa, buf, 0, n - 1, less);
        tmp[sa[0]] = 0;
        for(int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (less(sa[i - 1], sa[i]) ? 1 : 0);
        for(int i = 0; i < n; i++) rnk[i] = tmp[i];
        if(rnk[sa[n - 1]] == n - 1) break;
    }
    return sa;
}
