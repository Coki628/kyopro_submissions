/*
参考：https://www.youtube.com/watch?v=SZGIhJaZxK8
・ABC残埋め
・自力全然無理。いやーさすがに黄diffはしんどい。解説動画じっくり見てやっと理解。
・主客転倒、順列のDP、サイクル、数え上げDP
・まず最初の取っ掛かりとして、N!通り見るのは無理なので、スコアがjとなるものの通り数を数えるとして、
　Σ(スコア)^K*通り数 を求める形にして考える。これは何かもう主客転倒の定番みたいなやつ。
・これならi番目まで見て、スコアがjとなる通り数 的なDPを進められそうな気がしてくる。
　ここで、これは順列の数え上げDPなので、i番目まで見ての所を、(何番かに関わらず)i個使って、
　の形にして順列の順序違いで性質同じやつをまとめあげる。これも結構見たことある方法。
・スコアとしてはそこまでに作ったサイクルのLCMになる。これはまあ大丈夫。
　問題は遷移の時係数としてどのくらい状態まとまって増えるかで、
　重複なく数えるための方法が必要になる。この時、この方針も結構見たことある気がするけど、
　未使用で最小の値を固定するとすると、重複なく数えられる。
　よって、N-使用済-1個から、順序を考慮して、次に追加する個数-1個選ぶ、みたいに
　固定分を-1した形で二項係数をやる。順序があるので、nCrじゃなくてnPr使う。
・このDPをN個使い終わる所まで回せば、後はΣ(スコア)^K*通り数 の定義通りに答えに足せばOK。
・解説PDF見た所までだとめっちゃ難しく感じたけど、理解してみると、
　やったことあるテクとか典型みたいなやつの組み合わせなんだよね…。解けるようになりたいね。
*/

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
    ll N, K;
    cin >> N >> K;

    ModTools<mint> mt(N);
    // dp[i][j] := i個使って、そこまでのサイクルのlcmがjの時の通り数
    vector<map<ll, mint>> dp(N+1);
    dp[0][1] = 1;
    rep(i, N) {
        for (auto [l, v] : dp[i]) {
            // 今回追加するサイクル長をjとする遷移(未使用で最小の値を固定するとすると、重複なく数えられる)
            rep(j, 1, N+1) {
                if (i+j > N) break;
                // N-i-1個から、順序を考慮してj-1個選ぶ(-1は固定している1個の分)
                dp[i+j][lcm(l, j)] += v * mt.nPr(N-i-1, j-1);
            }
        }
    }
    mint ans = 0;
    for (auto [l, v] : dp[N]) {
        ans += v * pow(l, K, MOD);
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
