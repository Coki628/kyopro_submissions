/*
参考：https://atcoder.jp/contests/past202209-open/editorial/4834
・自力ならず。キーのアイデアが全く見えず。
・グリッド、deque
・2次元dequeみたいなことが高速にできればいいのだが、さっぱりだった。
　やり方は、H*Wが2*10^5あっても、これらのうち小さい方は必ず√2*10^5以下くらいになるので、
　このことを利用する。総和と種類数で√に落とすテクみたいな感じに考える。
　さて、ここに気付けば、後は小さい側を愚直シミュ、大きい側をdequeで処理するだけ。
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

#include "grid/transpose.hpp"

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;
    vector<string> grid(H);
    cin >> grid;

    bool swapped = false;
    if (H > W) {
        swapped = true;
        swap(H, W);
        grid = transpose(grid);
    }
    vector<deque<char>> que(H);
    rep(h, H) {
        rep(w, W) {
            que[h].eb(grid[h][w]);
        }
    }
    string S;
    rep(i, Q) {
        ll op, p;
        char c;
        cin >> op >> p >> c;
        p--;
        if (swapped) {
            op = 3 - op;
        }
        if (op == 1) {
            S += que[p].back();
            que[p].pop_back();
            que[p].push_front(c);
        } else {
            S += que[H - 1][p];
            rep(h, H - 1, 0, -1) {
                que[h][p] = que[h - 1][p];
            }
            que[0][p] = c;
        }
    }
    print(S);
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
