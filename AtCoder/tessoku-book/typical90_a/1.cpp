/*
・きっちり自力AC！
・最小値の最大化、にぶたん
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
    ll N, L;
    cin >> N >> L;
    ll K;
    cin >> K;
    vector<ll> A(N);
    cin >> A;

    vector<ll> B(N + 1);
    B[0] = A[0];
    rep(i, 1, N) {
        B[i] = A[i] - A[i - 1];
    }
    B[N] = L - A[N - 1];

    ll res = bisearch_max(0, INF, [&](ll x) {
        ll cur = 0, k = 0;
        rep(i, N + 1) {
            cur += B[i];
            if (cur >= x) {
                cur = 0;
                k++;
            }
        }
        if (cur < x) k--;
        return k >= K;
    });
    print(res);
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
