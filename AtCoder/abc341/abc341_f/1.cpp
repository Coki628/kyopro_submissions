/*
参考：https://twitter.com/kude_coder/status/1758848936813699137
　　　https://twitter.com/momohara_kyopro/status/1758849857480171712
・自力ならず…。これは悔しい。
・一般グラフ、2乗オーダー、寄与、部分和DP、復元
・近い所まで行ってたけど詰め切れず…。
　制約と、操作内容からして明らかに部分和DPを誘っている感じではある。
　そう思いつつも、各頂点から、ありえる遷移先だけ見て毎回部分和DP、
　という本質に辿り着くのに大分時間がかかった。
　そこから先もダメで、「ある頂点uのコマ1個がもたらす寄与」
　を求めるDPにしなきゃいけなかったのに、A[u]の重さがついたままやろうとしてた。
　ここがどうにも自分からは導けなかったように思う。
・なお、寄与を求めた後は*A[i]すればいいので復元は不要だったという…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<ll> W(N), A(N);
    cin >> W >> A;

    vector<pll> WI;
    rep(i, N) {
        WI.eb(W[i], i);
    }
    sort(ALL(WI));

    vector<ll> B(N);
    vvl vs(N);
    for (auto [_, u] : WI) {
        ll n = nodes[u].size();
        auto dp = listnd(n + 1, W[u], -INF);
        auto prv = listnd(n + 1, W[u], -1);
        auto val = listnd(n + 1, W[u], -1);
        dp[0][0] = 0;
        rep(i, n) {
            ll v = nodes[u][i];
            rep(w, W[u]) {
                if (dp[i][w] == -INF) continue;
                if (chmax(dp[i + 1][w], dp[i][w])) {
                    prv[i + 1][w] = w;
                    val[i + 1][w] = v;
                }
                if (w + W[v] < W[u]) {
                    if (chmax(dp[i + 1][w + W[v]], dp[i][w] + B[v])) {
                        prv[i + 1][w + W[v]] = w;
                        val[i + 1][w + W[v]] = v;
                    }
                }
            }
        }
        ll mxa = -INF, mxwi = -1;
        rep(w, W[u]) {
            if (chmax(mxa, dp[n][w])) {
                mxwi = w;
            }
        }
        vector<ll> vec;
        ll i = n, w = mxwi;
        while (i > 0) {
            if (w != prv[i][w]) {
                vec.eb(val[i][w]);
            }
            w = prv[i][w];
            i--;
        }
        vs[u] = vec;
        B[u] = 1 + dp[n][mxwi];
    }

    reverse(ALL(WI));
    ll ans = 0;
    for (auto [_, u] : WI) {
        ans += A[u];
        for (auto v : vs[u]) {
            A[v] += A[u];
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
