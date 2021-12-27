#include "../macros.hpp"

ll pow(ll x, ll n) {
    ll res = 1;
    rep(_, n) res *= x;
    return res;
}

ll pow(int x, ll n) { return pow((ll)x, n); }

ll pow(ll x, int n) { return pow(x, (ll)n); }

ll pow(int x, int n) { return pow((ll)x, (ll)n); }

ll pow(ll x, ll n, int mod) {
    x %= mod;
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (res * x) % mod;
        }
        x = (x * x) % mod;
        n >>= 1;
    }
    return res;
}
