#include "../base.hpp"

// 部分永続UF
struct PartiallyPersistentUnionFind {

    int n;
    vector<int> par, last;
    vector<vector<pair<int, int>>> history;

    PartiallyPersistentUnionFind(int n) : n(n) {
        // xが根のときはxを含むグループのサイズ(の-1倍)、そうでないときは親ノード
        par.resize(n, -1);
        // 最後に「根」ではなくなった瞬間の時刻
        last.resize(n, -1);
        history.resize(n);
        for (auto &vec : history) vec.emplace_back(-1, -1);
    }

    PartiallyPersistentUnionFind() {}

    // 根の検索(グループ番号)
    int find(int t, int x) {
        // 根ならその番号を返す
        if (last[x] == -1 || t < last[x]) {
            return x;
        } else {
            return find(t, par[x]);
        }
    }

    // 時刻tにa,bを併合
    bool merge(int t, int a, int b) {
        // 根を探す
        int x = find(t, a);
        int y = find(t, b);
        if (x == y) {
            return false;
        }
        // 要素数の少ない方を付け替える(マージテク)
        if (par[x] > par[y]) {
            swap(x, y);
        }
        // xにyを付ける
        par[x] += par[y];
        par[y] = x;
        last[y] = t;
        history[x].emplace_back(t, par[x]);
        return true;
    }

    // 時刻tに同じ集合に属するか判定
    bool same(int t, int a, int b) {
        return find(t, a) == find(t, b);
    }

    // 時刻tに頂点xを含む連結成分のサイズ
    int size(int t, int x) {
        x = find(t, x);
        return -prev(lower_bound(history[x].begin(), history[x].end(), make_pair(t, 0)))->second;
    }
};
