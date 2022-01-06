#include "../macros.hpp"
#include "_dijkstra.hpp"

// ダイクストラ(クラス版、復元付き、コスト演算設定可)
template<typename T, typename E, typename F>
struct Dijkstra {

    int N;
    const T inf;
    vector<vector<pair<int, E>>> nodes;
    const F f;
    vector<int> prv;

    Dijkstra(const vector<vector<pair<int, E>>> &nodes, T inf, F f) :
        nodes(nodes),
        inf(inf),
        f(f),
        N(nodes.size()) {}

    vector<T> solve(const vector<int> &src, int goal=-1, T init=T(), bool restore=false) {
        vector<T> res(N, inf);
        if (restore) prv.assign(N, -1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
        for (int s : src) {
            res[s] = init;
            que.push({init, s});
        }
        while (que.size()) {
            auto [dist, u] = que.top(); que.pop();
            if (u == goal) return res;
            if (res[u] < dist) continue;
            for (auto [v, cost] : nodes[u]) {
                T nxtdist = f(dist, cost);
                if (nxtdist < res[v]) {
                    res[v] = nxtdist;
                    if (restore) prv[v] = u;
                    que.push({nxtdist, v});
                }
            }
        }
        return res;
    }

    // s からの最短経路
    vector<T> solve(int s, int goal=-1, T init=T(), bool restore=false) {
        return solve(vector<int>({s}), goal, init, restore);
    }

    // s -> t 間の経路を取得
    vector<int> get_route(int s, int t) {
        vector<int> res = {t};
        while (t != s) {
            t = prv[t];
            if (t == -1) {
                return vector<int>();
            }
            res.eb(t);
        }
        reverse(ALL(res));
        return res;
    }
};

template<typename T=ll, typename E=ll, typename F=function<T(T, E)>>
Dijkstra<T, E, F> get_dijkstra(
    vector<vector<pair<int, E>>> &nodes,
    T inf=INF,
    const F f=[](T a, E b) -> T { return a + b; }
) {
    return {nodes, inf, f};
}
