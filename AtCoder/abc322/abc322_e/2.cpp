/*
・N進でビットみたいに状態を持つDP
・一応やってみた。でも慣れないとちょっとややこしく感じるし、
　余程TL厳しいとかじゃなければmapで配列の状態持つDPのが良さそう。
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
    ll N, K, P;
    cin >> N >> K >> P;
    vector<ll> C(N);
    auto A = listnd(N, K, INF);
    rep(i, N) {
        cin >> C[i];
        rep(j, K) {
            cin >> A[i][j];
        }
    }

    ll M = pow(P + 1, K);
    auto dp = listnd(N + 1, M, INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(bit, M) {
            if (dp[i][bit] >= INF) continue;
            chmin(dp[i + 1][bit], dp[i][bit]);
            ll nxtval = 0;
            rep(j, K) {
                ll tmp = bit / pow(P + 1, j) % (P + 1);
                tmp = min(tmp + A[i][j], P);
                nxtval += pow(P + 1, j) * tmp;
            }
            chmin(dp[i + 1][nxtval], dp[i][bit] + C[i]);
        }
    }
    ll ans = dp[N][M - 1] < INF ? dp[N][M - 1] : -1;
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
