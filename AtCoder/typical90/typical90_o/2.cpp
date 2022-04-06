/*
参考：https://github.com/E869120/math-algorithm-book/blob/main/editorial/chap6-26_30/chap6-26_30.pdf
・自力ならず。。。悔しい。
・調和級数、数え上げ
・これは完敗。最近やった包除とか余事象に完全に頭を引っ張られて、
　調和級数とか全く見えなった。数え上げパートの解釈も全然だった。
・差分kに加えて、選ぶ個数mについても全探索しても、この内側ループは
　調和級数になるので多くは回らない。言われたら確かにそうなんだけど、
　まじで気付かないよなぁ…。
・で、数え上げパート。ここも1年前解いた自分も釈然とせずに終わっていたようで、
　今回も解説読んでも悩んだ。選んだ所から先k-1個が使えなくなって、
　そういう場所がm-1箇所あるから、残るN-(k-1)*(m-1)からm個選ぶ、と言われても、
　選び出す位置は選ぶ場所によって毎回ずれる訳だし、
　そうなると除く場所(k-1)*(m-1)って決めちゃうとおかしくならない？って思った。
・E8さんの今回の解説から新しい解釈をして、前よりはいくらか納得いく形にできた。
　選んだ先k-1箇所が選べないのは、長さkの横長なボールを1つ取ると解釈する。
　で、最後だけ普通のボール。余るのがN-(k*(m-1)+1)箇所の空白。
　こう考えると、余った空白をm+1箇所のボール間のどこかに割り当てると思えて、
　m+1個の部屋にN-(k*(m-1)+1)人を割り当てる通り数、重複組み合わせにできる。
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    ModTools<mint> mt(N);
    rep(k, 1, N+1) {
        mint ans = 0;
        rep(m, 1, ceil(N, k)+1) {
            ans += mt.nHr(m+1, N-(k*(m-1)+1));
        }
        print(ans);
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
