/*
・自力AC！
・累積和取っとけば、自分より手前の1引いて後ろの0足して、
　みたいのでその位置をフリップした時の転倒数の差分が分かる。
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
    cin >> A;

    vector<Accumulate<ll>> acc(2, {N});
    rep(i, N) {
        acc[A[i]].add(i, 1);
    }
    rep(p, 2) acc[p].build();

    ll base = 0;
    rep(i, N) {
        if (A[i] == 0) {
            base += acc[1].query(0, i);
        }
    }
    ll ans = base;
    rep(i, N) {
        if (A[i] == 0) {
            chmax(ans, base-acc[1].query(0, i)+acc[0].query(i+1, N));
        } else {
            chmax(ans, base-acc[0].query(i+1, N)+acc[1].query(0, i));
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
    while (T--) solve();

    return 0;
}
