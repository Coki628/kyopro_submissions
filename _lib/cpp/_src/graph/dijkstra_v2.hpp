#include "../macros.hpp"

// ダイクストラ(O(V^2)版) ※未verify
template<typename T>
vector<T> dijkstra(const vector<vector<T>> &G, int src) {
    int N = G.size();
    vector<T> dist(N, INF);
    vector<bool> used(N);

    dist[src] = 0;
    while (1) {
        int v = -1;
        rep(u, N) {
            if (!used[u] and (v == -1 or dist[u] < dist[v])) {
                v = u;
            }
        }
        if (v == -1) {
            break;
        }
        used[v] = true;
        rep(u, N) {
            dist[u] = min(dist[u], dist[v] + G[v][u]);
        }
    }
    return dist;
}
