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
    ll N;
    cin >> N;
    string S;
    cin >> S;

    const vector<pii> D = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    ll x = 0, y = 0, d = 0;
    rep(i, N) {
        if (S[i] == 'S') {
            auto [dx, dy] = D[d];
            x += dx;
            y += dy;
        } else {
            d = (d+1)%4;
        }
    }
    print(mkp(x, y));
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
