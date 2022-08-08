/*
・きっちり自力AC！
・1個ずつずらしてく。
　最初前後入れ替えたけど、これも多分いらなくて全部1個ずつずらすだけでいいはず。
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

    vector<ll> A(N);
    iota(ALL(A), 1);
    vvl ans;
    ans.eb(A);
    swap(A[0], A[N-1]);
    ans.eb(A);
    rep(i, N-2) {
        swap(A[i], A[i+1]);
        ans.eb(A);
    }
    print(ans.size());
    for (auto& a : ans) print(a);
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
