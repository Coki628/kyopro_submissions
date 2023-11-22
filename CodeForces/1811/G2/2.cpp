/*
参考：https://twitter.com/kude_coder/status/1643304255443574784
・自力ならず。
・区切るDP、組み合わせの遷移、最大値の通り数を求めるDP
・実はG1の方針で結構惜しい所まで来てた。
　最大値の通り数を求める時、最大値の値は添字に持たなくても、
　(最大値, 通り数) のペアを値にしてもOKだと、くでさんの方針で分かった。
　確かに言われてみると、最短経路の通り数とかこういう形で求めるよね。
　これでブロック数が添字に必要なくなるので、
　1次元DPと遷移NのO(N^2)となり、無事ACした。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> C(N);
    cin >> C;

    ModTools<mint> mt(N + 1);
    vvl adj(N + 1);
    rep(i, N) {
        adj[C[i]].eb(i);
    }
    // dp[i] := i番目まで見た時の、(最大ブロック数, その通り数)
    vector<pair<ll, mint>> dp(N + 1, {-INF, 0});
    dp[0] = {0, 1};
    ll allmx = 0;
    rep(i, N) {
        ll k = bisect_right(adj[C[i]], i);
        if (k - K < 0) continue;
        ll r = adj[C[i]][k - K];
        ll cnt = K - 1;
        rep(m, r, -1, -1) {
            if (C[m] == C[i]) cnt++;
            if (dp[i + 1].first < dp[m].first + 1) {
                dp[i + 1] = {dp[m].first + 1, dp[m].second * mt.nCr(cnt - 1, K - 1)};
            } else if (dp[i + 1].first == dp[m].first + 1) {
                dp[i + 1].second += dp[m].second * mt.nCr(cnt - 1, K - 1);
            }
        }
        chmax(allmx, dp[i + 1].first);
    }

    mint ans = 0;
    rep(i, N + 1) {
        if (dp[i].first == allmx) {
            ans += dp[i].second;
        }
    }
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
