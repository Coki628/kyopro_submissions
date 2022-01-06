/*
参考：https://twitter.com/keijak/status/1478788069641834507
　　　https://www.codechef.com/viewsolution/55894214
・自力ならず。近い方針も考えたけど詰め切れず。
　それ以外にHLDこねくり回したり、迷走を続け終了…。
・木DP
・ちょっと状態の持ち方とか工夫が要る木DP。この辺解けるようにしていきたい。
・状態としては、
　dp[i][bit] := i以下の部分木に{ 0: 青(だけ)があるか, 1: 赤-青があるか, 2: 緑-青があるか }
　みたいな形で持つ。これを、各部分木を見ていく時に、
　「それまでの部分木たち × 今見ている部分木」みたいな所でペアができないかチェックしていく。
　ちょうど、列で右端固定して今見た場所の状態を累積してって、
　自分より左全体と今見てる要素でペアがいくつできるか見るみたいな感じとイメージは似てる。
・判定は今いる頂点の色によって状況を場合分けて、
　両側に青があるのに赤か緑がないことが発生しないか見る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/HeavyLightDecomposition.hpp"
#include "../../../_lib/cpp/_src/common/randrange.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    // dp[i][bit] := i以下の部分木に{ 0: 青があるか, 1: 赤-青があるか, 2: 緑-青があるか }
    vector<bitset<3>> dp(N);
    auto dfs = [&](auto&& f, ll u, ll prv) -> bool {
        if (S[u] == 'B') {
            dp[u][0] = 1;
        }
        for (ll v : nodes[u]) {
            if (v == prv) continue;
            if (!f(f, v, u)) {
                return false;
            }
            if (S[u] == 'B') {
                if (dp[v].any()) {
                    return false;
                }
                dp[u] |= dp[v];
            } elif (S[u] == 'R') {
                // 緑なしのペアができてしまう
                if ((dp[u][0] or dp[u][1]) and (dp[v][0] or dp[v][1])) {
                    return false;
                }
                if (dp[v][0] or dp[v][1]) {
                    dp[u][1] = 1;
                }
            } else {
                // 赤なしのペアができてしまう
                if ((dp[u][0] or dp[u][2]) and (dp[v][0] or dp[v][2])) {
                    return false;
                }
                if (dp[v][0] or dp[v][2]) {
                    dp[u][2] = 1;
                }
            }
        }
        return true;
    };

    if (dfs(dfs, 0, -1)) {
        Yes();
    } else {
        No();
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
