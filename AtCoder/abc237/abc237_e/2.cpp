/*
参考：https://www.youtube.com/watch?v=sntAcA4Jbwo
　　　https://atcoder.jp/contests/abc237/editorial
・後日after_contestケースに対応してupsolveした。
・ダイクストラ、負辺除去、ポテンシャル
・すぬけさんが公式動画でポテンシャルについて詳しく解説してくれてる。
　新しい辺コスト = 元の辺コスト (from頂点のポテンシャル - to頂点のポテンシャル)
　という式で新しい辺コストを割り当てて、負辺のないグラフを作る。
　そうなるような適切なポテンシャルを定める。これは負閉路がないグラフであれば可能。
　2乗OKな制約であれば、ベルマンフォードである頂点からの最短路を求めれば、
　それがそのまま使えるとのこと。それが無理なら何かしら工夫するしかない。
　今回で言えば、頂点の高さHがちょうどそのまま使える。
・今までフローとかで一律に下駄履かせるのはやったことあったけど、
　それは通る調整した辺の数が可変だと壊れると思ったので、
　今回みたいな場合にどうやるのかは分からなかった。
　ぱっと聞いた時は今回の個々にポテンシャルを設定する方法で何でうまくいくのか分からなかったが、
　つまりこのポテンシャルの使い方だと、途中に通った辺の分のポテンシャルは全て相殺されるので、
　結果的に始点と終点のポテンシャルの足し引きだけやればいい状態が作れるってことだった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "graph/_dijkstra.hpp"

// 適切なポテンシャルPを使って負辺を除去する
vector<tuple<int, int, ll>> remove_negative_edges(vector<tuple<int, int, ll>>& edges, vector<ll>& P) {
    vector<tuple<int, int, ll>> res;
    for (auto [u, v, c] : edges) {
        ll nc = c+P[u]-P[v];
        assert(nc >= 0);
        res.eb(u, v, nc);
    }
    return res;
}

void solve() {
    ll N, M;
    cin >> N >> M;
    auto H = LIST(N);
    vector<tuple<int, int, ll>> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        if (H[u] <= H[v]) {
            edges.eb(u, v, (H[v]-H[u])*2);
            edges.eb(v, u, -(H[v]-H[u]));
        } else {
            edges.eb(u, v, -(H[u]-H[v]));
            edges.eb(v, u, (H[u]-H[v])*2);
        }
    }

    vvpll nodes(N);
    auto edges2 = remove_negative_edges(edges, H);
    for (auto [u, v, c] : edges2) {
        nodes[u].eb(v, c);
    }
    ll s = 0;
    auto res = dijkstra(nodes, s);
    ll ans = -INF;
    rep(t, N) {
        chmax(ans, -(res[t]-(H[s]-H[t])));
    }
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
