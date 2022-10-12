/*
・自力AC。これも遅かった。
・N=2,3を場合分けした後、後ろ2つだけ前にシフトしてくるとした。
　3つくらい嘘方針生やしてタイムロス…。
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
    ll N;
    cin >> N;

    if (N == 2) {
        print(mkp(2, 1));
        return;
    }
    if (N == 3) {
        print(-1);
        return;
    }

    vector<ll> ans;
    rep(p, N-1, N+1) {
        ans.eb(p);
    }
    rep(p, 1, N-1) {
        ans.eb(p);
    }
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
