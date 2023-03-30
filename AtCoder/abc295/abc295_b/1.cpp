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
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    auto dist = [](ll i, ll j, ll ii, ll jj) {
        return abs(i - ii) + abs(j - jj);
    };

    auto ans = grid;
    rep(i, H) {
        rep(j, W) {
            if (grid[i][j] != '.' and grid[i][j] != '#') {
                ll len = toint(grid[i][j]);
                rep(ii, H) {
                    rep(jj, W) {
                        if (dist(i, j, ii, jj) <= len) {
                            ans[ii][jj] = '.';
                        }
                    }
                }
            }
        }
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
