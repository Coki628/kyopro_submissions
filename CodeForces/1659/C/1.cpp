/*
・これは結構きっちり自力AC。
・1つ決めて全探索、累積和の累積和
・遷都は1つずつやっても一気にやっても、最終的にどの位置までやるかが同じならコストは同じ、
　が分かると、どこまで遷都するかを全探索ができる。
　首都より手前は累積和みたいになって、後ろは累積和の累積和みたいになる。
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

void solve() {
    ll N, a, b;
    cin >> N >> a >> b;
    auto A = LIST(N);

    A.insert(A.begin(), 0);
    vector<ll> tmp(N+1);
    rep(i, N) {
        tmp[i+1] = (A[i+1]-A[i]) * b;
    }
    Accumulate<ll> acc1(tmp);
    rep(i, N) {
        tmp[i+1] += tmp[i];
    }
    Accumulate<ll> acc2(tmp);

    ll ans = INF;
    rep(i, N+1) {
        ll acost = A[i] * a;
        ll bcost = acc1.query(0, i+1) + acc2.query(i+1, N+1) - acc2[i]*(N-i);
        chmin(ans, acost + bcost);
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
