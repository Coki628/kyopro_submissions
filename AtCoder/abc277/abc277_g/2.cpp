/*
参考：https://atcoder.jp/contests/abc277/editorial/5212
　　　https://www.youtube.com/watch?v=thDkAUUi1UI
・期待値、積の和典型
・むずい。クッキーの話(dwacon6th_prelims_c)をよく熟考してから戻ってくると、
　少し話が見えやすいかもしれない。同じような仕組みで、
　向こうはN要素の数列の総乗だけど、こっちはx^2なので要素2個の数列みたいに考える。
　コメントアウトした方の遷移だと、ほぼ同じというのが分かりやすいと思う。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<ll> C(N);
    cin >> C;

    vector<mint> inv(N);
    rep(i, N) {
        inv[i] = (mint)1 / nodes[i].size();
    }
    ll L = 2;
    ModTools<mint> mt(L+1);
    // dp[i][u][j] := i回目まで見て、頂点uにいて、注目する0をj個決めた時の、期待値にかかる重みのようなもの
    mint dp[K+1][N][L+1] = {};
    dp[0][0][0] = 1;
    mint ans = 0;
    rep(i, K) {
        rep(u, N) {
            for (auto v : nodes[u]) {
                rep(j, L+1) {
                    if (C[v] == 0) {
                        // 注目する0をk個使う遷移
                        rep(k, L+1) {
                            if (j+k > L) break;
                            // dp[i+1][v][j+k] += dp[i][u][j] * inv[u] * mt.nCr(L-j, k);
                            dp[i+1][v][j+k] += dp[i][u][j] * inv[u] * (j == 0 and k == 1 ? 2 : 1);
                        }
                    } else {
                        dp[i+1][v][j] += dp[i][u][j] * inv[u];
                    }
                }
            }
        }
    }
    rep(i, K+1) {
        rep(u, N) {
            if (C[u] == 1) {
                ans += dp[i][u][2];
            }
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
