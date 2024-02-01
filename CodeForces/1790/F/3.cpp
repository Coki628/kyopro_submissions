/*
参考：https://twitter.com/kude_coder/status/1619018749037928448
　　　https://codeforces.com/contest/1790/submission/190841094
・自力ならず。この解法はくでさんを参考に。
・木グラフ、最短距離、クエリ平方分割、多点スタートBFS
・操作√N回に一度、全体に向かってBFSして最短距離を更新、
　同じブロック内は毎回全ペアを愚直にチェックして更新する。
　これだと全ペアで2乗がかかってしまって無理そうな気がしたんだけど、
　√Nの2乗だからそこはNで、そういうブロックが√N個なので、
　全体でもN^1.5、つまりO(N√N)に収まる。
　実際にはここに最短距離を求める時のLCA取得のlogが乗ってしまっているのできつい。
　(LCAは線形のやつもあるらしいけど…。)
　制約4秒なのでまあ間に合ったけど。(AC2.53秒)
・線形LCAを作ってみた。速度はほとんど変わらなくて2.37秒。。
　ボトルネックは√N回BFSの方なんかなぁ。
　でもSparse Tableを2Nで作るから心配だったメモリはそれほどでもなくて、
　40MB -> 114MB 程度だったから、普通のグラフ問題なら問題なく使えそう。
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

#include "graph/LowestCommonAncestor.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<int> C(N);
    cin >> C;
    C--;
    vector<ll> inv(N);
    rep(i, N) {
        inv[C[i]] = i;
    }
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    LowestCommonAncestor lca(nodes);
    ll D = ceil(sqrt(N));
    vector<int> src = {C[0]};
    vector<ll> dist(N, INF);
    auto bfs = [&]() {
        queue<int> que;
        for (int s : src) {
            dist[s] = 0;
            que.push(s);
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto v : nodes[u]) {
                if (chmin(dist[v], dist[u] + 1)) {
                    que.push(v);
                }
            }
        }
        // 今回使った始点を削除
        src.clear();
    };
    bfs();
    vector<ll> ans;
    ll cur = INF;
    rep(i, 1, N) {
        // ここまでの√N個の頂点を始点として多点スタートBFSする
        if (i % D == 0) {
            bfs();
        }
        ll u = C[i];
        chmin(cur, dist[u]);
        // 同じブロックは毎回全ペアを確認
        for (auto v : src) {
            chmin(cur, (ll)lca.dist(u, v));
        }
        src.eb(u);
        ans.eb(cur);
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
