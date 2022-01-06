#include "../macros.hpp"

// 素数列挙(エラトステネスの篩)(旧)
vector<bool> eratosthenes_sieve(ll n) {
    vector<bool> table(n+1), primes(n+1);
    rep(i, 2, n+1) {
        if (!table[i]) {
            primes[i] = true;
            for (ll j=i+i; j<=n; j+=i) {
                table[j] = true;
            }
        }
    }
    return primes;
}
