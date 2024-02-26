/*
・きっちり自力AC！
・前後の0だけtrimして中の0を数える。
　ランレングスした。
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

void solve(int testcase) {
    ll N;
    cin >> N;
    auto A = LIST(N);

    auto rle = RLE(A);
    if (rle[0].first == 0) {
        rle.erase(rle.begin());
    }
    if(rle.back().first == 0) {
        rle.pop_back();
    }
    ll ans = 0;
    for (auto [c, cnt] : rle) {
        if (c == 0) {
            ans += cnt;
        }
    }
    print(ans);
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
    rep(t, T) solve(t);

    return 0;
}
