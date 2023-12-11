/*
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

    vector<pll> AI;
    rep(i, N) {
        AI.eb(A[i], i);
    }
    sort(ALL(AI));
    auto [A2, ids] = zip(AI);
    Accumulate<ll> acc(A2);
    vector<ll> score(N);
    iota(ALL(score), 0);
    rep(i, N - 2, -1, -1) {
        ll cur = acc.query(0, i + 1);
        ll j = bisect_right(A2, cur, i) - 1;
        score[i] = score[j];
    }
    vector<ll> ans(N);
    rep(i, N) {
        ans[ids[i]] = score[i];
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
