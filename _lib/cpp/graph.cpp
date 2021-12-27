/*
・ライブラリ：グラフ
*/

#include "_tpl.cpp"


// BFS
vector<int> bfs(const vvi &nodes, const vector<int> &src) {

    int N = nodes.size();
    vector<int> res(N, -1);
    queue<int> que;
    for (int s : src) {
        res[s] = 0;
        que.push(s);
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (auto v: nodes[u]) {
            if (res[v] == -1) {
                res[v] = res[u]+1;
                que.push(v);
            }
        }
    }
    return res;
}


// ダイクストラ
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


// ダイクストラ
template<typename T>
vector<T> dijkstra(const vector<vector<pair<ll, T>>> &nodes, int src, int goal=-1) {

    int N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
    res[src] = 0;
    que.push({0, src});

    while (!que.empty()) {
        auto [dist, u] = que.top(); que.pop();
        if (u == goal) return res;
        if (res[u] < dist) continue;
        for (auto [v, cost] : nodes[u]) {
            if (dist+cost < res[v]) {
                res[v] = dist+cost;
                que.push({dist+cost, v});
            }
        }
    }
    return res;
}


template<typename T>
vector<vector<T>> warshall_floyd(vector<vector<T>> G) {
    ll N = G.size();
    rep(i, N) G[i][i] = 0;
    rep(k, N) {
        rep(i, N) {
            rep(j, N) {
                chmin(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
    rep(i, N) {
        if (G[i][i] < 0) {
            return {};
        }
    }
    return G;
}


// HL分解
// ・主な使用方法など
// 　・初期化後、忘れずにbuildを呼ぶこと。
// 　・パスクエリはadd,queryで処理
// 　・1点取得/更新はhld.in[x]で可能。add,queryは呼ばなくていい。
// 　・部分木クエリは[hld.in[x],hld.out[x])で処理
// 　・根付き木は頂点0が根である前提。他の頂点を根にしたい場合、
// 　　HLD構築前に根と頂点0の関係を全てスワップしておく。
// 　・パスクエリ[u,v]にて、u->lcaとlca->vでHLD上の列の向きが逆になるので、
// 　　乗せたセグ木の演算にマージ方向がある場合などは注意して処理する。
// 　・辺属性にすると、添字0が欠番になる。(親に向かう辺と対応するはずなのでそれはそうか)
// 　　なお辺属性に値を割り当てる時は、depで深い方の頂点にってやるといい。(ABC133fとか参照)

// HL分解
struct HeavyLightDecomposition {
public:
    vvi g;
    vector< int > sz, in, out, head, rev, par, dep;

    void build() {
        sz.assign(g.size(), 0);
        in.assign(g.size(), 0);
        out.assign(g.size(), 0);
        head.assign(g.size(), 0);
        rev.assign(g.size(), 0);
        par.assign(g.size(), 0);
        dep.assign(g.size(), 0);
        dfs_sz(0, -1, 0);
        int t = 0;
        dfs_hld(0, -1, t);
    }

    // 頂点vからk回遡った頂点を返す
    int la(int v, int k) {
        while(1) {
            int u = head[v];
            if(in[v] - k >= in[u]) return rev[in[v] - k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    int lca(int u, int v) const {
        for(;; v = par[head[v]]) {
            if(in[u] > in[v]) swap(u, v);
            if(head[u] == head[v]) return u;
        }
    }

    int dist(int u, int v) const {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    template< typename E, typename Q, typename F, typename S >
    E query(int u, int v, const E &ti, const Q &q, const F &f, const S &s, bool edge = false) {
        E l = ti, r = ti;
        for(;; v = par[head[v]]) {
            if(in[u] > in[v]) swap(u, v), swap(l, r);
            if(head[u] == head[v]) break;
            l = f(q(in[head[v]], in[v] + 1), l);
        }
        return s(f(q(in[u] + edge, in[v] + 1), l), r);
    }

    template< typename E, typename Q, typename F >
    E query(int u, int v, const E &ti, const Q &q, const F &f, bool edge = false) {
        return query(u, v, ti, q, f, f, edge);
    }

    template< typename Q >
    void add(int u, int v, const Q &q, bool edge = false) {
        for(;; v = par[head[v]]) {
            if(in[u] > in[v]) swap(u, v);
            if(head[u] == head[v]) break;
            q(in[head[v]], in[v] + 1);
        }
        q(in[u] + edge, in[v] + 1);
    }

    /* {parent, child} */
    vector< pair< int, int > > compress(vector< int > &remark) {
        auto cmp = [&](int a, int b) { return in[a] < in[b]; };
        sort(begin(remark), end(remark), cmp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        int K = (int) remark.size();
        for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k - 1], remark[k]));
        sort(begin(remark), end(remark), cmp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        vector< pair< int, int > > es;
        stack< int > st;
        for(auto &k : remark) {
            while(!st.empty() && out[st.top()] <= in[k]) st.pop();
            if(!st.empty()) es.emplace_back(st.top(), k);
            st.emplace(k);
        }
        return es;
    }

    explicit HeavyLightDecomposition(vvi &g) : g(g) {}

private:
    void dfs_sz(int idx, int p, int d) {
        dep[idx] = d;
        par[idx] = p;
        sz[idx] = 1;
        if(g[idx].size() && g[idx][0] == p) swap(g[idx][0], g[idx].back());
        for(auto &to : g[idx]) {
            if(to == p) continue;
            dfs_sz(to, idx, d + 1);
            sz[idx] += sz[to];
            if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to);
        }
    }

    void dfs_hld(int idx, int p, int &times) {
        in[idx] = times++;
        rev[in[idx]] = idx;
        for(auto &to : g[idx]) {
            if(to == p) continue;
            head[to] = (g[idx][0] == to ? head[idx] : to);
            dfs_hld(to, idx, times);
        }
        out[idx] = times;
    }
};


// 全方位木DP
// ・主な使用方法
// 　・f1は集合同士のマージ、f2はある集合に新しく辺を取り込む時のマージに使う。
// 　　例えば普通の木DPの遷移が dp[u] += dp[v]+1 だったら、
// 　　f1が dp[u]+dp[v] で、f2が dp[v]+1 に相当する感じ。

// 全方位木DP
template<typename sum_t, typename key_t, typename F1, typename F2>
struct ReRooting {
    struct Edge {
        int to;
        key_t data;
        sum_t dp, ndp;
    };

    vector<vector<Edge>> g;
    vector<sum_t> subdp, dp;
    const sum_t ident;
    const F1 f1;
    const F2 f2;

    ReRooting(int V, const F1 f1, const F2 f2, const sum_t &ident)
        : g(V), f1(f1), f2(f2), ident(ident), subdp(V, ident), dp(V, ident) {}

    void add_edge(int u, int v, const key_t &d) {
        g[u].emplace_back((Edge) {v, d, ident, ident});
        g[v].emplace_back((Edge) {u, d, ident, ident});
    }

    void add_edge_bi(int u, int v, const key_t &d, const key_t &e) {
        g[u].emplace_back((Edge) {v, d, ident, ident});
        g[v].emplace_back((Edge) {u, e, ident, ident});
    }

    void dfs_sub(int idx, int par) {
        for(auto &e : g[idx]) {
        if(e.to == par) continue;
        dfs_sub(e.to, idx);
        subdp[idx] = f1(subdp[idx], f2(subdp[e.to], e.data));
        }
    }

    void dfs_all(int idx, int par, const sum_t &top) {
        sum_t buff{ident};
        for(int i = 0; i < (int) g[idx].size(); i++) {
        auto &e = g[idx][i];
        e.ndp = buff;
        e.dp = f2(par == e.to ? top : subdp[e.to], e.data);
        buff = f1(buff, e.dp);
        }
        dp[idx] = buff;
        buff = ident;
        for(int i = (int) g[idx].size() - 1; i >= 0; i--) {
        auto &e = g[idx][i];
        if(e.to != par) dfs_all(e.to, idx, f1(e.ndp, buff));
        e.ndp = f1(e.ndp, buff);
        buff = f1(buff, e.dp);
        }
    }

    vector<sum_t> build() {
        dfs_sub(0, -1);
        dfs_all(0, -1, ident);
        return dp;
    }
};

template<typename sum_t, typename key_t, typename F1, typename F2>
ReRooting<sum_t, key_t, F1, F2> get_rerooting(int N, const F1& f1, const F2& f2, const sum_t& M1, const key_t& M2) {
    return {N, f1, f2, M1};
}


// 01BFS(コストが0or1なら使える)
vector<ll> bfs01(const vvpll &nodes, const vector<ll> &src) {

    ll N = nodes.size();
    vector<ll> res(N, INF);
    deque<ll> que;
    for (ll s : src) {
        res[s] = 0;
        que.push_back(s);
    }

    while (!que.empty()) {
        ll u = que.front(); que.pop_front();
        for (auto [v, c] : nodes[u]) {
            if (c == 0 and res[u] < res[v]) {
                res[v] = res[u];
                que.push_front(v);
            } elif (c == 1 and res[u]+1 < res[v]) {
                res[v] = res[u]+1;
                que.push_back(v);
            } elif (c >= 2) {
                assert(c == 0 or c == 1);
            }
        }
    }
    return res;
}


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
    void merge(int x, int y, ll w) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;

        // xの木の高さ < yの木の高さ
        if (rank[rx] < rank[ry]) {
            par[rx] = ry;
            weight[rx] = w - weight[x] + weight[y];
        } else {
            par[ry] = rx;
            weight[ry] = - w - weight[y] + weight[x];
            // 木の高さが同じだった場合の処理
            if (rank[rx] == rank[ry]) {
                rank[rx]++;
            }
        }
    }

    // 同じ集合に属するか
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // xからyへのコスト
    T diff(int x, int y) {
        return weight[x] - weight[y];
    }
};


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


// 参考：https://lorent-kyopro.hatenablog.com/entry/2020/07/24/170656
// 区間に辺を張るテク
template<typename W>
struct range_edge_graph {
    int n;
    struct edge { int to; W weight; };
    vector<vector<edge>> g;
    
    // range_edge_graph(int n) : n(n) {
    //     g.resize(4*n);
    //     for (int i = 1; i < n; ++i) {
    //         int cl = i<<1|0, cr = i<<1|1;
    //         g[i].push_back({cl, 0});
    //         g[i].push_back({cr, 0});
    //         g[cl+2*n].push_back({i+2*n, 0});
    //         g[cr+2*n].push_back({i+2*n, 0});
    //     }
    //     for (int i = n; i < 2*n; ++i) g[i].push_back({i+2*n, 0});
    // }

    // // from [l1, r1) to [l2, r2)
    // void add_edge(int l1, int r1, int l2, int r2, W w) {
    //     int idx = g.size();
    //     for (l1 += n, r1 += n; l1 < r1; l1 >>= 1, r1 >>= 1) {
    //         if (l1 & 1) g[l1+2*n].push_back({idx, 0}), l1++;
    //         if (r1 & 1) --r1, g[r1+2*n].push_back({idx, 0});
    //     }
    //     vector<edge> node;
    //     for (l2 += n, r2 += n; l2 < r2; l2 >>= 1, r2 >>= 1) {
    //         if (l2 & 1) node.push_back({l2++, w});
    //         if (r2 & 1) node.push_back({--r2, w});
    //     }
    //     g.push_back(node);
    // }

    range_edge_graph(int n) : n(n) {
        g.resize(3*n);
        for (int i = 1; i < n; ++i) {
            int cl = i<<1|0, cr = i<<1|1;
            _add_edge(i, cl, 0);
            _add_edge(i, cr, 0);
            _add_edge(cl+2*n, i+2*n, 0);
            _add_edge(cr+2*n, i+2*n, 0);
        }
    }

    // map [3n, 4n) -> [n, 2n)
    void _add_edge(int u, int v, W w) {
        if (3*n <= u) u -= 2*n;
        g[u].push_back({v, w});
    }

    // from [l1, r1) to [l2, r2)
    void add_edge(int l1, int r1, int l2, int r2, W w) {
        int idx = g.size();
        for (l1 += n, r1 += n; l1 < r1; l1 >>= 1, r1 >>= 1) {
            if (l1 & 1) _add_edge(l1+2*n, idx, 0), l1++;
            if (r1 & 1) --r1, _add_edge(r1+2*n, idx, 0);
        }
        vector<edge> node;
        for (l2 += n, r2 += n; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) node.push_back({l2++, w});
            if (r2 & 1) node.push_back({--r2, w});
        }
        g.push_back(node);
    }

    // from u to v
    void add_edge(int u, int v, W w) {
        add_edge(u, u+1, v, v+1, w);
    }

    vector<W> dijkstra(int s) {
        s += n;
        vector<W> dist(g.size(), INF);
        dist[s] = 0;
        using P = pair<W, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.emplace(0, s);
        while (!que.empty()) {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (edge& e : g[v]) {
                if (dist[e.to] > dist[v] + e.weight) {
                    dist[e.to] = dist[v] + e.weight;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
        vector<W> res(dist.begin() + n, dist.begin() + 2*n);
        return res;
    }
};


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
