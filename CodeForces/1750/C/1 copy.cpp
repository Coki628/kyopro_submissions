/*
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
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    ll cnt1 = count(ALL(S), '0');
    ll cnt2 = count(ALL(S), '0');
    if (cnt1 != cnt2) {
        NO();
        return;
    }

    vector<pll> ans;
    vector<bool> done(N);
    ll p = 0;
    rep(i, N) {
        if (((S[i] == T[i]) ^ p) and (S[i] == '1')) {
            ans.eb(i+1, N);
            p = p - 1;
            done[i] = 1;
        }
    }
    if (p) {
        rep(i, N) {
            T[i] = T[i] == '0' ? '1' : '0';
        }
    }
    rep(i, N) {
        if (done[i]) continue;
        if (S[i] != T[i]) {

        }
    }
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
