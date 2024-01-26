/*
・Div.3残埋め
・長い戦いだった…。
・三角形の2次元累積和
・とりあえず、うまく三角形領域を切り取るために頑張る。
　最終的に、基準点が左上にある方がその後の色々がやりやすく思えたので、
　左上、右上、左下の3点をとる三角形の累積和にした。
　これの左下の点を取れば、一番上からの累積になる。
　で、右上の点を引けば、そこより右上からの累積は取り除ける。
　左上に長方形領域が引けないで残るので、
　これは普通の2次元累積和を別途作っておいてそれを使って引く。
　あと、累積和の形を変えるのは面倒なのでグリッドを回転させて対応する。
・H,W間違えたみたいなしょうもないバグは埋め込んだものの、
　基本的にはこの方針で通る。なんだけど、実装を楽にするために、
　番兵としてグリッドを2K広く取ってたらMLE。。
　制約上、10^5*1グリッドでK=1000みたいのができてしまうので、
　これが10^5*2000みたいな巨大グリッドを作ってしまう。
　intにしたりboolにしたり、K片側だけでよくしたり、
　色々メモリ減らせないか試行錯誤したけど、結局そのままだと無理で、
　グリッドは広げずに、はみ出した部分に対して適切な対処を考慮することになった。
　これはソース内コメントにも書いたけど、
　縦のはみ出しは三角形の左下先端をはみ出さないように右にずらす。
　で、そうなると先端左上に、足せてない長方形領域が発生するので、
　これは別途また普通の累積和の方で足す。これを適切にやったら通った。
　なお、横のはみ出しは、単にWを最大に制限すれば、
　0を取ってくるだけなので問題ない(と思ってる)。
・でもこれは番兵生やして楽するのでも通って欲しかったよなー。
　めんどい終端処理を適切に省略するための手段なのに、
　それを封じてめんどい終端処理を敢えてやれってのは本質じゃなく思えるよ。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "grid/flip.hpp"
#include "datastructure/Accumulate2D.hpp"

// 472##.#..###.#....#..##.#....##

void solve(int t) {
    int H, W, K;
    cin >> H >> W >> K;
    K++;
    vector<string> grid(H);
    cin >> grid;

    // if (t == 134) {
    //     cout << H << W << --K;
    //     rep(h, H) {
    //         rep(w, W) {
    //             cout << grid[h][w];
    //         }
    //     }
    //     cout << endl;
    //     return;
    // }

    auto check = [&](const vector<string> &grid) -> int {
        int H = grid.size();
        int W = grid[0].size();
        Accumulate2D<int> acc(H, W);
        auto acc2 = listnd(H + 1, W + 1, 0);
        rep(h, H) {
            rep(w, W) {
                if (grid[h][w] == '#') {
                    acc.set(h, w, 1);
                    acc2[h + 1][w] = 1;
                }
            }
        }
        acc.build();
        rep(h, H) {
            rep(w, W + 1) {
                acc2[h + 1][w] += acc2[h][w];
            }
        }
        // 左上 → 右下
        rep(h, H) {
            rep(w, W, 0, -1) {
                acc2[h + 1][w - 1] += acc2[h][w];
            }
        }

        int res = 0;
        rep(h, H) {
            int hk = min((int)h + K, H);
            // H側へのはみ出し
            int x = (h + K) - hk;
            rep(w, W) {
                int wk = min((int)w + K, W);
                // 縦にはみ出した分、三角形の先端が右にずれる
                int wx = min((int)w + x, W);
                // 三角形(左下) - 三角形(右上) - 長方形(左上)
                int cur = acc2[hk][wx] - acc2[h][wk] - acc.query(0, wx, h, wk);
                // 先端がずれた分、先端の左側で長方形になった部分を足す
                cur += acc.query(h, w, hk, wx);
                chmax(res, cur);
            }
        }
        return res;
    };
    int ans = 0;
    chmax(ans, check(grid));
    grid = flip_h(grid);
    chmax(ans, check(grid));
    grid = flip_w(grid);
    chmax(ans, check(grid));
    grid = flip_h(grid);
    chmax(ans, check(grid));
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
    rep(t, T) solve(t);

    return 0;
}
