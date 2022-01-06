#include "../macros.hpp"

// 素因数分解(mapベース)(旧)
map<ll, ll> factorize(ll x) {
    map<ll, ll> res;
    for (ll i=2; i*i<=x; i++) {
        while (x%i == 0) {
            x /= i;
            res[i]++;
        }
        if (x == 1) break;
    }
    if (x != 1) res[x]++;
    return res;
}
