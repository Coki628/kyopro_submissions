#include "../macros.hpp"

// トポロジカルソート(頂点数、辺集合(0-indexed)) 
vector<int> topological_sort(int N, vector<pll> edges) {

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
    vector<int> S;
    rep(i, N) {
        if (incnts[i] == 0) {
            S.eb(i);
        }
    }
    // ここからトポロジカルソート
    vector<int> L;
    // 暫定セットが空になるまでループ
    while (S.size()) {
        // 暫定セットから結果リストへ1つ入れる
        L.pb(S.back()); S.pop_back();
        // 確定させたノードから流出するノードでループ
        for (auto node : outnodes[L.back()]) {
            // 流入ノード数を1減らす
            incnts[node]--;
            // 流入ノードが0なら暫定セットへ
            if (incnts[node] == 0) {
                S.eb(node);
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
