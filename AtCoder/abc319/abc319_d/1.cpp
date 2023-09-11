/*
・決め打ちにぶたん
・にぶたん。max(L)>xを別処理しておらず1WA。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> L(N);
    cin >> L;

    ll ans = bisearch_min(0, INF, [&](ll x) {
        if (max(L) > x) {
            return false;
        }
        ll rowcnt = 1, curcol = L[0] + 1;
        rep(i, 1, N) {
            if (curcol + L[i] <= x) {
                curcol += L[i];
            } else {
                rowcnt++;
                curcol = L[i];
            }
            curcol++;
        }
        return rowcnt <= M;
    });
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
