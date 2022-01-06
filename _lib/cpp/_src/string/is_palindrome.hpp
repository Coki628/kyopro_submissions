#include "../macros.hpp"

// 回文判定
bool is_palindrome(const string &S) {
    ll N = S.size();
    rep(i, N/2) {
        ll j = N-i-1;
        if (S[i] != S[j]) {
            return false;
        }
    }
    return true;
}
