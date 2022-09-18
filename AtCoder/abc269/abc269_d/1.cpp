/*
・きっちり自力AC！
・mapに座標詰めて6方向見る。連結成分はUFで管理。
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
    UnionFind uf(N);
    map<pll, ll> mp;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        mp[{x, y}] = i;
    }

    const vector<pii> directions = {{-1, -1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}};
    for (auto [k, i] : mp) {
        auto [h, w] = k;
        for (auto [dh, dw] : directions) {
            int nh = h + dh;
            int nw = w + dw;
            if (not mp.count({nh, nw})) continue;
            ll j = mp[{nh, nw}];
            uf.merge(i, j);
        }
    }
    ll ans = uf.size();
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
