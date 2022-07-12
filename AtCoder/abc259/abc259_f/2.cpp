/*
・これはTLE想定。
　dp[u][i] := 頂点uの部分木まで見て、uに接続する辺をi本以下選んだ時の最大値
　みたいなDPをやる。
・ちょっと普通のDPと違う注意点として、内側の遷移のループで、DP配列をそのまま更新すると、
　遷移元dp[u][i]にあらぬ変更がかかってしまうので、一時的にコピー作って対応。
　この感じは2乗の木DPでのアプローチと似てる。
・2乗の木DPが3乗っぽく見える2乗なら、これはうまくループ短くすれば
　2乗っぽく見える1乗になるんじゃあ、とか思ってやってみたけど全然そんなことなかった…。
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
        dp[u].assign(1, -INF);
        dp[u][0] = 0;
        ll i = 1;
        for (auto [v, w] : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            ll sz = min(i+1, D[u]+1);
            vector<ll> nxt(sz, -INF);
            rep(j, sz) {
                if (j < dp[u].size()) {
                    chmax(nxt[j], dp[u][j]+dp[v][D[v]]);
                }
                if (j+1 < sz and D[v] > 0) {
                    chmax(nxt[j+1], dp[u][j]+dp[v][D[v]-1]+w);
                }
            }
            dp[u] = nxt;
            i++;
        }
        while (dp[u].size() <= D[u]) dp[u].eb(-INF);
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
