/*
・プレテスがギリ通ったけどシステスTLE…。
・2次元セグ木、二分探索
・グリッドのマス数が100万で、log3つも乗るからまあ無理だろなぁとは思ったんだけどね…。
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

#include "datastructure/SegmentTree2D.hpp"

void solve() {
    int H, W;
    cin >> H >> W;
    auto grid = listnd(H, W, 0);
    cin >> grid;

    auto seg = get_segment_tree_2d(
        grid, [](int a, int b) { return min(a, b); }, MOD);
    int ans = 0;
    int N = min(H, W);
    rep(sh, H) {
        rep(sw, W) {
            int res = bisearch_max(1, N + 1, [&](int x) {
                int th = sh + x;
                int tw = sw + x;
                if (th > H or tw > W) {
                    return false;
                }
                int res = seg.query(sh, sw, th, tw);
                return res >= x;
            });
            chmax(ans, res);
        }
    }
    print(ans);
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
