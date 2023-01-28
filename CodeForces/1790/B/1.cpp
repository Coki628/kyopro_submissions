/*
・きっちり自力AC！
・残りN-1個になるべく均等に割り振りたいので割り算する。
　あとは丁寧に場合分け。
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
    ll N, S, R;
    cin >> N >> S >> R;

    ll x = S - R;
    if (x > 6) {
        print(-1);
        return;
    }
    auto [d, m] = divmod(R, N - 1);
    vector<ll> ans(N - 1, d);
    rep(i, m) {
        ans[i]++;
    }
    if (max(ans) > x or min(ans) == 0) {
        print(-1);
        return;
    }
    ans.eb(x);
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
