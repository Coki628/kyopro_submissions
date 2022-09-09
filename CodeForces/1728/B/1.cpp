/*
・きっちり自力AC！
・最後から3番目を0にして、最後2つを残すことを考える。
　降順にすると偶奇で0が来るので、Nが偶数なら最後2つ以外降順、奇数なら最初に1入れて調整。
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

    vector<ll> ans;
    if (N%2 == 0) {
        rep(i, N-2, 0, -1) {
            ans.eb(i);
        }
    } else {
        ans.eb(1);
        rep(i, N-2, 1, -1) {
            ans.eb(i);
        }
    }
    ans.eb(N-1);
    ans.eb(N);
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
    while (T--) solve();

    return 0;
}
