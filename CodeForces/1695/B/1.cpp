/*
参考：https://twitter.com/kude_coder/status/1538202679323033601
・自力ならず…。
・ゲーム、偶奇
・色々迷走もしたんだけど、最終的に、N奇数なら先手必勝(最初に全部取る)、
　偶数なら先に1があるとこ(そこ次に自分が引くけど0にするしかない)、ってやってWAで終了。
　正解は、1ずつ減らす(ので最終的に最小値の場所で終わる)だった。言われると超納得…。
　なるべく減らしたくないって気持ちまでは来てたのに、なんで気付かなかったこれ。。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    if (N%2 == 1) {
        print("Mike");
        return;
    }

    ll mni = min_element(ALL(A)) - A.begin();
    if (mni%2 == 0) {
        print("Joe");
    } else {
        print("Mike");
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
