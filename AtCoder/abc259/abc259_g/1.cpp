/*
参考：TLのツイートとか
・最大流、燃やす埋める
・そう言われて考察すると見えるやつ。気付けるかが勝負…。
　もう、Gで制約ぬるめなやつ来たら全部疑ってかかるくらいでいいかもしれない。ｗ
・ある行/列を使う/使わないを選択する燃やす埋めるに帰着させる。
　行と列を自由に選ぶことができて選べばその行列の損益を取得できるが、
　ある行と列を同時に選ぶと、交差するマスの分は損をすると考える。
　このままだと追加コストの条件が、同じ側を選んだ時に掛かってしまうので、
　行か列どちらかの選択肢の左右を入れ替える。実装上は列を入れ替えた。
　制約の辺は、使う側に適用させたいので、
　使うのが右にある方から出て、左にある方に入るようにする。
・今回のやつで、ようやく制約の辺の使い方がまともに見えるようになったかもしれない。
　メモにも残したけど、条件の親側に来る方の項目が右(終点側)に来るようにする。
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
using namespace atcoder;

void solve() {
    ll H, W;
    cin >> H >> W;
    vvl grid(H);
    rep(i, H) grid[i] = LIST(W);

    vector<ll> rowsm(H), colsm(W);
    rep(h, H) {
        rep(w, W) {
            rowsm[h] += grid[h][w];
            colsm[w] += grid[h][w];
        }
    }

    ll N = H + W;
    ll s = N;
    ll t = N + 1;
    mf_graph<ll> mf(N+2);
    ll total = 0;
    rep(h, H) {
        if (rowsm[h] >= 0) {
            mf.add_edge(s, h, 0);
            mf.add_edge(h, t, rowsm[h]);
            total += rowsm[h];
        } else {
            mf.add_edge(s, h, -rowsm[h]);
            mf.add_edge(h, t, 0);
        }
    }
    rep(w, W) {
        if (colsm[w] >= 0) {
            mf.add_edge(H+w, t, 0);
            mf.add_edge(s, H+w, colsm[w]);
            total += colsm[w];
        } else {
            mf.add_edge(H+w, t, -colsm[w]);
            mf.add_edge(s, H+w, 0);
        }
    }
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] >= 0) {
                mf.add_edge(H+w, h, grid[h][w]);
            } else {
                mf.add_edge(H+w, h, INF);
            }
        }
    }
    auto res = mf.flow(s, t);
    ll ans = total - res;
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
