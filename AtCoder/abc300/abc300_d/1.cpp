/*
・自力AC！でもこれもハズレ方針かも。
・素数列挙、式変形
・掛け算たくさんなのでa,b,cは大きくならない。
　素数列挙してa,c固定で式変形で最大のb求めて区間和。
　素数列挙どこまでやるかは、サンプルに最大ケースがあったので、
　雑にそれが合うまで大きくして試してった感じ。適当…。
・実は内側こんな丁寧にやらなくても、枝刈りだけで通るみたい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "numbers/Eratosthenes.hpp"

Eratosthenes era(300007);

void solve() {
    ll N;
    cin >> N;

    Accumulate<ll> acc(300007);
    vector<ll> primes;
    rep(x, 2, 300007) {
        if (era.is_prime(x)) {
            acc.set(x, 1);
            primes.eb(x);
        }
    }
    acc.build();

    ll ans = 0;
    for (auto a : primes) {
        ll aa = a * a;
        for (auto c : primes) {
            if (a >= c) continue;
            ll cc = c * c;
            if (aa * cc > N) break;
            // aa * b * cc <= N → b <= floor(N, aa * cc)
            ll mxb = N / (aa * cc);
            chmin(mxb, c - 1);
            ll mnb = a + 1;
            if (mnb > mxb) continue;
            ans += acc.query(mnb, mxb + 1);
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
