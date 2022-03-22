#pragma once
#include "../macros.hpp"
#include "../common/chmin.hpp"

// ※結局こっちのが使い勝手いいから残しておく。

// ダイクストラ
template<typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> &nodes, int src, int goal=-1) {

    int N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    res[src] = 0;
    que.push({0, src});

    while (!que.empty()) {
        auto [dist, u] = que.top(); que.pop();
        if (u == goal) return res;
        if (res[u] < dist) continue;
        for (auto [v, cost] : nodes[u]) {
            if (chmin(res[v], dist+cost)) {
                que.push({dist+cost, v});
            }
        }
    }
    return res;
}
