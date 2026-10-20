#include <iostream>
using namespace std;

template <typename Less>
void mergeSort(int a[], int buf[], int l, int r, Less less){
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

int* buildSuffixArray(const char* s, int n){
    if(n == 0) return new int[0];
    int* sa  = new int[n];
    int* rnk = new int[n];
    int* tmp = new int[n];
    int* buf = new int[n];
    for(int i = 0; i < n; i++){
        sa[i]  = i;
        rnk[i] = (unsigned char)s[i];
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
    delete[] rnk; delete[] tmp; delete[] buf;
    return sa;
}

int cmpSuffix(const char* s, int n, int i, const char* p, int m){
    int j = 0;
    while(j < m && i + j < n){
        if (s[i + j] != p[j]) return s[i + j] < p[j] ? -1 : 1;
        j++;
    }
    return (j == m) ? 0 : -1;
}

int searchPattern(const char* s, int n, int sa[], const char* p, int res[]){
    int m = length(p);
    if(m == 0) return 0; 
    int lo = 0, hi = n;
    while(lo < hi){
        int mid = (lo + hi) / 2;
        if(cmpSuffix(s, n, sa[mid], p, m) < 0) lo = mid + 1;
        else hi = mid;
    }
    int left = lo;
    hi = n;
    while(lo < hi){
        int mid = (lo + hi) / 2;
        if (cmpSuffix(s, n, sa[mid], p, m) <= 0) lo = mid + 1;
        else hi = mid;
    }
    int right = lo;
    int cnt = right - left;
    for(int i = 0; i < cnt; i++) res[i] = sa[left + i];
    if(cnt > 1){
        int* buf = new int[cnt];
        mergeSort(res, buf, 0, cnt - 1, [](int x, int y) { return x < y; });
        delete[] buf;
    }
    return cnt;
}

int naiveSearch(const char* s, int n, const char* p, int res[]){
    int m = length(p), cnt = 0;
    for(int i = 0; i + m <= n; i++){
        int j = 0;
        while(j < m && s[i + j] == p[j]) j++;
        if(j == m) res[cnt++] = i;
    }
    return cnt;
}

int main(){
    const char* s = "banana";
    int n = length(s);
    int* sa = buildSuffixArray(s, n);
    cout << "SA: ";
    for(int i = 0; i < n; i++) cout << sa[i] << " ";
    cout << "\n";
    int* res = new int[n];
    int c1 = searchPattern(s, n, sa, "ana", res);
    cout << "SA search:    ";
    for(int i = 0; i < c1; i++) cout << res[i] << " ";
    cout << "\n";
    int c2 = naiveSearch(s, n, "ana", res);
    cout << "Naive search: ";
    for(int i = 0; i < c2; i++) cout << res[i] << " ";
    cout << "\n";
    delete[] sa; delete[] res;
}
