/*
・自力AC！
・mex手前までと使える最大値で埋める。あとはダメなやつを場合分け。
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
    ll N, K, X;
    cin >> N >> K >> X;

    if (K - 1 > X) {
        print(-1);
        return;
    }

    vector<ll> res;
    rep(i, K) {
        res.eb(i);
    }
    if (res.size() > N) {
        print(-1);
        return;
    }

    rep(_, K, N) {
        res.eb(K == X ? K - 1 : X);
    }
    ll ans = sum(res);
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
