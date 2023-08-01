/*
参考：https://atcoder.jp/contests/past202206-open/editorial/4442
・自力ならず。
・ゲーム、期待値、逆転の回数
・組み合わせ
・普通に期待値DPっぽい方針しか生えず。二項係数系はほんと苦手よね。。
　「i+1ゲーム目に逆転が起こる確率」みたいな注目の仕方をすると、
　iゲーム目で同点になる確率を求めて、その直前勝った方がまた勝つ確率が1/2で、
　これは二項係数使って、「iゲーム目で同点になる通り数/全通り数*1/2」
　みたいに表せるので、全てのi(偶数のみ)でのこれを足し合わせれば答え。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    ModTools<mint> mt(N * 2);
    mint ans = 0;
    mint inv2 = (mint)1 / 2;
    vector<mint> inv2pow(N * 2);
    mint cur = 1;
    rep(i, N * 2) {
        inv2pow[i] = cur;
        cur *= inv2;
    }
    rep(i, 2, N * 2 - 1, 2) {
        ans += mt.nCr(i, i / 2) * inv2pow[i + 1];
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
