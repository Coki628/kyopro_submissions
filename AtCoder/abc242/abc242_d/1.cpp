/*
参考：https://www.youtube.com/watch?v=hdkrWya61Ds
・ABC残埋め
・やっとこれupsolveした。むずすぎ…。
・二分木
・すぬけさん解説動画じっくり見てやっと理解した。マジこの考察むずいだろ…。
・まずtが大きくない場合で考えると、(k--で0-indexed済だとして)floor(k, 2)することで、
　tを1つ遡った時点での位置kを探すことができるので、
　これにより、遷移を辿って現在の文字を見つけることができる。
　(自分はこの考察さえ出なかったので、スタートラインにさえ立てなかった模様…)
・で、文字ABCを012に置き換えて考えて、今回の問題設定の文字の変化を観察すると、
　a→a+1とa+2(mod 3) みたいな遷移と解釈できる。ここから、右の子に遷移する回数をrcntとして、
　t+rcntで最初の文字から値がどのくらい進んだかが分かる。
　右の子に遷移することは、立っているビットが1つ増えることとみなせる
　(こんなん気付かないよ)ので、popcountすればこれはすぐに分かる。
　これに、初期位置での文字と、その位置で既に立っているビットの差し引きをすれば、
　答えを求めるために必要な情報が全て揃う。
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
    string S;
    cin >> S;
    ll N = S.size();

    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i]-'A';
    }
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll t, k;
        cin >> t >> k;
        k--;

        // 二分木を右に遷移した回数
        ll rcnt = popcount(k);
        // t=0時点での位置(tが大きい場合は常に0)
        ll origin = k;
        ll curt = t;
        while (origin > 0 and curt > 0) {
            origin /= 2;
            curt--;
        }
        assert(origin < N);
        // 元位置で既に立っていたビット分を差し引く
        rcnt -= popcount(origin);
        char res = 'A' + (A[origin]+t+rcnt) % 3;
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
