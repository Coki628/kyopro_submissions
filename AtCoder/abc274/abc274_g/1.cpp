/*
参考：https://atcoder.jp/contests/abc274/editorial
・自力全然ならず。燃やす埋めるだと言われても辺の張り方見えず。
・燃やす埋める、最大流、最小カット
・まず、考察して取りうる行動をよくシンプルにしていく必要がある。
　上向き、左向きのカメラを使う必要はないし、置く場所は、
　障害物(かグリッドの端)のすぐ下かすぐ右以外は考える必要がない。
　この辺はどう考えればいいかも公式解説に詳しく書いてある。
　で、ここまで状態を整えると、あるマスから見て、そのマスに向けられるカメラが
　上か左のどっちかには必ずないとダメ、みたいな制約をつけた燃やす埋めるになる。
　各マスが取れる選択肢は「そこにカメラを置く/置かない」で、
　これを下向きと右向きで必要なので2倍作る。
　両方同じ側の選択肢を禁止する制約になるので、片方は反転させる。
　後はフロー流せばOK。今回は利得最大化じゃなくコスト最小化なので、
　理屈が分かればそこからの辺の張り方・コストの振り方は難しくない。
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

#include "acl/maxflow.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll N = H*W*2 + 2;
    ll s = H*W*2;
    ll t = H*W*2 + 1;
    atcoder::mf_graph<ll> mf(N);
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') continue;
            ll x = gridtoid(h, w, W);
            ll y = H*W + x;
            // (h,w)に下向きのカメラを置く
            mf.add_edge(s, x, 1);
            // (h,w)に下向きのカメラを置かない
            mf.add_edge(x, t, 0);
            // (h,w)に右向きのカメラを置かない
            mf.add_edge(s, y, 0);
            // (h,w)に右向きのカメラを置く
            mf.add_edge(y, t, 1);
            ll gh = h, gw = w;
            while (gh > 0 and grid[gh-1][w] == '.') {
                gh--;
            }
            while (gw > 0 and grid[h][gw-1] == '.') {
                gw--;
            }
            ll gx = gridtoid(gh, w, W);
            ll gy = H*W + gridtoid(h, gw, W);
            // (gh,w),(h,gw)ともにカメラを置かないことを禁止
            mf.add_edge(gx, gy, INF);
        }
    }
    ll ans = mf.flow(s, t);
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
