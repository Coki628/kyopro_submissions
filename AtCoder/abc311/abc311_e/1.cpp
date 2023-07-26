/*
・きっちり自力AC！
・2次元累積和にぶたん。3000^2*logは犯罪臭が漂う。0.5秒くらいでAC。
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

#include "datastructure/Accumulate2D.hpp"

void solve() {
    ll H, W, N;
    cin >> H >> W >> N;
    Accumulate2D<int> acc(H, W);
    rep(i, N) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        acc.set(a, b, 1);
    }
    acc.build();

    ll ans = 0;
    rep(h, H) {
        rep(w, W) {
            ll d = min(H - h, W - w);
            ll res = bisearch_max(0, d + 1, [&](ll x) {
                return acc.query(h, w, h + x, w + x) == 0;
            });
            ans += res;
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
