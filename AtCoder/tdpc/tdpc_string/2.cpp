/*
参考：https://atcoder.jp/contests/tdpc/editorial
　　　https://suikaba.hatenablog.com/entry/2017/08/22/163506
・類題履修：abc234_fより。でもこっちのが全然むずい。
・種類数のDP、難しい数え上げDP
・いや、まじでむずかった。状態もそうだけど、遷移がとても複雑。
　添字みたいなものがめちゃたくさん出てくるので、全てKiriさんの解説と同じに合わせた。
　ソース内コメントになるべく細かく記した。けどこんなんまじで自力で思いつく人凄すぎだよね…。
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
    const int M = 26;
    auto C = LIST(M);
    ll N = sum(C);

    ModTools<mint> mt(N);
    // dp[n][a] := n種類目の文字まで見て、同じ文字が隣り合う箇所がa箇所の時の種類数
    auto dp = list2d<mint>(M+1, N, 0);
    dp[0][0] = 1;
    ll sm = 0;
    rep(n, M) {
        // f := 文字nを使う個数
        ll f = C[n];
        // a := 同じ文字が隣り合う箇所の数
        rep(a, N) {
            if (dp[n][a] == 0) continue;
            // b := 同じ文字が隣り合わない箇所の数(両端を含む)
            ll b = sm-a+1;
            if (b < 0) break;
            // この文字が1つも使えない時は何もしない
            if (f == 0) {
                dp[n+1][a] = dp[n][a];
            } else {
                // i := f個がi箇所のグループに分かれる
                rep(i, 1, f+1) {
                    // j := i個のグループのうち、j個をaのどこかに入れる
                    rep(j, i+1) {
                        if (0 <= a+f-i-j and a+f-i-j < N) {
                            // 遷移：隣り合う箇所の増減
                            // ・新しく増えるのはf-i箇所。何グループに分かれるかによる。
                            // ・減るのはj箇所。(aは元々隣り合っている箇所なので、ここを分けることになる。)
                            // nCr(f-1, i-1) は、f個をi個のグループに分ける通り数 (写像の6相、仕切りで考える。)
                            // nCr(a, j) は、a箇所のどこかにj個を割り当てる通り数
                            // nCr(b, i-j) は、b箇所のどこかにi個の残りを割り当てる通り数
                            dp[n+1][a+f-i-j] += dp[n][a]*mt.nCr(f-1, i-1)*mt.nCr(a, j)*mt.nCr(b, i-j);
                        }
                    }
                }
            }
        }
        sm += f;
    }
    mint ans = dp[M][0];
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
