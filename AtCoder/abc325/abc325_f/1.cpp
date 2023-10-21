/*
・自力ならず。。これは悔しい。
・添字にしたい状態を値に持たせるDP
・これ考えたんだよ。なんだけど、これやると最小コストが値に持たせられないから無理じゃんって。
　判定ならまだしも最小化だと無理だろうって、思ってしまったんだよね。
　よく見ると、コストは個数が分かってれば計算で後から割り出せるので、持たなくていい。
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
    ll N;
    cin >> N;
    vector<ll> D(N);
    cin >> D;
    ll L1, C1, K1, L2, C2, K2;
    cin >> L1 >> C1 >> K1 >> L2 >> C2 >> K2;

    // dp[i][j] := i個目まで見て、センサー1をj個使った時のセンサー2の最小使用個数
    auto dp = listnd(N + 1, K1 + 1, INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, K1 + 1) {
            if (dp[i][j] >= INF) continue;
            rep(k1, K1 + 1) {
                if (j + k1 > K1) break;
                ll d2 = max(D[i] - k1 * L1, 0LL);
                ll k2 = ceil(d2, L2);
                chmin(dp[i + 1][j + k1], dp[i][j] + k2);
            }
        }
    }
    ll ans = INF;
    rep(k1, K1 + 1) {
        ll k2 = dp[N][k1];
        if (k2 <= K2) {
            chmin(ans, k1 * C1 + k2 * C2);
        }
    }
    if (ans >= INF) ans = -1;
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
