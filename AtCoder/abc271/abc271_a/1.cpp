/*
・自前の進数変換ライブラリが10進よりでかい方に対応してなくてその場でいじった。
　Aにしては、とか思ったけど2桁以下だから1回divmodすりゃあいいだけか…。
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

    ll num = N;
    string res;
    ll m;
    while (num > 0) {
        tie(num, m) = divmod(num, 16LL);
        if (m < 10) {
            res += '0'+m;
        } else {
            res += 'A'+(m-10);
        }
    }
    reverse(ALL(res));
    res = zfill(res, 2);
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
