/*
・agc017_d
・自力ならず。。雰囲気覚えてたのに詰め切れず。
・Grundy数、木上のゲーム
・まあ昔解いた時のを見て欲しい。自力ACしてる。。
　今回は dp[u] ^= dp[v]+1 って遷移を dp[u] ^= 1-dp[v] ってしててWAだった。
　なんか1つ前が負け状態ならここは勝ち状態みたいに反転するかなーとか思ったんだけど、
　Grundy数が1増えるんだね。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

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

    vector<ll> dp(N);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        for (ll v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            dp[u] ^= dp[v]+1;
        }
    };
    dfs(dfs, 0, -1);
    if (dp[0]) {
        print("Alice");
    } else {
        print("Bob");
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
