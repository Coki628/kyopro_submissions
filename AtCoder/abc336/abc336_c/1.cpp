/*
・自力AC！
・K番目の値、N進法変換
・N進法変換の5進をちょっといじって*2する。
・なお、N進法が見えなかった場合、決め打ちにぶたん*桁DPっていう
　(Cにしては)地獄実装コースが用意されてる模様。(ワドさんのツイートより)
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
    ll N;
    cin >> N;
    N--;

    ll B = 5;
    string res;
    ll m;
    while (N > 0) {
        tie(N, m) = divmod(N, B);
        res += tochar(m * 2);
    }
    reverse(ALL(res));
    if (res == "") {
        res = "0";
    }
    print(res);
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
