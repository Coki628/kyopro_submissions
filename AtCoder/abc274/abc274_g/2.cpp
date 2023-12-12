/*
ライブラリ整備：燃やす埋める
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

#include "graph/PSP.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll N = H * W;
    PSP psp(N * 2, false);
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') continue;
            ll x = gridtoid(h, w, W);
            ll y = N + x;
            // (h,w)に下向きのカメラを置く/置かない
            psp.add(x, 1, 0);
            // (h,w)に右向きのカメラを置かない/置く
            psp.add(y, 0, 1);
            ll gh = h, gw = w;
            while (gh > 0 and grid[gh - 1][w] == '.') {
                gh--;
            }
            while (gw > 0 and grid[h][gw - 1] == '.') {
                gw--;
            }
            ll gx = gridtoid(gh, w, W);
            ll gy = N + gridtoid(h, gw, W);
            // (gh,w),(h,gw)ともにカメラを置かないことを禁止(gxに置かないならgyに置く)
            psp.a_right_then_b_right(gx, gy);
        }
    }
    ll ans = psp.solve();
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
