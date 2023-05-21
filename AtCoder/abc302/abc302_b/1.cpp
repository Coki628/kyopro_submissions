/*
・筋肉実装。。
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
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    auto check = [grid, H, W](
        ll h1, ll h2, ll h3, ll h4, ll h5,
        ll w1, ll w2, ll w3, ll w4, ll w5
    ) {
        if (h1 >= H or h5 >= H or w1 >= W or w5 >= W) {
            return false;
        }
        return string{
            grid[h1][w1], grid[h2][w2], grid[h3][w3], grid[h4][w4], grid[h5][w5]
        } == "snuke";
    };

    ll h1, h2, h3, h4, h5, w1, w2, w3, w4, w5;
    vector<pll> ans(5);
    rep(h, H) {
        rep(w, W) {
            h1 = h;
            h2 = h + 1;
            h3 = h + 2;
            h4 = h + 3;
            h5 = h + 4;
            w1 = w2 = w3 = w4 = w5 = w;
            if (check(h1, h2, h3, h4, h5, w1, w2, w3, w4, w5)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                print(ans, '\n');
                return;
            }
            if (check(h5, h4, h3, h2, h1, w5, w4, w3, w2, w1)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                reverse(ALL(ans));
                print(ans, '\n');
                return;
            }
            w1 = w;
            w2 = w + 1;
            w3 = w + 2;
            w4 = w + 3;
            w5 = w + 4;
            h1 = h2 = h3 = h4 = h5 = h;
            if (check(h1, h2, h3, h4, h5, w1, w2, w3, w4, w5)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                print(ans, '\n');
                return;
            }
            if (check(h5, h4, h3, h2, h1, w5, w4, w3, w2, w1)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                reverse(ALL(ans));
                print(ans, '\n');
                return;
            }
            h1 = h;
            h2 = h + 1;
            h3 = h + 2;
            h4 = h + 3;
            h5 = h + 4;
            w1 = w;
            w2 = w + 1;
            w3 = w + 2;
            w4 = w + 3;
            w5 = w + 4;
            if (check(h1, h2, h3, h4, h5, w1, w2, w3, w4, w5)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                print(ans, '\n');
                return;
            }
            if (check(h5, h4, h3, h2, h1, w5, w4, w3, w2, w1)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                reverse(ALL(ans));
                print(ans, '\n');
                return;
            }
            h1 = h + 4;
            h2 = h + 3;
            h3 = h + 2;
            h4 = h + 1;
            h5 = h;
            w1 = w;
            w2 = w + 1;
            w3 = w + 2;
            w4 = w + 3;
            w5 = w + 4;
            if (check(h1, h2, h3, h4, h5, w1, w2, w3, w4, w5)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                print(ans, '\n');
                return;
            }
            if (check(h5, h4, h3, h2, h1, w5, w4, w3, w2, w1)) {
                ans[0] = {h1 + 1, w1 + 1};
                ans[1] = {h2 + 1, w2 + 1};
                ans[2] = {h3 + 1, w3 + 1};
                ans[3] = {h4 + 1, w4 + 1};
                ans[4] = {h5 + 1, w5 + 1};
                reverse(ALL(ans));
                print(ans, '\n');
                return;
            }
        }
    }
    assert(0);
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
