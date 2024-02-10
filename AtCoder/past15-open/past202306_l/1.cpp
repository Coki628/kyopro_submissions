/*
・なんとか自力AC！
・グリッド、XOR、行更新、列更新、ビット毎に見る
・まず、自由マスが1つでもあれば、適当にこねくり回して
　だいたい何とかなるんじゃないかっていう雑な予測が立つ。
　PASTは提出のペナとかないので、
　assert使ってこの予測が正しいか確認。合ってた。
　これで少しは考えることが減ってラクになる。
　次にXORなので、ビット毎に独立に可否を判定した方が
　見通しが良さそうだと思う。実際これも合ってた。
　さて、この先だいぶ右往左往するんだけど、最終的に、
　結局雑に言うと「なるようにしかならない」んじゃないかと思う。
　で、両方のグリッドで差分取って変更する必要のある場所を可視化した後、
　これをまず1行目だけ揃えるために各列を必要に応じて反転、
　2行目以降はそのままOKか行反転でOK以外は全部ダメ、
　としたらこれが当たって、無事AC。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    auto grid1 = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            cin >> grid1[h][w];
        }
    }
    auto grid2 = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            cin >> grid2[h][w];
        }
    }

    rep(h, H) {
        rep(w, W) {
            if (grid2[h][w] == -1) {
                Yes();
                return;
            }
        }
    }

    rep(b, 30) {
        auto diff = listnd(H, W, 0);
        rep(h, H) {
            rep(w, W) {
                int cur1 = grid1[h][w] >> b & 1;
                int cur2 = grid2[h][w] >> b & 1;
                diff[h][w] = cur1 != cur2;
            }
        }
        vector<int> revw(W);
        rep(w, W) {
            if (diff[0][w]) {
                revw[w] = true;
            }
        }
        rep(h, 1, H) {
            ll diffcnt = 0;
            rep(w, W) {
                if (diff[h][w] ^ revw[w]) diffcnt++;
            }
            if (diffcnt != 0 and diffcnt != W) {
                No();
                return;
            }
        }
    }
    Yes();
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
