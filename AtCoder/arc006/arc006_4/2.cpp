/*
・ライブラリ整備：2次元ロリハ
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

#include "grid/rot90.hpp"
#include "grid/scale.hpp"
#include "string/RollingHash2D.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    vector<string> targets[3];
    targets[0] = {
        ".......",
        "...o...",
        "..o.o..",
        ".o...o.",
        ".ooooo.",
        ".o...o.",
        ".......",
    };
    targets[1] = {
        ".......",
        ".oooo..",
        ".o...o.",
        ".oooo..",
        ".o...o.",
        ".oooo..",
        ".......",
    };
    targets[2] = {
        ".......",
        "..ooo..",
        ".o...o.",
        ".o.....",
        ".o...o.",
        "..ooo..",
        ".......",
    };

    auto used = listnd(H, W, 0);
    vector<ll> V;
    rep(i, H) {
        rep(j, W) {
            if (used[i][j]) continue;
            if (grid[i][j] == 'o') {
                ll ni = i, nj = j;
                while (grid[i][nj] == 'o' and grid[ni][j] == 'o' and grid[ni][nj] == 'o') {
                    ni++, nj++;
                }
                V.eb(ni - i);
                rep(h, i, ni) {
                    rep(w, j, nj) {
                        used[h][w] = true;
                    }
                }
            }
        }
    }
    UNIQUE(V);

    RollingHash2D rh2d;
    set<uint64_t> se[3];
    for (ll n : V) {
        rep(i, 3) {
            auto scaled = scale(targets[i], n);
            rep(_, 4) {
                auto target = rh2d.get_hash(scaled);
                se[i].insert(target);
                scaled = rot90(scaled);
            }
        }
        n++;
    }

    vector<ll> ans(3);
    for (ll n : V) {
        ll R = n * 7, C = n * 7;
        auto hashs = rh2d.get_hashs(grid, R, C);
        rep(h, H - R + 1) {
            rep(w, W - C + 1) {
                rep(i, 3) {
                    if (se[i].count(hashs[h][w])) {
                        ans[i]++;
                    }
                }
            }
        }
        n++;
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
