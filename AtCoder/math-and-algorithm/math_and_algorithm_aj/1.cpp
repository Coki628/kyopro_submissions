/*
・いもす
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;

    vector<ll> imos(N+1);
    rep(i, Q) {
        ll l, r, x;
        cin >> l >> r >> x;
        l--;
        imos[l] += x;
        imos[r] -= x;
    }

    rep(i, N) {
        imos[i+1] += imos[i];
    }
    string ans;
    rep(i, N-1) {
        if (imos[i] < imos[i+1]) {
            ans += '<';
        } elif (imos[i] > imos[i+1]) {
            ans += '>';
        } else {
            ans += '=';
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
