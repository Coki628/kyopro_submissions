/*
・Div.3残埋め
・なんとか自力AC！G通してから戻ってきて再考したら解けた。
・グリッド、操作の復元、グラフに帰着、トポソ
・制約は小さめだけど、グリッドの全状態を持ったりできる程じゃない。
　どうにかできないか考える。市松とかを想定すると、
　思ったより操作回数もかなりできてしまいそうだ。ここで結構詰まった。
　でもよく考えていくと、この操作は元の状態に戻ったりはできなそうで、
　しかも変化させたマスが影響して隣が操作できるようになったり、
　そういう複雑な状況が起こらなそうなことが見えてきた。
　(隣同士を操作しようとしたりを手元で試すと分かる。)
　他の操作の影響で操作できるマスに変化がないのであれば、
　全ペアについて独立に見て、状態遷移させられる所だけに辺を張り、
　トポソすれば正しい順序が作れそう。
　なお同じ盤面だけ、ループにならないように工夫しておく。
　後は遷移可否チェックの時に操作もメモっといたりの実装面をやって、
　最後にトポソ順に見ていって必要な操作を答えていけばOK。
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

#include "graph/topological_sort.hpp"

void solve() {
    ll H, W, K;
    cin >> H >> W >> K;
    vv<string> grid(K + 1);
    rep(i, K + 1) {
        grid[i].resize(H);
        rep(h, H) {
            cin >> grid[i][h];
        }
    }

    vector<pii> cur;
    auto check = [&](const vector<string> &grid1, const vector<string> &grid2) {
        rep(h, H) {
            rep(w, W) {
                if (grid1[h][w] != grid2[h][w]) {
                    for (auto [dh, dw] : dir4) {
                        ll nh = h + dh, nw = w + dw;
                        if (nh < 0 or nw < 0 or nh >= H or nw >= W) {
                            return false;
                        }
                        if (grid1[h][w] == grid2[nh][nw]) {
                            return false;
                        }
                    }
                    cur.eb(h, w);
                }
            }
        }
        return true;
    };
    auto ops = listnd(K + 1, K + 1, vector<pii>());
    vector<pii> edges;
    rep(i, K + 1) {
        rep(j, K + 1) {
            // 同型は i < j だけにしておく
            if (grid[i] == grid[j] and i >= j) continue;
            if (check(grid[i], grid[j])) {
                ops[i][j] = cur;
                edges.eb(i, j);
            } else {
                ops[i][j] = {{-1, -1}};
            }
            cur.clear();
        }
    }

    auto res = topological_sort(K + 1, edges);
    assert(res.size());
    vvl ans;
    rep(i, K) {
        ll u = res[i];
        ll v = res[i + 1];
        assert(ops[u][v].empty() or ops[u][v][0].first != -1);
        for (auto& [h, w] : ops[u][v]) {
            ans.pb({1, h + 1, w + 1});
        }
        ans.pb({2, v + 1});
    }
    print(res[0] + 1);
    print(ans.size());
    print(ans, "\n");
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
