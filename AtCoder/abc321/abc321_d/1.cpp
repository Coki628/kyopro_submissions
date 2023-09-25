/*
・きっちり自力AC！
・ソートしてにぶたん
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
    ll N, M, P;
    cin >> N >> M >> P;
    vector<ll> A(N), B(M);
    cin >> A >> B;

    sort(ALL(A));
    sort(ALL(B));
    Accumulate<ll> acc(B);
    ll ans = 0;
    rep(i, N) {
        ll j = bisect_left(B, P - A[i]);
        ll pcnt = M - j;
        ans += pcnt * P + acc.query(0, j) + j * A[i];
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
