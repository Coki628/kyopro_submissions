/*
・ライブラリ整備：2次元いもすのverify
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/Imos2D.hpp"

void solve() {
    ll N;
    cin >> N;

    ll M = 1000;
    Imos2D<ll> imos(M, M);
    rep(i, N) {
        ll lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;

        imos.add(lx, ly, rx, ry, 1);
    }
    imos.build();

    vector<ll> ans(N+1);
    rep(i, M) {
        rep(j, M) {
            ans[imos.get(i, j)]++;
        }
    }
    rep(i, 1, N+1) {
        print(ans[i]);
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
