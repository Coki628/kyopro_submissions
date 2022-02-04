#include "macros.hpp"

// 区間[l,r)内の各素因数の個数(エラトステネスの区間篩) 
map<ll, ll> segment_sieve(ll l, ll r) {

    int MAX = int(sqrt(r));
    vector<bool> is_prime(MAX+1, true);
    map<ll, ll> C;
    vector<ll> A(r-l);
    iota(ALL(A), l);

    rep(i, 2, MAX+1) {
        ll cnt = 0;
        if (is_prime[i]) {
            rep(j, i*2, MAX+1, i) {
                is_prime[j] = false;
            }
            // 素数が見つかったら、区間内にあるその倍数について素因数分解していく
            rep(j, max(2LL, (l+i-1)/i)*i, r, i) {
                while (A[j-l] % i == 0) {
                    A[j-l] /= i;
                    cnt++;
                }
            }
            C[i] += cnt;
        }
    }
    // 自身が素数であればその分を足す
    rep(i, r-l) {
        if (A[i] > 1) {
            C[A[i]]++;
        }
    }
    return C;
}
