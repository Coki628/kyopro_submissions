/*
参考：https://atcoder.jp/contests/abc296/editorial/6117
・自力ならず。。
・まず多重集合の一致は前提としてある。(まあこれはそれはそう)　
　で、それがOKだとして、重複があればいつでもYes、なければ転倒数の和の偶奇が同じかどうか。
・ありがちだしエスパーならできるかもだけど、分かるかそんなんー！ってなる。
　隣接スワップで転倒数はよく出てくるけど、任意スワップでも、
　転倒数の和の偶奇が必ず変化するっていう特徴があるらしい。(順列の場合ね)
　なので、今回で言えば両方の数列で同時にスワップしてるから、
　和の偶奇は変化せず、つまり元々一致してなきゃ数列一致はあり得ない、と。
　(一致してれば絶対うまくいく理由も公式解説は説明してくれてるけど、
　あんまよく分かってない。。)
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

#include "datastructure/get_inversion.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    cin >> A >> B;
    A--, B--;

    if (sorted(A) != sorted(B)) {
        No();
        return;
    }
    set<ll> se1(ALL(A)), se2(ALL(B));
    if (se1.size() < N) {
        Yes();
        return;
    }

    if (get_inversion(A) % 2 == get_inversion(B) % 2) {
        Yes();
    } else {
        No();
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
