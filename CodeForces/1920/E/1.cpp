/*
参考：https://codeforces.com/contest/1920/submission/241469603
・自力ならず。。でも遷移がちゃんと整理できればDよりはこっちのが解けそうかも。
・01文字列、数え上げDP、難しいDP、indexに沿って進まないDP
・tonegawaさんの提出がとても参考になった。有用なコメントも付いてて分かりやすい。
　きっと2次元DPなんだろうとは思いつつ、自力ではどう遷移するか見出せなかった。
　やり方は、現在文字列の末尾に何個0がついた状態なのかを持っておき、
　そこに「1と0*k個を末尾に追加する」という操作をする遷移をやる。
　これで新しく付く1に絡むgood substringが何個増えるか分かって次の状態に進める。
　後は長さKを超えるgood substringがあってはいけないことと、
　good substringの総数がNを超えるのは答えを数える上で意味がないことによって、
　遷移のループを大きく枝刈りできるので、3乗に見えるループでも間に合った。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

    // good substringは"00001000"みたいなやつ。
    // 左右の0の数は自由なのでそこで通り数が「(左の0の数+1) * (右の0の数+1)」増える。

    // dp[i][j] := good substringがi個、末尾に連続する0の個数がj個の時の通り数
    auto dp = listnd(N + 1, K + 1, (mint)0);
    rep(j, K + 1) {
        // 最初に0がj個(1はまだ1つもない状態)
        dp[0][j] = 1;
    }
    rep(i, N) {
        rep(j, K + 1) {
            // 1と0*k個を末尾に追加する
            rep(k, K + 1) {
                // '0'*j + '1' + '0'*k
                ll mxlen = j + 1 + k;
                // Kより長いgood substringができてしまう
                if (mxlen > K) break;
                ll nxi = i + (j + 1) * (k + 1);
                // good substringの総数がN個を超える
                if (nxi > N) break;
                dp[nxi][k] += dp[i][j];
            }
        }
    }
    mint ans = 0;
    rep(j, K + 1) {
        ans += dp[N][j];
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
