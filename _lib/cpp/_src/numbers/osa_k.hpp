#include "../macros.hpp"

// 高速素因数分解(osa_k法)、前計算
vector<ll> eratosthenes_sieve(ll n) {
    vector<ll> table(n+1);
    table[1] = 1;
    rep(i, 2, n+1) {
        if (table[i] == 0) {
            for (ll j=i; j<=n; j+=i) {
                table[j] = i;
            }
        }
    }
    return table;
}

// 高速素因数分解(osa_k法)(vectorベース)
vector<pair<ll, int>> factorize(const vector<ll> &minfactor, ll x) {
    vector<pair<ll, int>> res;
    while (x > 1) {
        int p = minfactor[x];
        int cnt = 0;
        while (minfactor[x] == p) {
            x /= p;
            cnt++;
        }
        res.pb({p, cnt});
    }
    return res;
}

// 高速素因数分解(osa_k法)(mapベース)
// map<ll, ll> factorize(const vector<ll> &table, ll x) {
//     map<ll, ll> res;
//     while (x != table[x]) {
//         res[table[x]]++;
//         x /= table[x];
//     }
//     if (x != 1) {
//         res[x]++;
//     }
//     return res;
// }
