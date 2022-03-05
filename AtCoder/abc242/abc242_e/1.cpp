/*
・きっちり自力AC！
・回文、桁DP、辞書順
・結構重めの桁DPだったけど通し切れてよかった。
　辞書順である文字列Sより前ってのを、ある数値以下の桁DPみたいに扱う。
　具体的には、前から見てある文字がS[i]より小さくなれば、
　その先は何使ってもいいとなるので、これをsmallerフラグにする。
　今回は回文で、前が決まれば後ろの対応する位置も決まるので、ここの判定が加わる。
　これが結構ややこしい。後ろは最後に決めたもの(そこまでで一番手前にあるもの)を優先するので、
　前半が同値の場合、後ろで一番手前にあるものがS[i]以下かS[i]超かで状態を分ける。
　まとめると、今見ている文字位置をi、対応する後ろをiiとして、
　・S[i]以前で既に未満が確定している
　・S[i]まで前は同値で、後ろで一番手前にあるものがS[ii]以下
　・S[i]まで前は同値で、後ろで一番手前にあるものがS[ii]超
　の3つの状態で考える。この時後ろにも同値がありうるので、その時はそれより後ろの状態を引き継ぐとする。
　これでメインパートはOKだがまだある。奇数長だと真ん中をどうするかが必要。
　上記3状態によって、何でもOK、S[N/2]以下ならOK、S[N/2]未満ならOK、をそれぞれ加味する。
・これ30～40分で詰め切れたのは十分頑張ったと思うんだけど、
　実はもっと簡単に貪欲みたいので通るらしくて、みんなかなり通してて涙。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    if (N == 1) {
        ll ans = S[0]-'A'+1;
        print(ans);
        return;
    }

    ll N2 = N/2;
    auto dp = list2d<mint>(N2+1, 3, 0);
    dp[0][1] = 1;
    rep(i, N2) {
        ll ii = N-i-1;
        rep(j, 3) {
            for (auto c : ascii_uppercase) {
                if (j == 0) {
                    dp[i+1][0] += dp[i][j];
                } else {
                    // ここで未満確定、以降は何でもできる
                    if (c < S[i]) {
                        dp[i+1][0] += dp[i][j];
                    // 前は同値、後ろは小さい
                    } elif (c == S[i] and c < S[ii]) {
                        dp[i+1][1] += dp[i][j];
                    // 前も後ろも同値(前の状態を引き継ぐ)
                    } elif (c == S[i] and c == S[ii]) {
                        dp[i+1][j] += dp[i][j];
                    // 前は同値、後ろは大きい
                    } elif (c == S[i] and c > S[ii]) {
                        dp[i+1][2] += dp[i][j];
                    }
                    // (前が大きいのは遷移不可)
                }
            }
        }
    }
    if (N%2 == 1) {
        // 真ん中1文字をどうするか、ここまでの状態で場合分け
        mint ans = dp[N2][0]*26+dp[N2][1]*(S[N/2]-'A'+1)+dp[N2][2]*(S[N/2]-'A');
        print(ans);
    } else {
        mint ans = dp[N2][0]+dp[N2][1];
        print(ans);
    }
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
