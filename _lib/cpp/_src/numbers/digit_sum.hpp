#include "../macros.hpp"
#include "../common/toint.hpp"

// 桁和：O(logN)
ll digit_sum(ll n) {
    ll res = 0;
    while (n > 0) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

// 桁和：O(|S|)(未verify)
ll digit_sum(string S) {
    ll res = 0;
    rep(i, S.size()) {
        res += toint(S[i]);
    }
    return res;
}
