/*
・きっちり自力AC！
・座圧、BIT
・座圧BITに詰めて数えた。(想定解はmapでうまくやってた。)
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
    auto A = LIST(N);

    Compress<ll> cp(A);
    A = cp.zip(A);
    ll M = cp.size();
    BIT<ll> bit(M);
    rep(i, N) {
        if (bit[A[i]] == 0) {
            bit.add(A[i], 1);
        }
    }
    vector<ll> C(N);
    rep(i, N) {
        ll res = bit.query(A[i]+1, M);
        C[res]++;
    }
    print(C, '\n');
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
