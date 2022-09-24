/*
・速攻自力AC！
・DFSして、戻りでパス回収してくればOK。
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
    ll N, x, y;
    cin >> N >> x >> y;
    x--; y--;
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> ans;
    auto dfs = [&](auto&& f, ll u, ll prv) -> bool {
        if (u == x) return true;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            if (f(f, v, u)) {
                ans.eb(v+1);
                return true;
            }
        }
        return false;
    };
    dfs(dfs, y, -1);
    ans.eb(y+1);
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
