/*
・きっちり自力AC！
・結局、最短距離で目指すのが最善。前後から差分取って累積和。
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
    auto A = LIST(N);

    vector<ll> B1(N-1), B2(N-1);
    rep(i, N-1) {
        B1[i] = max(A[i]-A[i+1], 0LL);
        B2[i] = max(A[i+1]-A[i], 0LL);
    }
    Accumulate<ll> acc1(B1), acc2(B2);
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        if (a < b) {
            ll res = acc1.query(a, b);
            print(res);
        } elif (a > b) {
            ll res = acc2.query(b, a);
            print(res);
        } else {
            assert(0);
        }
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
