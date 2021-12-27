#include "../macros.hpp"

struct UnionFind {

    int n, groupcnt;
    vector<int> par, rank, sz;
    vector<bool> tree;

    UnionFind(int n) : n(n) {
        par.assign(n, 0);
        rank.assign(n, 0);
        sz.assign(n, 1);
        tree.assign(n, true);
        rep(i, n) par[i] = i;
        groupcnt = n;
    }

    UnionFind() {}

    void resize(int _n) {
        n = _n;
        par.assign(n, 0);
        rank.assign(n, 0);
        sz.assign(n, 1);
        tree.assign(n, true);
        rep(i, n) par[i] = i;
        groupcnt = n;
    }

    // 根の検索(グループ番号)
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            par[x] = find(par[x]);
            return par[x];
        }
    }

    // 併合(マージ後の集合の根を返す)
    int merge(int a, int b) {
        int x = find(a);
        int y = find(b);

        if (x == y) {
            tree[x] = false;
            return x;
        }
        if (!tree[x] or !tree[y]) {
            tree[x] = tree[y] = false;
        }

        groupcnt--;
        if (rank[x] < rank[y]) {
            par[x] = y;
            sz[y] += sz[x];
            return y;
        } else {
            par[y] = x;
            sz[x] += sz[y];
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
            return x;
        }
    }

    // 同じ集合に属するか判定
    bool same(int a, int b) {
        return find(a) == find(b);
    }

    // あるノードの属する集合のノード数
    ll size(int x) {
        return sz[find(x)];
    }

    // 集合の数
    int size() {
        return groupcnt;
    }

    // 木かどうかの判定
    bool is_tree(int x) {
        return tree[find(x)];
    }

    // 全ての根を取得
    set<int> get_roots() {
        set<int> res;
        rep(i, n) {
            res.insert(find(i));
        }
        return res;
    }
};
