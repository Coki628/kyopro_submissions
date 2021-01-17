/**
 * 参考：http://satelliteyezu.hatenablog.com/entry/2016/04/05/073359
 * ・別解。こちらはマージテクなし。
 * ・HLDに区間加算BITとchminできるセグ木(beats)を乗せてデータ構造で殴る。
 * ・辺uから外に伸びる辺は、LCAの頂点までの間使えるので、HLDのパスクエリにchminする。
 * ・行き先が部分木の外かどうかの判定は、部分木クエリの逆側に区間加算を当てる。
 * ・さすがに綺麗な解法ではないし遅くて、AC1.34秒。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define ALL(A) A.begin(), A.end()
#define elif else if
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll INF = 1e18;
constexpr ll MOD = 1000000007;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

vector<ll> LIST(ll N) { vector<ll> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

struct UnionFind {

    int n, groupcnt;
    vector<int> par, rank, size;
    vector<bool> tree;

    UnionFind(int n) : n(n) {
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        tree.resize(n, 1);
        rep(i, 0, n) par[i] = i;
        groupcnt = n;
    }

    UnionFind() {}

    void resize(int _n) {
        n = _n;
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        rep(i, 0, n) par[i] = i;
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

    // 併合
    void merge(int a, int b) {
        int x = find(a);
        int y = find(b);

        if (x == y) {
            tree[x] = false;
            return;
        }
        if (!tree[x] or !tree[y]) {
            tree[x] = tree[y] = false;
        }

        if (x == y) return;
        groupcnt--;
        if (rank[x] < rank[y]) {
            par[x] = y;
            size[y] += size[x];
        } else {
            par[y] = x;
            size[x] += size[y];
            if (rank[x] == rank[y]) {
                rank[x] += 1;
            }
        }
    }

    // 同じ集合に属するか判定
    bool is_same(int a, int b) {
        return find(a) == find(b);
    }

    // あるノードの属する集合のノード数
    int get_size(int x) {
        return size[find(x)];
    }

    // 集合の数
    int get_size() {
        return groupcnt;
    }

    // 木かどうかの判定
    bool is_tree(int x) {
        return tree[find(x)];
    }

    // 全ての根を取得
    set<int> get_roots() {
        set<int> res;
        rep(i, 0, n) {
            res.insert(find(i));
        }
        return res;
    }
};

template<typename T>
struct BIT2 {

    ll N;
    vector<T> data0, data1;

    BIT2() {};

    BIT2(int N) {
        resize(N);
    }

    void resize(int n) {
        // 添字0が使えないので、内部的には全て1-indexedとして扱う
        N = ++n;
        data0.resize(N);
        data1.resize(N);
    }

    void _add(vector<T> &data, int k, T x) {
        k++;
        while (k < N) {
            data[k] += x;
            k += k & -k;
        }
    }

    T _get(vector<T> &data, int k) {
        k++;
        T s = 0;
        while (k) {
            s += data[k];
            k -= k & -k;
        }
        return s;
    }

    // 区間[l,r)に値xを加算
    void add(int l, int r, T x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    // 1点加算
    void add(int i, T x) {
        add(i, i+1, x);
    }

    // 区間[l,r)の和を取得
    T query(int l, int r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    // 1点取得
    T get(int i) {
        return query(i, i+1);
    }

    // 1点更新
    void update(int i, T x) {
        add(i, i+1, x - get(i));
    }

    T operator[](int i) {
        return get(i);
    }
};

struct HeavyLightDecomposition {
public:
    vvl &g;
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

    /* k: 0-indexed */
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

    explicit HeavyLightDecomposition(vvl &g) : g(g) {}

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

template<class T> class SegTreeBeats {
    T inf;
    size_t length;
    vector<T>
    node_max_first,node_max_second,count_max_first,
    node_min_first,node_min_second,count_min_first,
    node_sum,lazy_add,lazy_update;
    vector<pair<int,int>> range;
    stack<int> down,up;
    inline void internal_chmax(int k, long long x) {
        node_sum[k] += (x - node_max_first[k]) * count_max_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_first[k] == node_min_second[k]) node_max_first[k] = node_min_second[k] = x;
        else node_max_first[k] = x;
        if(lazy_update[k] != inf && x < lazy_update[k]) lazy_update[k] = x;
    }
    inline void internal_chmin(int k, long long x) {
        node_sum[k] += (x - node_min_first[k]) * count_min_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_second[k] == node_min_first[k]) node_min_first[k] = node_max_second[k] = x;
        else node_min_first[k] = x;
        if(lazy_update[k] != inf && lazy_update[k] < x) lazy_update[k] = x;
    }
    inline void internal_add(int k, long long x) {
        node_max_first[k] += x;
        if(node_max_second[k] != -inf) node_max_second[k] += x;
        node_min_first[k] += x;
        if(node_min_second[k] != inf) node_min_second[k] += x;
        node_sum[k] += x * (range[k].second - range[k].first);
        (lazy_update[k] != inf ? lazy_update[k]:lazy_add[k]) += x;
    }
    inline void internal_update(int k, long long x) {
        node_max_first[k] = x; node_max_second[k] = -inf;
        node_min_first[k] = x; node_min_second[k] = inf;
        count_max_first[k] = count_min_first[k] = (range[k].second - range[k].first);
        node_sum[k] = x * (range[k].second - range[k].first);
        lazy_update[k] = x;
        lazy_add[k] = 0;
    }
    inline void propagate(int k) {
        if(length-1 <= k) return;
        if(lazy_update[k] != inf) {
            internal_update(2*k+0, lazy_update[k]);
            internal_update(2*k+1, lazy_update[k]);
            lazy_update[k] = inf;
            return;
        }
        if(lazy_add[k] != 0) {
            internal_add(2*k+0, lazy_add[k]);
            internal_add(2*k+1, lazy_add[k]);
            lazy_add[k] = 0;
        }
        if(node_max_first[k] < node_max_first[2*k+0]) {
            internal_chmax(2*k+0, node_max_first[k]);
        }
        if(node_min_first[2*k+0] < node_min_first[k]) {
            internal_chmin(2*k+0, node_min_first[k]);
        }
        if(node_max_first[k] < node_max_first[2*k+1]) {
            internal_chmax(2*k+1, node_max_first[k]);
        }
        if(node_min_first[2*k+1] < node_min_first[k]) {
            internal_chmin(2*k+1, node_min_first[k]);
        }
    }
    inline void merge(int k) {
        node_sum[k] = node_sum[2*k+0] + node_sum[2*k+1];
        if(node_max_first[2*k+0] < node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+1];
            count_max_first[k] = count_max_first[2*k+1];
            node_max_second[k] = max(node_max_first[2*k+0], node_max_second[2*k+1]);
        }
        else if(node_max_first[2*k+0] > node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_first[2*k+1]);
        }
        else {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0] + count_max_first[2*k+1];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_second[2*k+1]);
        }
        if(node_min_first[2*k+0] < node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_first[2*k+1]);
        }
        else if(node_min_first[2*k+0] > node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+1];
            count_min_first[k] = count_min_first[2*k+1];
            node_min_second[k] = min(node_min_first[2*k+0], node_min_second[2*k+1]);
        }
        else {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0] + count_min_first[2*k+1];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_second[2*k+1]);
        }
    }
    inline void up_merge(void){
        while(up.size()) {
            merge(up.top());
            up.pop();
        }
    }
    inline void down_propagate(const int& k) {
        propagate(k);
        down.push(2*k+0);
        down.push(2*k+1);
    }
public:
    SegTreeBeats(const int num,const T inf = (1LL<<60)) {
        vector<T> a(num,0);
        *this = SegTreeBeats(a,inf);
    }
    SegTreeBeats(const vector<T>& a,const T inf = (1LL<<60)) : inf(inf){
        int num = a.size();
        for (length = 1; length <= num; length *= 2);
        node_max_first.resize(2*length);
        node_max_second.resize(2*length);
        count_max_first.resize(2*length);
        node_min_first.resize(2*length);
        node_min_second.resize(2*length);
        count_min_first.resize(2*length);
        node_sum.resize(2*length);
        range.resize(2*length);
        lazy_add.resize(2*length);
        lazy_update.resize(2*length);

        for(int i=0; i<2*length; ++i) lazy_add[i] = 0, lazy_update[i] = inf;
        for(int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for(int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);

        for(int i=0; i<num; ++i) {
            node_max_first[length+i] = node_min_first[length+i] = node_sum[length+i] = a[i];
            node_max_second[length+i] = -inf;
            node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 1;
        }
        for(int i=num; i<length; ++i) {
            node_max_first[length+i] = node_max_second[length+i] = -inf;
            node_min_first[length+i] = node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 0;
        }
        for(int i=length-1; i; --i) merge(i);
    }
    inline void range_chmin(int a, int b, long long x) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || node_max_first[k] <= x) continue;
            if(a <= range[k].first && range[k].second <= b && node_max_second[k] < x) {
                internal_chmax(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_chmax(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || x <= node_min_first[k]) continue;
            if(a <= range[k].first && range[k].second <= b && x < node_min_second[k]) {
                internal_chmin(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_add(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_add(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_update(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_update(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline T get_max(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = max(v,node_max_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_min(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = min(v,node_min_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_sum(int a, int b, int k=1) {
        down.push(1);
        long long v = 0;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v += node_sum[k];
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;

    vector<tuple<ll, ll, ll>> edges;
    vvl nodes(N);
    map<pll, pll> cost;
    rep(i, 0, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        edges.pb({c, u, v});
        nodes[u].pb(v);
        nodes[v].pb(u);
        cost[{u, v}] = {c, i};
        cost[{v, u}] = {c, i};
    }
    sort(ALL(edges));

    UnionFind uf(N);
    vvl nodes2(N);
    ll base = 0;
    set<pll> used;
    for (auto& [c, u, v] : edges) {
        if (!uf.is_same(u, v)) {
            uf.merge(u, v);
            base += c;
            nodes2[u].pb(v);
            nodes2[v].pb(u);
            used.insert({u, v});
            used.insert({v, u});
        }
    }
    // そもそも最小全域木を構築不可
    if (uf.get_size() != 1) {
        rep(i, 0, M) print(-1);
        return 0;
    }

    HeavyLightDecomposition hld(nodes2);
    hld.build();
    // bit[i] := 頂点iが現在見ている頂点の部分木ではないかどうか
    BIT2<ll> bit(N);
    // seg[i] := 頂点iが使える辺の中で最小のコスト
    SegTreeBeats<ll> seg(vector<ll>(N, INF), INF);

    vector<ll> ans(M, base);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        for (ll v : nodes2[u]) {
            if (v == prv) continue;
            f(f, v, u);
        }

        // 部分木ではない場所をOKとする
        bit.add(0, hld.in[u], 1);
        bit.add(hld.out[u], N, 1);
        // 頂点uから外に伸びる辺を確認
        ll c, i;
        for (ll v : nodes[u]) {
            if (v == prv) continue;
            tie(c, i) = cost[{u, v}];
            // 行き先vが部分木の外側にあったら、LCAまでの辺でchminする
            if (bit[hld.in[v]]) {
                ll lca = hld.lca(u, v);
                hld.add(u, v, [&](ll a, ll b) {
                    seg.range_chmin(a, b, c);
                }, true);
            }
        }
        // 状態を戻す
        bit.add(0, hld.in[u], -1);
        bit.add(hld.out[u], N, -1);

        // 辺(u,prv)を取り除く場合の答えを求める
        if (prv != -1) {
            tie(c, i) = cost[{u, prv}];
            // この位置での最小値を取得
            ll res = seg.get_min(hld.in[u], hld.in[u]+1);
            if (res != INF) {
                ans[i] = base - c + res;
            } else {
                ans[i] = -1;
            }
        }
    };
    dfs(dfs, 0, -1);

    for (ll a : ans) print(a);
    return 0;
}
