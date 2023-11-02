/*
・これは自力TLE。DPにできたけど、よく見ると遷移の数が多いので無理。
・畳み込みできそうだけど、添字2次元だし片方乗算じゃなくてORだし、
　無理だよそんなんーって思ったら、公式解によればそれをやるんだった。
　2次元FFTなるものがあるらしく、それの片側をORにするみたいな。
　でも2次元FFTに関連する情報が調べてもなかなか出てこなくて、
　写経ACみたいなんはできそうだったけど、いまいちどういう理屈で
　それでOKなのか腑に落ちなかったから、とりあえず今は保留にしとく。
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
    ll N, Q;
    cin >> N >> Q;
    ll M = pow(2, N);
    auto A = listnd(2, M, 0LL);
    cin >> A[0] >> A[1];

    ll K = 2;
    mint dp[K + 1][M][2 * N + 1] = {};
    dp[0][0][0] = 1;
    rep(i, K) {
        rep(j, M) {
            rep(k, 2 * N + 1) {
                rep(m, M) {
                    if (k + popcount(m) > 2 * N) continue;
                    dp[i + 1][j | m][k + popcount(m)] += dp[i][j][k] * A[i][m];
                }
            }
        }
    }

    rep(_, Q) {
        ll x, y;
        cin >> x >> y;
        mint res = dp[K][x][y];
        print(res);
    }
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
