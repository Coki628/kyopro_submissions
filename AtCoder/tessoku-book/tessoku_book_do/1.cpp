/*
・きっちり自力AC！
・絶対値、正負4通り全探索
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
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    ll ans = 0;
    rep(aop, 2) {
        rep(bop, 2) {
            ll acoef = aop ? 1 : -1;
            ll bcoef = bop ? 1 : -1;
            ll cura = 0, curb = 0;
            rep(i, N) {
                ll contrib = A[i] * acoef + B[i] * bcoef;
                if (contrib > 0) {
                    cura += A[i];
                    curb += B[i];
                }
            }
            chmax(ans, abs(cura) + abs(curb));
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
