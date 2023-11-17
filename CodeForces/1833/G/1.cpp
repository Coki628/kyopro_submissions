/*
・きっちり自力AC！Div.3時間内全完嬉しい。20分くらい余ったし。
・木グラフ、復元
・DFSして、葉から貪欲に必要な場所を切る。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    map<pll, ll> mp;
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        mp[{u, v}] = i;
        mp[{v, u}] = i;
    }

    try {
        vector<ll> sz(N, 1), ans;
        auto dfs = [&](auto &&f, ll u, ll prv) -> void {
            for (auto v : nodes[u]) {
                if (v == prv) continue;
                f(f, v, u);
                sz[u] += sz[v];
            }
            // 構築不可 or 最後が合わない
            if (sz[u] > 3 or prv == -1 and sz[u] != 3) {
                throw -1;
            // ここで辺を切る
            } else if (prv != -1 and sz[u] == 3) {
                ans.eb(mp[{prv, u}]);
                sz[u] = 0;
            }
        };
        dfs(dfs, 0, -1);
        ans++;
        print(ans.size());
        print(ans);
    } catch (int e) {
        print(-1);
    }
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
