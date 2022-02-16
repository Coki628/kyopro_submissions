/*
・dojo set_e_3_6
・自力ならず。。
・スライドbitDP、余事象
・この問題確かスライドbitDPのやつだよなぁまで思い出したのに正しい方針は立たず。
　dp[i][j][k] := i文字目まで見て、j=今x,y,zのどれを見ているか、今見ているx,y,zの和がk
　みたいな嘘解法DP生やしてサンプルも合わずに終了。。
・なんとなくスライドbitDPってグリッドとかで1マスずつずらしてくみたいなイメージがあったんだけど、
　こうやって数列の区間和を管理するみたいな使い方もできたんだね。。
　多分こっちを先に見たと思うんだけど、すっかり忘れてたよ。。
　数列を位置毎じゃなくて、直前の和が17くらいまで値毎に管理する感じ。
　これノーヒントで自力導出する人やばいな。。
・さて、実装方針もまあまあ面倒で。遷移パートとか悩むんだけど、
　昔の自分がしっかりコメント付きでコード書いてくれてたからそれ見て理解。
　C++だと1ビットケチることもないので、その分簡潔には書けたけど。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, X, Y, Z;
    cin >> N >> X >> Y >> Z;

    ll M = X+Y+Z;
    // XYZとの一致をチェックするビット列
    ll ng = 1<<(X+Y+Z-1) | 1<<(Y+Z-1) | 1<<(Z-1);
    // dp[i][S] := i個目まで見て、前の値M以下までの集合がSの時の、XYZを含まないものの通り数
    auto dp = list2d<mint>(N+1, 1<<M, 0);
    dp[0][0] = 1;
    ll msk = (1<<M)-1;
    rep(i, N) {
        rep(bit, 1<<M) {
            rep(d, 10) {
                // 1ビットずらして1を足してjビットずらしてマスクする
                ll nxbit = (((bit<<1)|1)<<d)&msk;
                // 直前Mビットで使った値がXYZと一致していないか確認する
                // (大きい方に余分なビットが立っている可能性があるので、ngと&取ってからチェック)
                if ((nxbit&ng) != ng) {
                    dp[i+1][nxbit] += dp[i][bit];
                }
            }
        }
    }
    mint ans = mint(10).pow(N)-sum(dp[N]);
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
