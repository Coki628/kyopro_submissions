/*
・これはTLE。
・G1の実装を添字逆にして、nCr部分が同じ遷移をまとめた。
　遷移が1回じゃなくて全体でNになってたりしないかなぁと思ったけどダメみたいだった。
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
    // dp[i][j] := iブロック作って、j番目まで見た通り数
    auto dp = listnd(N + 1, N + 1, (mint)0);
    dp[0][0] = 1;
    rep(i, N) {
        Accumulate<mint> acc(dp[i]);
        rep(j, N) {
            ll k = bisect_right(adj[C[j]], j);
            if (k - K < 0) continue;
            ll cnt = K;
            rep(m, k - K, 0, -1) {
                ll r = adj[C[j]][m] + 1;
                ll l = adj[C[j]][m - 1] + 1;
                dp[i + 1][j + 1] += acc.query(l, r) * mt.nCr(cnt - 1, K - 1);
                cnt++;
            }
            ll r = adj[C[j]][0] + 1;
            ll l = 0;
            dp[i + 1][j + 1] += acc.query(l, r) * mt.nCr(cnt - 1, K - 1);
        }
    }
    ll mx = 0;
    rep(i, 1, N + 1) {
        rep(j, N + 1) {
            if (dp[i][j] != 0) {
                chmax(mx, i);
            }
        }
    }
    if (mx == 0) {
        print(1);
        return;
    }
    mint ans = 0;
    rep(i, N + 1) {
        ans += dp[mx][i];
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
