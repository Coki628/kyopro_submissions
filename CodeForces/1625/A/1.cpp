/*
・きっちり自力AC！
・ビット毎に出現数をカウントして、多い方にしていく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, L;
    cin >> N >> L;
    auto A = LIST(N);

    vector<ll> C(L);
    rep(i, N) {
        rep(j, L) {
            if (A[i]>>j & 1) {
                C[j]++;
            }
        }
    }
    ll ans = 0;
    rep(i, L) {
        if (C[i] >= ceil(N, 2LL)) {
            ans += 1LL<<i;
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
