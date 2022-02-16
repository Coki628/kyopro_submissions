/*
・dojo set_d_3_5
・自力ならず。。自力はここまで。
・一晩考えて必死で考察して、「偶奇で分けて区間和が等しくなる所」
　ってことまでは分かったけど、それが高速化できず…。
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
    ll N;
    cin >> N;
    vector<ll> A1(N), A2(N);
    rep(i, N) {
        if (i%2 == 0) {
            cin >> A1[i];
        } else {
            cin >> A2[i];
        }
    }

    Accumulate<ll> acc1(A1), acc2(A2);
    ll ans = 0;
    rep(i, N) {
        rep(j, i+2, N+1) {
            if (acc1.query(i, j) == acc2.query(i, j)) {
                ans++;
            }
        }
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
