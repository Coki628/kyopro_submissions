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
    ll R, N, M, L;
    cin >> R >> N >> M >> L;
    vector<ll> A(L);
    cin >> A;

    ll r = 0, n = 0, m = 0;
    for (auto a : A) {
        n += a;
        if (n > N) {
            No();
            return;
        } else if (n == N) {
            r++;
            n = 0;
            m = 0;
        } else {
            m++;
            if (m == M) {
                r++;
                n = 0;
                m = 0;
            }
        }
    }
    if (r == R and m == 0) {
        Yes();
    } else {
        No();
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
