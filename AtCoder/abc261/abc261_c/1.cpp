/*
・さくっと自力AC！
・最近のCにしては易しい？Counterするのはまあすぐだし、文字列整形パートが本質？
　数値→文字列変換→連結からの出力がちょっとあっとこっぽくない感じ。
　(オレは数学数学よりこういう方が好きだけど。)
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
    HashMap<string, int> C;

    rep(i, N) {
        string s;
        cin >> s;
        if (C.count(s)) {
            print(s+"("+tostr(C[s])+")");
        } else {
            print(s);
        }
        C[s]++;
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
