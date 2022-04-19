/*
・終了後、なんとか自力AC？TLで解法見えちゃったけど、まあだいたい自分がやろうとしたのと同じ感じ。
・状態管理を頑張るDP、任意Modint、QCFium法
・直前の状態を適切に持ちながら進むんだけど、まあ大変。
　形と上下連結の有無で5つの状態にした。遷移どうなるかは、
　行ける行けないを自分ノートで色々書いたので見るならそっちを参照。
・結構定数倍がきつくて、3000^2*5^2をまともにやると2億超えくらいになるのでつらめ。
　2.1秒くらいのTLEをQCFium法したら0.65秒になって無事AC。
・通り数0のcontinue書き忘れてた。書いたらQCFiumしなくてもAC1.18秒。
　その状態でQCFiumしたら0.40秒。やっぱシンプルなDPだとQCFium効くね。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
// using mint = ModInt<MOD>;
#include "template.hpp"

#include "combinatorics/ArbitraryModInt.hpp"
using mint = ArbitraryModInt;

mint dp[3007][3007][5];

void solve() {
    ll N, P;
    cin >> N >> P;
    mint::set_mod(P);

    // dp[i][m][j] := i列目の頂点まで左右を繋いで、辺をm本削除して、最後の状態がjの通り数
    // j = 0: L, 1: 匚, 2: ニ(上下連結), 3: ニ(上下非連結), 4: 一(上下非連結)
    dp[0][1][0] = 2;
    dp[0][0][1] = 1;
    dp[0][1][3] = 1;
    rep(i, N-2) {
        rep(m, N) {
            rep(j, 5) {
                if (dp[i][m][j] == 0) continue;
                rep(k, 5) {
                    if (
                        j == 0 and k == 2 or
                        j == 1 and k == 3 or
                        j == 2 and k == 3 or
                        j == 3 and k == 2
                    ) {
                        continue;
                    }
                    if (j == 4 and not (k == 0 or k == 1 or k == 3)) continue;
                    if (k == 4 and not (j == 1 or j == 2)) continue;
                    ll nxm = m + (k == 1 ? 0 : k == 4 ? 2 : 1);
                    if (nxm >= N) continue;
                    dp[i+1][nxm][k] += dp[i][m][j] * (1+(k == 0 or k == 4));
                }
            }
        }
    }
    vector<mint> ans(N);
    rep(m, 1, N) {
        // 右端の縦線の有無を決める
        ans[m] = (
            dp[N-2][m-1][1] + dp[N-2][m-1][2] +
            dp[N-2][m][0] + dp[N-2][m][1] + dp[N-2][m][2] + dp[N-2][m][3] + dp[N-2][m][4]
        );
    }
    ans.erase(ans.begin());
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
