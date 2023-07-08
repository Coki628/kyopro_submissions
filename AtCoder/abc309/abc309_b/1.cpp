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
    vector<string> grid(N);
    cin >> grid;

    auto ans = grid;
    rep(w, N - 1) {
        ans[0][w + 1] = grid[0][w];
    }
    rep(h, N - 1) {
        ans[h + 1][N - 1] = grid[h][N - 1];
    }
    rep(w, N - 1, 0, -1) {
        ans[N - 1][w - 1] = grid[N - 1][w];
    }
    rep(h, N - 1, 0, -1) {
        ans[h - 1][0] = grid[h][0];
    }
    print(ans, '\n');
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
