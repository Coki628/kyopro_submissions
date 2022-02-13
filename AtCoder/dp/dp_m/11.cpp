/*
参考：https://maspypy.com/%e5%a4%9a%e9%a0%85%e5%bc%8f%e3%83%bb%e5%bd%a2%e5%bc%8f%e7%9a%84%e3%81%b9%e3%81%8d%e7%b4%9a%e6%95%b0%ef%bc%88%ef%bc%92%ef%bc%89%e5%bc%8f%e5%a4%89%e5%bd%a2%e3%81%ab%e3%82%88%e3%82%8b%e8%a7%a3%e6%b3%95#toc13
・FPS演習
・FPS、式変形
・各回の遷移は等比数列の和から、2項の多項式にできる。
　分子側の(1-x^a)みたいなやつは、前の状態と同じ位置から、a個ずらしたやつを引く。
　ずらすのも引くのも配列長Kくらい計算量がかかるが、今回は操作Nが100回なので大丈夫。
　分母側は全部(1-x)なのでこれをN乗するだけで、これはもっと高速にできる。
・計算量K*Nが1000万あるからどうかと思ったけどAC0.13秒とかで全然速かった。
　多分この1000万のパートには乗算で畳み込みとか含まれないから軽いんだろう。
・この方針はmaspyさんの記事を元にやったけど、
　そこにNが10万でもできるって書いてあったけどどうやるんだろう。。
　→多分expとか使って部分和DP高速化したあれじゃないかな、やってみるか。
・やってみた。けどこれはWA。(1-x^a)と(1+x^a)じゃ勝手が違うのかなー。
　違いは係数の正負だけなんだから、同じように出来る気がするんだけどな。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"
#include "math/fps/pow_term2.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    vector<ll> C(K+2);
    rep(i, N) {
        C[A[i]+1]--;
    }
    FPS<mint> res(K+1), fps(K+2);
    res[0] = 1;
    // Π(1-x^(a+1))
    rep(a, 1, K+2) {
        if (C[a] == 0) continue;
        ll k = 1;
        while (a*k <= K+1) {
            fps[a*k] += (mint)(k&1 ? 1 : -1)*mt.div(C[a], k);
            k++;
        }
    }
    res *= fps.exp(K+2);
    res.shrink(K+1);
    // /= (1-x)^N
    res *= pow_term2_inv(N, K+1);
    mint ans = res[K];
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
