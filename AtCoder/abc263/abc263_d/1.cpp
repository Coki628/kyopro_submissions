/*
・なんとか自力AC！
・差分取って前後から累積和して累積minして全箇所見る。結構むずくないか…。
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
    ll N, L, R;
    cin >> N >> L >> R;
    auto A = LIST(N);

    vector<ll> D1(N), D2(N);
    rep(i, N) {
        D1[i] = L - A[i];
        D2[i] = R - A[i];
    }
    auto accd1 = D1;
    rep(i, N-1) {
        accd1[i+1] += accd1[i];
    }
    auto accd2 = D2;
    rep(i, N-2, -1, -1) {
        accd2[i] += accd2[i+1];
    }
    auto lmn = accd1;
    rep(i, N-1) {
        chmin(lmn[i+1], lmn[i]);
    }
    lmn.insert(lmn.begin(), 0);
    auto rmn = accd2;
    rep(i, N-2, -1, -1) {
        chmin(rmn[i], rmn[i+1]);
    }
    rmn.eb(0);
    ll sub = 0;
    rep(i, N+1) {
        chmin(sub, lmn[i]+rmn[i]);
    }
    ll ans = sum(A) + sub;
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
