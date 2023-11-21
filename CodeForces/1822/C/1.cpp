/*
・きっちり自力AC！
・グリッド、渦巻き、等差数列の和
・ちょっと線を付け替えると、ほぼ全部正方形で囲ってるみたいな形にできる。
　この状態で正方形毎に線分の長さを数えると、ほぼ等差数列の和にできる。
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

#include "numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll N;
    cin >> N;

    if (N % 2 == 0) {
        ll res = arithmetic_sequence_sum(2LL, 2LL, N / 2) * 4 + 2;
        print(res);
    } else {
        ll res = arithmetic_sequence_sum(1LL, 2LL, ceil(N, 2LL)) * 4 + 1;
        print(res);
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
