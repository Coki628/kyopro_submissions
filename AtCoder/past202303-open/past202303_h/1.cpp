/*
・きっちり自力AC！
・ソートしてランレングス
・下から使えるだけ使っていく貪欲で損はなさそうに見える。
　やってみると実際そうで、問題なくAC。
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
    vector<ll> A(N);
    cin >> A;

    sort(ALL(A));
    auto rle = RLE(A);
    ll M = rle.size();
    ll ans = N;
    rep(i, M - 2) {
        auto& [k1, v1] = rle[i];
        auto& [k2, v2] = rle[i + 1];
        auto& [k3, v3] = rle[i + 2];
        if (k1 == k2 - 1 and k1 == k3 - 2) {
            ll use = min({v1, v2, v3});
            ans -= use * 3;
            v2 -= use;
            v3 -= use;
        }
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
