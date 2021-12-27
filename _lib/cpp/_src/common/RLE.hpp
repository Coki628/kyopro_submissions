#include "../macros.hpp"

// ランレングス圧縮
template<typename T>
vector<pair<T, int>> RLE(const vector<T> &A) {
    if (A.empty()) return {};
    int N = A.size();
    vector<pair<T, int>> res;
    T cur = A[0];
    int cnt = 1;
    rep(i, 1, N) {
        if (A[i] == A[i-1]) {
            cnt++;
        } else {
            res.pb({cur, cnt});
            cnt = 1;
            cur = A[i];
        }
    }
    res.pb({cur, cnt});
    return res;
}

// ランレングス圧縮(文字列)
vector<pair<char, int>> RLE(const string &S) {
    if (S.empty()) return {};
    int N = S.size();
    vector<pair<char, int>> res;
    char cur = S[0];
    int cnt = 1;
    rep(i, 1, N) {
        if (S[i] == S[i-1]) {
            cnt++;
        } else {
            res.pb({cur, cnt});
            cnt = 1;
            cur = S[i];
        }
    }
    res.pb({cur, cnt});
    return res;
}
