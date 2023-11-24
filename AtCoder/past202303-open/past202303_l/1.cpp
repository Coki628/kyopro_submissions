/*
・きっちり自力AC！
・トポソ、辞書順最小
・辞書順最小のトポソは前にやったことがある。(ABC223_d)
　そのまま貼ればOK。
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

// トポロジカルソート(頂点数、辺集合(0-indexed))
vector<int> topological_sort(int N, vector<pii> edges) {

    // ここからトポロジカルソート準備
    vector<int> incnts(N);
    vvi outnodes(N);
    int M = edges.size();
    rep(i, M) {
        // 流入するノード数
        incnts[edges[i].second]++;
        // 流出先ノードのリスト
        outnodes[edges[i].first].pb(edges[i].second);
    }
    // 流入ノード数が0であるノードの集合S
    Set<int> S;
    rep(i, N) {
        if (incnts[i] == 0) {
            S.insert(i);
        }
    }
    // ここからトポロジカルソート
    vector<int> L;
    // 暫定セットが空になるまでループ
    while (S.size()) {
        // 暫定セットから結果リストへ1つ入れる
        L.pb(S.pop_front());
        // 確定させたノードから流出するノードでループ
        for (auto node : outnodes[L.back()]) {
            // 流入ノード数を1減らす
            incnts[node]--;
            // 流入ノードが0なら暫定セットへ
            if (incnts[node] == 0) {
                S.insert(node);
            }
        }
    }
    // 閉路があって正しくソート出来なかった場合
    if (L.size() != N) {
        return vector<int>();
    }
    // ソートされた頂点のリストを返却
    return L;
}

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pii> edges;
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges.eb(a, b);
    }

    auto res = topological_sort(N, edges);
    res++;
    print(res);
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
