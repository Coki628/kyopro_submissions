#include "../macros.hpp"

// 重み付きUF
template<typename T>
struct WeightedUnionFind {

    int n;
    vector<int> par, rank;
    vector<T> weight;
    
    WeightedUnionFind(int n) : n(n) {
        par.resize(n);
        rank.resize(n);
        // 根への距離を管理
        weight.resize(n);
        rep(i, n) par[i] = i;
    }

    // 検索
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            int y = find(par[x]);
            // 親への重みを追加しながら根まで走査
            weight[x] += weight[par[x]];
            par[x] = y;
            return y;
        }
    }

    // 併合
    int merge(int x, int y, ll w) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return rx;

        // xの木の高さ < yの木の高さ
        if (rank[rx] < rank[ry]) {
            par[rx] = ry;
            weight[rx] = w - weight[x] + weight[y];
            return ry;
        } else {
            par[ry] = rx;
            weight[ry] = - w - weight[y] + weight[x];
            // 木の高さが同じだった場合の処理
            if (rank[rx] == rank[ry]) {
                rank[rx]++;
            }
            return rx;
        }
    }

    // 同じ集合に属するか
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // xからyへのコスト
    T diff(int x, int y) {
        assert(same(x, y));
        return weight[x] - weight[y];
    }
};
