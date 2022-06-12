/*
参考：TLのキーワード
・自力ならず。。
・最遠点、座標変換、45度回転
・これ45度回転見えなかったのは悔しいな…。
　絶対こういうのどっかでやったことあるって思ったのに出なかった。。
　(実際、これで最遠点みたいのを求めるのはABC178eとかtypical90_036でやってた)
・変換したU,V座標で最も遠い2点の中間を取ると、
　それを式変形でまたx,y座標に戻せば、どこに置くのが最適か分かる。
　実際は整数にならなかったりするので、周囲何マスか雑に探索入れるのが楽。
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
    rep(i, H) cin >> grid[i];

    vector<ll> U, V;
    vector<pll> HW;
    rep(i, H) {
        rep(j, W) {
            if (grid[i][j] == 'B') {
                U.eb(i+j);
                V.eb(i-j);
                HW.eb(i, j);
            }
        }
    }
    sort(ALL(U));
    sort(ALL(V));
    ld u = (U[0]+U.back()) / 2.0;
    ld v = (V[0]+V.back()) / 2.0;
    ll h = round((u+v) / 2);
    ll w = round((u-v) / 2);
    auto check = [&](ll h, ll w) {
        ll mx = 0;
        for (auto [ch, cw] : HW) {
            chmax(mx, abs(h-ch)+abs(w-cw));
        }
        return mx;
    };
    ll mn = INF;
    pll ans;
    rep(i, max(h-2, 0LL), min(h+2, H)) {
        rep(j, max(w-2, 0LL), min(w+2, W)) {
            if (chmin(mn, check(i, j))) {
                ans = {i+1, j+1};
            }
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
