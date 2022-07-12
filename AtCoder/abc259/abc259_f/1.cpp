/*
・これはTLE想定。
　dp[u][i] := 頂点uの部分木まで見て、uに接続する辺をi本以下選んだ時の最大値
　みたいなDPをやる。
・ちょっと普通のDPと違う注意点として、内側の遷移のループで、DP配列をそのまま更新すると、
　遷移元dp[u][i]にあらぬ変更がかかってしまうので、一時的にコピー作って対応。
　この感じは2乗の木DPでのアプローチと似てる。
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
    auto D = LIST(N);
    vvpll nodes(N);
    rep(i, N-1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        nodes[u].eb(v, w);
        nodes[v].eb(u, w);
    }

    vvl dp(N);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        dp[u].assign(D[u]+1, -INF);
        dp[u][0] = 0;
        auto nxt = dp[u];
        for (auto [v, w] : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            rep(i, D[u]+1) {
                chmax(nxt[i], dp[u][i]+dp[v][D[v]]);
                if (i+1 <= D[u] and D[v] > 0) {
                    chmax(nxt[i+1], dp[u][i]+dp[v][D[v]-1]+w);
                }
            }
            dp[u] = nxt;
        }
        rep(i, D[u]) {
            chmax(dp[u][i+1], dp[u][i]);
        }
    };
    dfs(dfs, 0, -1);
    ll ans = dp[0][D[0]];
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
