/*
・終了後自力AC？でもTLでDPってのは見てしまったと思う。
・区間状態DP
・連続部分列の列挙で、取りうる値の状態も0か1しかないので、
　区間前、中、後を持ついつもの区間状態DPが使える。
・本番中はD通せなくて焦ったのもあって、すぐにはこれ見えなくてFに行った訳だけど、
　終了後よく考えたらちゃんと方針立った。
　結果的に30分以上張り付いてF通せなかったから、今回は完全に立ち回り負けね。。
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
    string S;
    cin >> S;

    auto dp = listnd(N + 1, 3, 2, 0LL);
    dp[0][0][0] = 1;
    rep(i, N) {
        ll a = S[i] - '0';
        rep(j, 3) {
            rep(k, 2) {
                rep(jj, j, 3) {
                    ll kk = jj == 1 ? (j == 0 ? a : !(k & a)) : k;
                    dp[i + 1][jj][kk] += dp[i][j][k];
                }
            }
        }
    }
    ll ans = dp[N][1][1] + dp[N][2][1];
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
