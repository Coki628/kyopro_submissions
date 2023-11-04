/*
・なんとか自力AC。ここもたついたのは良くなかったなー…。
・2-SAT
・閉路検出でいける気がしたんだけどUFで何か合わなくて2-SATを召喚した。
　(a=1|b=1)&(a=0|b=0)&..とすることで、((a=1&b=0)|(a=0&b=1))&..を表してる。
　絶対こんなややこしく真偽値演算やんなくてもいいだろって思いながら頑張った。
・終了後TL見た。二部グラフ判定だわこれ。
　何でグラフに帰着までしといて二部グラフ思い出さなかったんだー…。
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

#include "acl/twosat.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(M), B(M);
    cin >> A >> B;
    A--, B--;

    atcoder::two_sat ts(N);
    rep(i, M) {
        ts.add_clause(A[i], true, B[i], true);
        ts.add_clause(A[i], false, B[i], false);
    }
    if (ts.satisfiable()) {
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
