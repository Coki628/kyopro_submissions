/*
ライブラリ整備：燃やす埋める
・新規問題を一問。問題なくAC。
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

#include "graph/PSP.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> vcost(N);
    cin >> vcost;
    vector<array<ll, 3>> edges;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        edges.pb({u, v, c});
    }

    // 頂点・辺それぞれを選択肢とする
    PSP psp(N + M);
    rep(i, N) {
        // 頂点iを選ばない/選ぶ
        psp.add(i, 0, -vcost[i]);
    }
    rep(i, M) {
        auto [u, v, c] = edges[i];
        // 辺iを選ばない/選ぶ
        psp.add(N + i, 0, c);
        // 辺iを選ぶなら、頂点uも選ぶ
        psp.a_right_then_b_right(N + i, u);
        // 辺iを選ぶなら、頂点vも選ぶ
        psp.a_right_then_b_right(N + i, v);
    }
    ll ans = psp.solve();
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
