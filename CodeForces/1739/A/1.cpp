/*
・自力AC！
・題意より、全く動けない場合とどのマスに置いても(1歩でも)動ける場合は、答えはどこでもいい。
　つまり動けないマスも動けるマスもありそうな場合だけ気をつける。
　これに該当するのは、縦横の小さい方が3の場合と、小さい方が2で大きい方が3の場合。
　(長さ3の方で2に置くとどこにも行けず、それ以外なら動ける。)
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
    ll N, M;
    cin >> N >> M;

    if (N > M) swap(N, M);
    if (N == 3 or N == 2 and M == 3) {
        print(mkp(2, 2));
    } else {
        print(mkp(1, 1));
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
