/*
・自力AC！
・Pi<=8が怪しい。って思うとmodでlcm(1~8)を同一視したくなる。
　添字にしてDPかと思ったら出発点だけ分ければいいので840通り前計算シミュっとく。
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

void solve() {
    ll N, X, Y;
    cin >> N >> X >> Y;
    vector<ll> P(N), T(N);
    P[0] = 1, T[0] = X;
    rep(i, 1, N) {
        cin >> P[i] >> T[i];
    }

    ll M = 1;
    rep(p, 1, 9) {
        M = lcm(M, p);
    }
    // M = 840

    vector<ll> cost(M);
    rep(m, M) {
        ll cur = m;
        rep(i, N) {
            ll wait = (P[i] - cur % P[i]) % P[i];
            cur += wait + T[i];
        }
        cost[m] = cur;
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll q;
        cin >> q;

        auto [d, m] = divmod(q, M);
        ll res = d * M + cost[m] + Y;
        print(res);
    }
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
