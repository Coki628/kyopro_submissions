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
    string S;
    cin >> S;
    ll N = S.size();
    vector<ll> vec;
    rep(i, N) {
        if (S[i] == 'B') {
            vec.eb(i);
        }
    }
    bool ok1 = (vec[0] % 2) != (vec[1] % 2);
    vec.clear();
    ll ki = -1;
    rep(i, N) {
        if (S[i] == 'R') {
            vec.eb(i);
        } else if (S[i] == 'K') {
            ki = i;
        }
    }
    bool ok2 = vec[0] < ki and ki < vec[1];
    if (ok1 and ok2) {
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
