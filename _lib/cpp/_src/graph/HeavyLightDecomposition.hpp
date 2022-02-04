#include "../macros.hpp"

// HL分解
// ・主な使用方法など
// 　・初期化後、忘れずにbuildを呼ぶこと。
// 　・パスクエリはadd,queryで処理
// 　・1点取得/更新はhld.in[x]で可能。add,queryは呼ばなくていい。
// 　・辺属性にすると、添字0が欠番になる。(親に向かう辺と対応するはずなのでそれはそうか)
// 　　なお辺属性に値を割り当てる時は、depで深い方の頂点にってやるといい。(ABC133fとか参照)
// 　・部分木クエリは[hld.in[x],hld.out[x])で処理。
// 　　なお部分木クエリも辺属性の時はedge=trueのように左端を+1する。
// 　　あと「部分木じゃない部分」も取れる。[0,hld.in[x])と[hld.out[x],N) の2区間でOK。
// 　　これと深さで比較して場合分けすれば、あるパスの手前と向こう側が任意に取れるようになる。
// 　・根付き木は頂点0が根である前提。他の頂点を根にしたい場合、
// 　　HLD構築前に根と頂点0の関係を全てスワップしておく。
// 　　→任意の頂点を根にできるよう改修してみた。前やろうとして失敗したんだけど、
// 　　headの初期値をrootにしたらうまくいった。
// 　・パスクエリ[u,v]にて、u->lcaとlca->vでHLD上の列の向きが逆になるので、
// 　　乗せたセグ木の演算にマージ方向がある場合などは注意して処理する。

// HL分解
struct HeavyLightDecomposition {
public:
    vvi g;
    vector<int> sz, in, out, head, rev, par, dep;

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
    void update(int u, int v, const Q &q, bool edge = false) {
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

    explicit HeavyLightDecomposition(vvi &g, int root=0) : g(g) {
        build(root);
    }

private:
    void build(int root=0) {
        sz.assign(g.size(), 0);
        in.assign(g.size(), 0);
        out.assign(g.size(), 0);
        head.assign(g.size(), root);
        rev.assign(g.size(), 0);
        par.assign(g.size(), 0);
        dep.assign(g.size(), 0);
        dfs_sz(root, -1, 0);
        int t = 0;
        dfs_hld(root, -1, t);
    }

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