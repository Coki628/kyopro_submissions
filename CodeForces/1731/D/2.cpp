/*
参考：https://twitter.com/298slider/status/1607777241618067458
・なんと同じ方針で通してる人がいたので。
・2次元セグ木、二分探索
・左上固定全探索のにぶたんでなくて、判定内でグリッドのループ回すと通った…。TL2秒で1.05秒。
　普段判定の内側が重い方が遅いことが多い気がするので、これのが速いのはなんか意外。
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
    int N = min(H, W);
    int ans = bisearch_max(1, N + 1, [&](int x) {
        rep(sh, H) {
            int th = sh + x;
            if (th > H) break;
            rep(sw, W) {
                int tw = sw + x;
                if (tw > W) break;
                int res = seg.query(sh, sw, th, tw);
                if (res >= x) {
                    return true;
                }
            }
        }
        return false;
    });
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
