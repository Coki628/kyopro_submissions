/*
参考：https://codeforces.com/contest/1689/submission/160110045
・自力ならず。これは解きたかったな。悔しい。
・二分木、木DP
・選んだ方の部分木は総取りできて、逆側はその後の選択によって変わってくる。
　最終的にかなり近い形までできていたが詰め切れず。
　どちらを取るかの選択を、ソートして部分木サイズの大きい方と決めてしまっていた。
　これを両方試してmax取るようにするとAC。。
　本番中は、部分木サイズが大きいならそれを先に取るのが最善な気がしてしまったけど、
　その後の形によっては、先に部分木の小さい方を取る方がいいこともありそうだね確かに…。
　(大きい方の部分木が一直線グラフで小さい方が完全二分木みたいだったら、
　小さい方は今取らないと結構な頂点を失うけど、
　大きい方は1回遅れても次で全取りできるので損失1で済む、みたいな。)
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
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> sz(N), dp(N);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        vector<ll> cur;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            sz[u] += sz[v] + 1;
            cur.eb(v);
        }
        if (cur.size() == 0) {
            dp[u] = 0;
        } elif (cur.size() == 1) {
            dp[u] = sz[cur[0]];
        } else {
            // どっちを切ってどっちを残すか両方試す
            dp[u] = max(sz[cur[0]]+dp[cur[1]], sz[cur[1]]+dp[cur[0]]);
        }
    };
    dfs(dfs, 0, -1);
    ll ans = dp[0];
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
