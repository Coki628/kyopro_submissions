/*
・自力はここまで。クエリ100回やればいけそうだったけど、30は無理。
・gcd(a,b)==b-aみたいな場所があると、mod(b-a)でb-a-aなのが多分定まる。
　これをいっぱい集めてcrtにかければいけないかな、
　ってやってたら100クエリくらいあれば当てれるようになったぽいんだけど、そこまで。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

#include "numbers/Eratosthenes.hpp"

#include "acl/math.hpp"
using namespace atcoder;

Eratosthenes era(200);
vector<ll> primes;
void prep() {
    rep(i, 200) {
        if (era.is_prime(i)) {
            primes.eb(i);
        }
    }
}

ll x = -1;
ll calc(ll a, ll b) {
    return gcd(x+a, x+b);
}

// インタラクティブ用
ll ask(ll a, ll b) {
    ll res;
    cout << "? " << a << ' ' << b << endl;
    #ifdef __LOCAL
        res = calc(a, b);
        cout << res << endl;
    #else
        cin >> res;
    #endif
    return res;
}

void answer(ll i) {
    cout << "! " << i << endl;
}

void solve() {
    #ifdef __LOCAL
        cin >> x;
    #endif
    ll limit = 100;
    vector<ll> A, B;
    ll i = 0, s = 1;
    while (limit) {
        ll diff = primes[i];
        ll res = ask(s, s+diff);
        if (res == diff) {
            A.eb(diff-s);
            B.eb(diff);
            s = 1;
            i++;
        } else {
            s++;
        }
        limit--;
    }
    auto [y, z] = crt(A, B);
    answer(y);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
