/**
 * 参考：https://suikaba.hatenablog.com/entry/2020/10/14/235107
 * 　　　https://jag-icpc.org/?plugin=attach&refer=2012%2FPractice%2F%E6%98%A5%E3%82%B3%E3%83%B3%E3%83%86%E3%82%B9%E3%83%88%2F%E8%AC%9B%E8%A9%95&openfile=E.pdf
 * ・蟻本演習4-6-2
 * ・DFS、マージテク
 * ・難しかったー。すいバカさんの記事を頑張って読み込んで理解した。
 * 　簡単なのはやったことあったけど、マージテクが本質的に効く問題はまだ慣れてないから
 * 　すごくためになるね。
 * ・基本的には部分木の中で有効な集合を持ち回ってDFSする感じなんだけど、
 * 　集合のマージはマージテクに従えばlogで収まるので速い。
 * 　公式解説は難しいデータ構造を紹介してたけど、setで問題なく対応できる。
 * ・あと自分的には、集合からどのタイミングで辺を取り除くかを理解するのに時間がかかった。
 * 　直列なやつを祖先まで戻った時に除くのは割と直感的に思えたけど、
 * 　並列なやつを除くタイミングが、説明見てもしばらく、これでいいのかー、ってうんうん言ってた。
 * 　両頂点のLCAに戻った時、って思ったら、イメージできて理解できた。
 * ・マージテクもそうだけど、mapとかsetでもばんばんlog乗ってるはずなんだけど、
 * 　10万頂点20万辺でAC0.61秒。やっぱC++速いよなー。。
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

    vector<ll> ans(M, base);
    auto dfs = [&](auto&& f, ll u, ll prv) -> set<pll> {
        // se := 頂点uの部分木から、それより祖先側に伸びる辺の集合
        set<pll> se;
        for (ll v : nodes2[u]) {
            if (v == prv) continue;
            auto res = f(f, v, u);
            // マージテク
            if (res.size() > se.size()) swap(res, se);
            for (auto& p : res) {
                // 並列な位置にある辺をLCAまで戻ってきたところで削除
                if (se.count(p)) {
                    se.erase(p);
                } else {
                    se.insert(p);
                }
            }
        }
        // 頂点uから外に伸びる辺の追加
        for (ll v : nodes[u]) {
            if (v == prv) continue;
            pll p = cost[{u, v}];
            if (!used.count({u, v})) {
                // 直列な位置にある辺を祖先まで戻ってきたところで削除
                if (se.count(p)) {
                    se.erase(p);
                } else {
                    se.insert(p);
                }
            }
        }
        // 辺(u,prv)を取り除く場合の答えを求める
        if (prv != -1) {
            auto& [c, i] = cost[{u, prv}];
            if (!se.empty()) {
                ans[i] = base - c + (*se.begin()).first;
            } else {
                ans[i] = -1;
            }
        }
        return se;
    };
    dfs(dfs, 0, -1);

    for (ll a : ans) print(a);
    return 0;
}
