/*
・終了後約40分で自力AC。もうちょいと思ったら全然かかった。。
・イベントソート、平面走査、二分探索
・座圧なしでいい制約がこどふぉにしては優しい。
　でも複数テストケースなのにBIT(MX)とか内側で宣言しててTLE踏んだ。。
・基本的にはyでソートする感じの平面走査。サボってmap<ll, vector>の隣接リストにした。
　イベントは水平ライン、横線のみ接する座標、縦線のみ接する座標の3つにする。
　縦横両方接する座標はマンハッタン距離でどこでも行けるので無視していい。
　また、横線座標から縦線座標とその逆もどこでもOKなので、同じ軸同士だけ見る。
・横線座標は同じ縦線に囲まれてる同士が対象ペアになるので、にぶたんで分けて管理。
　縦線座標は次の水平ラインが来るまでのものが対象で、そこからx座標が同じものは引く。
　こちらは動的に総和取ったり追加したりするのでBITで管理。
　水平ラインが来たらそこまでの縦線座標ペアの候補を消す。
・基本的にはこれでOKだけど、横線座標は同じy位置のものをペアしたくないので
　自身の追加は後からやるのに対して、縦線座標は関係なくて自分以前に追加された全部が対象なので注意。
　縦線座標も後からの追加にしててWAがなかなか取れなかった。
・多少ゴチャゴチャする、実装力要る問題だけども、これくらい爆速で組めるようになりたいなぁ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for (ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for (ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for (ll i = a, _bb = b; (c > 0 && a <= i && i < _bb) or (c < 0 && a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define UNIQUE(A) sort(ALL(A)), A.erase(unique(ALL(A)), A.end())
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(deque<T> A) { rep(i, 0, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

// from common.cpp
ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }
ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
ll modulo(ll a, ll b) { return ((a % b) + b) % b; }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }
template<typename T> T sum(const vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(const vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(const vector<T> &A) { return *min_element(ALL(A)); }
ll pow(int x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }
int popcount(ll S) { return __builtin_popcountll(S); }
int bit_length(ll x) { return x != 0 ? floor(log2((ld)x))+1 : 0; }
template<typename T> int bisect_left(const vector<T> &A, T val, int lo=0) { return lower_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> int bisect_right(const vector<T> &A, T val, int lo=0) { return upper_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> map<T, ll> Counter(const vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
template<typename T> vector<ll> Counter(const vector<T> &A, T mx) { vector<ll> res(mx+1); for (T a : A) { res[a]++; } return res; }
map<char, ll> Counter(const string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ld bisearch_min(ld mn, ld mx, const F &func, ll times) { ld ok = mx; ld ng = mn; rep(_, 0, times) { ld mid = (ok+ng) / 2; if (func(mid)) { ok = mid; } else { ng = mid; } } return ok; }
template<typename F> ld bisearch_max(ld mn, ld mx, const F &func, ll times) { ld ok = mn; ld ng = mx; rep(_, 0, times) { ld mid = (ok+ng) / 2; if (func(mid)) { ok = mid; } else { ng = mid; } } return ok; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(const vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }
template<typename T1, typename T2, typename T3> tuple<vector<T1>, vector<T2>, vector<T3>> zip(const vector<tuple<T1, T2, T3>> &A) { int N = A.size(); tuple<vector<T1>, vector<T2>, vector<T3>> res = {vector<T1>(N), vector<T2>(N), vector<T3>(N)}; rep(i, N) { get<0>(res)[i] = get<0>(A[i]); get<1>(res)[i] = get<1>(A[i]); get<2>(res)[i] = get<2>(A[i]); } return res; }
template<typename T> struct Compress { int N; vector<T> dat; Compress(vector<T> A) { sort(A.begin(), A.end()); A.erase(unique(A.begin(), A.end()), A.end()); N = A.size(); dat = A; } int zip(T x) { return bisect_left(dat, x); } T unzip(int x) { return dat[x]; } int operator[](T x) { return zip(x); } int size() { return dat.size(); } vector<T> zip(const vector<T> &A) { int M = A.size(); vector<T> res(M); rep(i, M) res[i] = zip(A[i]); return res; } };
template<typename T> vector<pair<T, int>> RLE(const vector<T> &A) { if (A.empty()) return {}; int N = A.size(); vector<pair<T, int>> res; T cur = A[0]; int cnt = 1; rep(i, 1, N) { if (A[i] == A[i-1]) { cnt++; } else { res.pb({cur, cnt}); cnt = 1; cur = A[i]; } } res.pb({cur, cnt}); return res; }
vector<pair<char, int>> RLE(const string &S) { if (S.empty()) return {}; int N = S.size(); vector<pair<char, int>> res; char cur = S[0]; int cnt = 1; rep(i, 1, N) { if (S[i] == S[i-1]) { cnt++; } else { res.pb({cur, cnt}); cnt = 1; cur = S[i]; } } res.pb({cur, cnt}); return res; }
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count()); ll randrange(ll l, ll r) { uniform_int_distribution<ll> rand(l, r-1); return rand(mt); }
template<typename T> vector<T> LIS(const vector<T> &A, bool equal=false) { auto compare = (not equal) ? [](T a, T b) { return a > b; } : [](T a, T b) { return a >= b; }; auto bisect = (not equal) ? bisect_left<T> : bisect_right<T>; vector<T> res; res.pb(A[0]); ll n = A.size(); rep(i, 1, n) { if (compare(A[i], res.back())) { res.pb(A[i]); } else { res[bisect(res, A[i])] = A[i]; } } return res; }
bool mul_overflow(ll x, ll y) { ll z; return __builtin_mul_overflow(x, y, &z); }

// from combinatorics.cpp
template<int mod> struct ModInt { int x; ModInt() : x(0) {} ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {} ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; } ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; } ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; } ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; } ModInt operator-() const { return ModInt(-x); } ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; } ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; } ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; } ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; } bool operator==(const ModInt &p) const { return x == p.x; } bool operator!=(const ModInt &p) const { return x != p.x; } ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); } ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; } friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; } friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); } static int get_mod() { return mod; } };
struct ArbitraryModInt { int x; ArbitraryModInt() : x(0) {} ArbitraryModInt(int64_t y) : x(y >= 0 ? y % get_mod() : (get_mod() - (-y) % get_mod()) % get_mod()) {} static int &get_mod() { static int mod = 0; return mod; } static void set_mod(int md) { get_mod() = md; } ArbitraryModInt &operator+=(const ArbitraryModInt &p) { if((x += p.x) >= get_mod()) x -= get_mod(); return *this; } ArbitraryModInt &operator-=(const ArbitraryModInt &p) { if((x += get_mod() - p.x) >= get_mod()) x -= get_mod(); return *this; } ArbitraryModInt &operator*=(const ArbitraryModInt &p) { unsigned long long a = (unsigned long long) x * p.x; unsigned xh = (unsigned) (a >> 32), xl = (unsigned) a, d, m; asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (get_mod())); x = m; return *this; } ArbitraryModInt &operator/=(const ArbitraryModInt &p) { *this *= p.inverse(); return *this; } ArbitraryModInt operator-() const { return ArbitraryModInt(-x); } ArbitraryModInt operator+(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) += p; } ArbitraryModInt operator-(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) -= p; } ArbitraryModInt operator*(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) *= p; } ArbitraryModInt operator/(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) /= p; } bool operator==(const ArbitraryModInt &p) const { return x == p.x; } bool operator!=(const ArbitraryModInt &p) const { return x != p.x; } ArbitraryModInt inverse() const { int a = x, b = get_mod(), u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ArbitraryModInt(u); } ArbitraryModInt pow(int64_t n) const { ArbitraryModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; } friend ostream &operator<<(ostream &os, const ArbitraryModInt &p) { return os << p.x; } friend istream &operator>>(istream &is, ArbitraryModInt &a) { int64_t t; is >> t; a = ArbitraryModInt(t); return (is); } };
using mint = ModInt<MOD>;
// using mint = ArbitraryModInt;
template<typename T> struct ModTools { int MAX; vector<T> fact, factinv; ModTools() {}; ModTools(int mx) { build(mx); } void build(int mx) { MAX = ++mx; fact.resize(MAX); factinv.resize(MAX); fact[0] = fact[1] = 1; rep(i, 2, MAX) { fact[i] = fact[i-1] * i; } factinv[MAX-1] = (T)1 / fact[MAX-1]; rep(i, MAX-2, -1, -1) { factinv[i] = factinv[i+1] * (i+1); } } T nCr(int n, int r) { if (n < r) return 0; r = min(r, n-r); T num = fact[n]; T den = factinv[r] * factinv[n-r]; return num * den; } T nHr(int n, int r) { return nCr(r+n-1, r); } T nPr(int n, int r) { if (n < r) return 0; return fact[n] * factinv[n-r]; } };
template<typename T> vector<vector<T>> permutations(const vector<T> &A, int N=-1) { if (N == -1) N = A.size(); int M = A.size(); vector<vector<T>> comb; rep(bit, 0, 1<<M) { if (popcount(bit) != N) continue; vector<T> res; rep(i, 0, M) { if (bit>>i & 1) { res.pb(A[i]); } } comb.pb(res); } vector<vector<T>> res; for (auto &perm : comb) { sort(ALL(perm)); do { res.pb(perm); } while (next_permutation(ALL(perm))); } return res; }
template<typename T> vector<vector<T>> combinations(const vector<T> &A, int N) { int M = A.size(); vector<vector<T>> res; auto rec = [&](auto&& f, vector<T> &cur, ll x, ll n) -> void { if (n == N) { res.pb(cur); return; } rep(i, x, M) { cur.pb(A[i]); f(f, cur, i+1, n+1); cur.pop_back(); } }; vector<T> cur; rec(rec, cur, 0, 0); return res; }
template<typename T> vector<vector<T>> combinations_with_replacement(const vector<T> &A, int N) { int M = A.size(); vector<vector<T>> res; auto rec = [&](auto&& f, vector<T> &cur, ll x, ll n) -> void { if (n == N) { res.pb(cur); return; } rep(i, x, M) { cur.pb(A[i]); f(f, cur, i, n+1); cur.pop_back(); } }; vector<T> cur; rec(rec, cur, 0, 0); return res; }
template<typename T> T factorial(T x) { T res = 1; for (T i=1; i<=x; i++) res *= i; return res; }
ll nCr(int n, int r) { auto dp = list2d(n+1, r+1, 0LL); dp[0][0] = 1; rep(i, 1, n+1) { dp[i][0] = 1; rep(j, 1, r+1) { dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]); } } return dp[n][r]; }

// from geometry.cpp
constexpr ld EPS = 1e-10;
constexpr ld PI = M_PI;
ld degrees(ld radians) { return radians * 180.0 / PI; }
ld radians(ld degrees) { return degrees * PI / 180.0; }

// from graph.cpp
vector<int> bfs(const vvi &nodes, const vector<int> &src) { int N = nodes.size(); vector<int> res(N, -1); queue<int> que; for (int s : src) { res[s] = 0; que.push(s); } while (!que.empty()) { int u = que.front(); que.pop(); for (auto v: nodes[u]) { if (res[v] == -1) { res[v] = res[u]+1; que.push(v); } } } return res; }
template<typename T> vector<T> dijkstra(const vector<vector<pair<ll, T>>> &nodes, int src) { int N = nodes.size(); vector<T> res(N, INF); priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que; res[src] = 0; que.push({0, src}); while (!que.empty()) { auto [dist, u] = que.top(); que.pop(); if (res[u] < dist) continue; for (auto [v, cost] : nodes[u]) { if (dist+cost < res[v]) { res[v] = dist+cost; que.push({dist+cost, v}); } } } return res; }
struct UnionFind { int n, groupcnt; vector<int> par, rank, sz; vector<bool> tree; UnionFind(int n) : n(n) { par.resize(n); rank.resize(n); sz.resize(n, 1); tree.resize(n, 1); rep(i, 0, n) par[i] = i; groupcnt = n; } UnionFind() {} void resize(int _n) { n = _n; par.resize(n); rank.resize(n); sz.resize(n, 1); rep(i, 0, n) par[i] = i; groupcnt = n; } int find(int x) { if (par[x] == x) { return x; } else { par[x] = find(par[x]); return par[x]; } } int merge(int a, int b) { int x = find(a); int y = find(b); if (x == y) { tree[x] = false; return x; } if (!tree[x] or !tree[y]) { tree[x] = tree[y] = false; } groupcnt--; if (rank[x] < rank[y]) { par[x] = y; sz[y] += sz[x]; return y; } else { par[y] = x; sz[x] += sz[y]; if (rank[x] == rank[y]) { rank[x]++; } return x; } } bool same(int a, int b) { return find(a) == find(b); } ll size(int x) { return sz[find(x)]; } int size() { return groupcnt; } bool is_tree(int x) { return tree[find(x)]; } set<int> get_roots() { set<int> res; rep(i, 0, n) { res.insert(find(i)); } return res; } };
struct HeavyLightDecomposition { public: vvi g; vector< int > sz, in, out, head, rev, par, dep; void build() { sz.assign(g.size(), 0); in.assign(g.size(), 0); out.assign(g.size(), 0); head.assign(g.size(), 0); rev.assign(g.size(), 0); par.assign(g.size(), 0); dep.assign(g.size(), 0); dfs_sz(0, -1, 0); int t = 0; dfs_hld(0, -1, t); } /* k: 0-indexed */ int la(int v, int k) { while(1) { int u = head[v]; if(in[v] - k >= in[u]) return rev[in[v] - k]; k -= in[v] - in[u] + 1; v = par[u]; } } int lca(int u, int v) const { for(;; v = par[head[v]]) { if(in[u] > in[v]) swap(u, v); if(head[u] == head[v]) return u; } } int dist(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; } template< typename E, typename Q, typename F, typename S > E query(int u, int v, const E &ti, const Q &q, const F &f, const S &s, bool edge = false) { E l = ti, r = ti; for(;; v = par[head[v]]) { if(in[u] > in[v]) swap(u, v), swap(l, r); if(head[u] == head[v]) break; l = f(q(in[head[v]], in[v] + 1), l); } return s(f(q(in[u] + edge, in[v] + 1), l), r); } template< typename E, typename Q, typename F > E query(int u, int v, const E &ti, const Q &q, const F &f, bool edge = false) { return query(u, v, ti, q, f, f, edge); } template< typename Q > void add(int u, int v, const Q &q, bool edge = false) { for(;; v = par[head[v]]) { if(in[u] > in[v]) swap(u, v); if(head[u] == head[v]) break; q(in[head[v]], in[v] + 1); } q(in[u] + edge, in[v] + 1); } /* {parent, child} */ vector< pair< int, int > > compress(vector< int > &remark) { auto cmp = [&](int a, int b) { return in[a] < in[b]; }; sort(begin(remark), end(remark), cmp); remark.erase(unique(begin(remark), end(remark)), end(remark)); int K = (int) remark.size(); for(int k = 1; k < K; k++) remark.emplace_back(lca(remark[k - 1], remark[k])); sort(begin(remark), end(remark), cmp); remark.erase(unique(begin(remark), end(remark)), end(remark)); vector< pair< int, int > > es; stack< int > st; for(auto &k : remark) { while(!st.empty() && out[st.top()] <= in[k]) st.pop(); if(!st.empty()) es.emplace_back(st.top(), k); st.emplace(k); } return es; } explicit HeavyLightDecomposition(vvi &g) : g(g) {} private: void dfs_sz(int idx, int p, int d) { dep[idx] = d; par[idx] = p; sz[idx] = 1; if(g[idx].size() && g[idx][0] == p) swap(g[idx][0], g[idx].back()); for(auto &to : g[idx]) { if(to == p) continue; dfs_sz(to, idx, d + 1); sz[idx] += sz[to]; if(sz[g[idx][0]] < sz[to]) swap(g[idx][0], to); } } void dfs_hld(int idx, int p, int &times) { in[idx] = times++; rev[in[idx]] = idx; for(auto &to : g[idx]) { if(to == p) continue; head[to] = (g[idx][0] == to ? head[idx] : to); dfs_hld(to, idx, times); } out[idx] = times; } };
template<typename T> vector<vector<T>> warshall_floyd(vector<vector<T>> G) { ll N = G.size(); rep(i, 0, N) G[i][i] = 0; rep(k, 0, N) { rep(i, 0, N) { rep(j, 0, N) { chmin(G[i][j], G[i][k] + G[k][j]); } } } rep(i, 0, N) { if (G[i][i] < 0) { return {}; } } return G; }

// from grid.cpp
const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const vector<pii> directions8 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
ll gridtoid(ll i, ll j, ll W) { return i*W+j; }
pll idtogrid(ll id, ll W) { return divmod(id, W); }
template<typename T> void transpose(vector<vector<T>> &grid) { int H = grid.size(); int W = grid[0].size(); auto res = list2d(W, H, (T)0); rep(i, 0, H) { rep(j, 0, W) { res[j][i] = grid[i][j]; } } swap(res, grid); }
void transpose(vector<string> &grid) { int H = grid.size(); int W = grid[0].size(); vector<string> res(W, string(H, '*')); rep(i, 0, H) { rep(j, 0, W) { res[j][i] = grid[i][j]; } } swap(res, grid); }
vvl bfs(const vector<string> &grid, const vector<pii> &src, char invalid='#') { int H = grid.size(); int W = grid[0].size(); auto res = list2d(H, W, INF); const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; queue<pii> que; for (auto [h, w] : src) { que.push({h, w}); res[h][w] = 0; } while (!que.empty()) { auto [h, w] = que.front(); que.pop(); for (auto [dh, dw] : directions) { int nh = h + dh; int nw = w + dw; if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue; if (grid[nh][nw] == invalid) continue; if (res[nh][nw] == INF) { res[nh][nw] = res[h][w] + 1; que.push({nh, nw}); } } } return res; }

// from mystl.cpp
template<typename _Key, typename _Tp, typename _Compare=less<_Key>, typename _Alloc=allocator<pair<const _Key, _Tp>>> struct defaultdict : public map<_Key, _Tp, _Compare, _Alloc> { const _Tp init; defaultdict() : init(_Tp()) {}; defaultdict(_Tp init) : init(init) {} _Tp& operator[](const _Key& k) { if (this->count(k)) { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k); } else { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k) = init; } } _Tp& operator[](_Key&& k) { if (this->count(k)) { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k); } else { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k) = init; } } };
template<typename _Key, typename _Compare=less<_Key>, typename _Alloc=allocator<_Key>> struct my_set : public set<_Key, _Compare, _Alloc> { _Key front() { return *this->begin(); } _Key pop_front() { auto res = this->front(); this->erase(this->begin()); return res; } _Key back() { return *this->rbegin(); } _Key pop_back() { auto res = this->back(); this->erase(prev(this->end())); return res; } };
template<typename _Key, typename _Compare=less<_Key>, typename _Alloc=allocator<_Key>> struct my_multiset : public multiset<_Key, _Compare, _Alloc> { _Key front() { return *this->begin(); } _Key pop_front() { auto res = this->front(); this->erase(this->begin()); return res; } _Key back() { return *this->rbegin(); } _Key pop_back() { auto res = this->back(); this->erase(prev(this->end())); return res; } };
template<typename _Tp, typename _Sequence=vector<_Tp>, typename _Compare=less<typename _Sequence::value_type>> struct my_priority_queue : public priority_queue<_Tp, _Sequence, _Compare> { _Tp pop() { auto res = this->top(); priority_queue<_Tp, _Sequence, _Compare>::pop(); return res; } };
template<typename _Tp, typename _Sequence=deque<_Tp>> struct my_queue : public queue<_Tp, _Sequence> { _Tp pop() { auto res = this->front(); queue<_Tp, _Sequence>::pop(); return res; } };
template<typename _Tp, typename _Sequence=deque<_Tp>> struct my_stack : public stack<_Tp, _Sequence> { _Tp pop() { auto res = this->top(); stack<_Tp, _Sequence>::pop(); return res; } };
template<typename _Tp, typename _Alloc=std::allocator<_Tp>> struct my_deque : public deque<_Tp, _Alloc> { _Tp pop_front() { auto res = this->front(); deque<_Tp, _Alloc>::pop_front(); return res; } _Tp pop_back() { auto res = this->back(); deque<_Tp, _Alloc>::pop_back(); return res; } };

// from numbers.cpp
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }
bool is_prime(ll num) { if (num < 2) { return false; } if (set<ll>({2, 3, 5}).count(num)) { return true; } if (num%2 == 0 or num%3 == 0 or num%5 == 0) { return false; } ll prime = 7; ll step = 4; ll num_sqrt = sqrt(num); while (prime <= num_sqrt) { if (num%prime == 0) { return false; } prime += step; step = 6-step; } return true; }
template<typename T> vector<pair<T, int>> factorize(T n) { vector<pair<T, int>> ret; for(T i=2; i*i<=n; i++) { int cnt = 0; while(n % i == 0) { n /= i; cnt++; } if(cnt) ret.emplace_back(i, cnt); } if(n > 1) ret.emplace_back(n, 1); return ret; }
vector<ll> divisors(ll n) { vector<ll> res; for (ll i=1; i*i<=n; i++) { if (n%i == 0) { res.pb(i); if (n/i != i) res.pb(n/i); } } return res; }
ll ntod(string S, ll n) { ll res = 0, k = 1; reverse(ALL(S)); for (char &c : S) { res += k*toint(c); k *= n; } return res; }
string dton(ll num, ll n, char base='0') { string res; while (abs(num) > 0) { ll m = num % abs(n); num -= m; res += base+m; num /= n; } reverse(ALL(res)); if (res != "") { return res; } else { return res+base; } }
ll isqrt(ll n, bool ceil=false) { ll ok = 0; ll ng = 3037000500; while (ng - ok > 1) { ll m = ok + (ng - ok) / 2; if (m * m <= n) { ok = m; } else { ng = m; } } if (ceil and ok*ok != n) ok++; return ok; }
ll digit_sum(ll n) { ll res = 0; while (n > 0) { res += n % 10; n /= 10; } return res; }
ll digit_sum(string S) { ll res = 0; rep(i, S.size()) { res += toint(S[i]); } return res; }
template<typename T> T arithmetic_sequence_sum(T l, T r, T n) { return (l+r)*n/2; }
struct Eratosthenes { int n; vector<bool> prime; vector<ll> minfactor, cntfactor, cntdivisor, sumdivisor; vector<int> mobius; Eratosthenes(int n, bool loglog=true) : n(n) { prime.assign(n+1, true); minfactor.assign(n+1, 0); cntfactor.assign(n+1, 0); mobius.assign(n+1, 1); if (not loglog) { cntdivisor.assign(n+1, 1); sumdivisor.assign(n+1, 1); } prime[0] = prime[1] = false; minfactor[1] = 1; rep(i, 2, n+1) { if (not loglog) { for (ll j=i; j<=n; j+=i) { cntdivisor[j]++; sumdivisor[j] += i; } } if (not prime[i]) continue; minfactor[i] = i; cntfactor[i]++; mobius[i] = -1; for (ll j=i+i; j<=n; j+=i) { prime[j] = false; minfactor[j] = i; cntfactor[i]++; if (j/i%i == 0) { mobius[j] = 0; } else { mobius[j] = -mobius[j]; } } } } vector<pair<ll, int>> factorize(ll x) { vector<pair<ll, int>> res; while (x > 1) { int p = minfactor[x]; int cnt = 0; while (minfactor[x] == p) { x /= p; cnt++; } res.pb({p, cnt}); } return res; } vector<ll> divisors(int n) { vector<ll> res = {1}; auto fact = factorize(n); for (auto [p, cnt] : fact) { ll m = res.size(); rep(i, m) { int v = 1; rep(j, cnt) { v *= p; res.pb(res[i] * v); } } } return res; } vector<ll> get_cntfactor() { return cntfactor; } vector<ll> get_cntdivisor() { return cntdivisor; } vector<ll> get_sumdivisor() { return sumdivisor; } vector<int> get_mobius() { return mobius; } };

// from segment.cpp
template<typename T> struct Accumulate { vector<T> acc; int N; Accumulate() {} Accumulate(int N) : N(N) { acc.resize(N); } Accumulate(const vector<T> &A) { N = A.size(); acc = A; build(); } void set(int i, T a) { acc[i] = a; } void build() { rep(i, N-1) { acc[i+1] += acc[i]; } acc.insert(acc.begin(), 0); } T query(int l, int r) { assert(0 <= l and l <= N and 0 <= r and r <= N); return acc[r]-acc[l]; } T get(int i) { return query(i, i+1); } T operator[](int i){ return query(i, i+1); } ll bisearch_fore(int l, int r, ll x) { if (l > r) return -1; ll l_sm = query(0, l); int ok = r + 1; int ng = l - 1; while (ng+1 < ok) { int mid = (ok+ng) / 2; if (query(0, mid+1) - l_sm >= x) { ok = mid; } else { ng = mid; } } if (ok != r+1) { return ok; } else { return -1; } } ll bisearch_back(int l, int r, ll x) { if (l > r) return -1; ll r_sm = query(0, r+1); int ok = l - 1; int ng = r + 1; while (ok+1 < ng) { int mid = (ok+ng) / 2; if (r_sm - query(0, mid) >= x) { ok = mid; } else { ng = mid; } } if (ok != l-1) { return ok; } else { return -1; } } };
template<typename T> struct BIT { int sz; vector<T> tree; BIT(int n) { n++; sz = 1; while (sz < n) { sz *= 2; } tree.resize(sz); } T sum(int i) { T s = 0; i++; while (i > 0) { s += tree[i-1]; i -= i & -i; } return s; } void add(int i, T x) { i++; while (i <= sz) { tree[i-1] += x; i += i & -i; } } T query(int l, int r) { return sum(r-1) - sum(l-1); } T get(int i) { return query(i, i+1); } void update(int i, T x) { add(i, x - get(i)); } T operator[](int i) { return query(i, i+1); } ll bisearch_fore(int l, int r, ll x) { if (l > r) return -1; ll l_sm = sum(l-1); int ok = r + 1; int ng = l - 1; while (ng+1 < ok) { int mid = (ok+ng) / 2; if (sum(mid) - l_sm >= x) { ok = mid; } else { ng = mid; } } if (ok != r+1) { return ok; } else { return -1; } } ll bisearch_back(int l, int r, ll x) { if (l > r) return -1; ll r_sm = sum(r); int ok = l - 1; int ng = r + 1; while (ok+1 < ng) { int mid = (ok+ng) / 2; if (r_sm - sum(mid-1) >= x) { ok = mid; } else { ng = mid; } } if (ok != l-1) { return ok; } else { return -1; } } };
template<typename T> struct BIT2 { int N; vector<T> data0, data1; BIT2() {}; BIT2(int N) { resize(N); } void resize(int n) { N = ++n; data0.resize(N); data1.resize(N); } void _add(vector<T> &data, int k, T x) { k++; while (k < N) { data[k] += x; k += k & -k; } } T _get(vector<T> &data, int k) { k++; T s = 0; while (k) { s += data[k]; k -= k & -k; } return s; } void add(int l, int r, T x) { _add(data0, l, -x*(l-1)); _add(data0, r, x*(r-1)); _add(data1, l, x); _add(data1, r, -x); } void add(int i, T x) { add(i, i+1, x); } T query(int l, int r) { return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1); } T get(int i) { return query(i, i+1); } void update(int i, T x) { add(i, i+1, x - get(i)); } T operator[](int i) { return query(i, i+1); } ll bisearch_fore(int l, int r, ll x) { if (l > r) return -1; ll l_sm = query(0, l); int ok = r + 1; int ng = l - 1; while (ng+1 < ok) { int mid = (ok+ng) / 2; if (query(0, mid+1) - l_sm >= x) { ok = mid; } else { ng = mid; } } if (ok != r+1) { return ok; } else { return -1; } } ll bisearch_back(int l, int r, ll x) { if (l > r) return -1; ll r_sm = query(0, r+1); int ok = l - 1; int ng = r + 1; while (ok+1 < ng) { int mid = (ok+ng) / 2; if (r_sm - query(0, mid) >= x) { ok = mid; } else { ng = mid; } } if (ok != l-1) { return ok; } else { return -1; } } };
template<typename Monoid, typename F> struct SegmentTree { int sz; vector<Monoid> seg; const F f; const Monoid M1; SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) { sz = 1; while(sz < n) sz <<= 1; seg.assign(2 * sz, M1); } SegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {} void resize(int n) { sz = 1; while(sz < n) sz <<= 1; seg.resize(2 * sz, M1); } void clear() { seg.clear(); } void set(int k, const Monoid &x) { seg[k+sz] = x; } void build() { for(int k = sz - 1; k > 0; k--) { seg[k] = f(seg[2*k], seg[2*k+1]); } } void build(const vector<Monoid> &A) { int n = A.size(); resize(n); rep(i, 0, n) set(i, A[i]); build(); } void update(int k, const Monoid &x) { k += sz; seg[k] = x; while(k >>= 1) { seg[k] = f(seg[2*k], seg[2*k+1]); } } Monoid query(int a, int b) { Monoid L = M1, R = M1; for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) { if(a & 1) L = f(L, seg[a++]); if(b & 1) R = f(seg[--b], R); } return f(L, R); } Monoid operator[](const int &k) const { return seg[k+sz]; } Monoid all() { return seg[1]; } void print(int n) { rep(i, n) { cout << query(i, i+1); if (i == n-1) cout << endl; else cout << ' '; } } template<typename C> int find_subtree(int a, const C &check, Monoid &M, bool type) { while(a < sz) { Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]); if(check(nxt)) a = 2 * a + type; else M = nxt, a = 2 * a + 1 - type; } return a - sz; } template<typename C> int find_first(int a, const C &check) { Monoid L = M1; if(a <= 0) { if(check(f(L, seg[1]))) return find_subtree(1, check, L, false); return -1; } int b = sz; for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) { if(a & 1) { Monoid nxt = f(L, seg[a]); if(check(nxt)) return find_subtree(a, check, L, false); L = nxt; ++a; } } return -1; } template<typename C> int find_last(int b, const C &check) { Monoid R = M1; if(b >= sz) { if(check(f(seg[1], R))) return find_subtree(1, check, R, true); return -1; } int a = sz; for(b += sz; a < b; a >>= 1, b >>= 1) { if(b & 1) { Monoid nxt = f(seg[--b], R); if(check(nxt)) return find_subtree(b, check, R, true); R = nxt; } } return -1; } }; template<typename Monoid, typename F> SegmentTree<Monoid, F> get_segment_tree(int N, const F& f, const Monoid& M1) { return {N, f, M1}; } template<typename Monoid, typename F> SegmentTree<Monoid, F> get_segment_tree(const F& f, const Monoid& M1) { return {f, M1}; }
template<typename Monoid, typename F> struct SegmentTreeIndex { int sz; vector<pair<Monoid, int>> seg; const F f; const Monoid M1; pair<Monoid, int> compare(const pair<Monoid, int> &a, const pair<Monoid, int> &b) { if (a.first == b.first) { if (a.second <= b.second) { return a; } else { return b; } } else if (f(a.first, b.first) == a.first) { return a; } else { return b; } } SegmentTreeIndex(int n, const F f, const Monoid &M1) : f(f), M1(M1) { sz = 1; while(sz < n) sz <<= 1; seg.assign(2 * sz, {M1, -1}); } SegmentTreeIndex(const F f, const Monoid &M1) : f(f), M1(M1) {} void resize(int n) { sz = 1; while(sz < n) sz <<= 1; seg.assign(2 * sz, {M1, -1}); } void set(int k, const Monoid &x) { seg[k+sz] = {x, k}; } void build() { for(int k = sz - 1; k > 0; k--) { seg[k] = compare(seg[2*k], seg[2*k+1]); } } void build(const vector<Monoid> &A) { int n = A.size(); resize(n); rep(i, 0, n) set(i, A[i]); build(); } void update(int k, const Monoid &x) { k += sz; seg[k] = {x, k-sz}; while(k >>= 1) { seg[k] = compare(seg[2*k], seg[2*k+1]); } } void add(int k, const Monoid &x) { update(k, seg[k+sz].first + x); } pair<Monoid, int> query(int a, int b) { pair<Monoid, int> L = {M1, -1}, R = {M1, -1}; for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) { if(a & 1) L = compare(L, seg[a++]); if(b & 1) R = compare(seg[--b], R); } return compare(L, R); } Monoid operator[](const int &k) const { return seg[k+sz].first; } pair<Monoid, int> all() { return seg[1]; } void print(int n) { rep(i, n) { cout << query(i, i+1).first; if (i == n-1) cout << endl; else cout << ' '; } } }; template<typename Monoid, typename F> SegmentTreeIndex<Monoid, F> get_segment_tree_index(int N, const F& f, const Monoid& M1) { return {N, f, M1}; } template<typename Monoid, typename F> SegmentTreeIndex<Monoid, F> get_segment_tree_index(const F& f, const Monoid& M1) { return {f, M1}; }
template<typename F, typename G, typename H, typename Monoid, typename OperatorMonoid> struct LazySegmentTree { int sz, height; vector<Monoid> data; vector<OperatorMonoid> lazy; const F f; const G g; const H h; const Monoid M1; const OperatorMonoid OM0; LazySegmentTree(int n, const F f, const G g, const H h, const Monoid &M1, const OperatorMonoid OM0) : f(f), g(g), h(h), M1(M1), OM0(OM0) { sz = 1; height = 0; while(sz < n) sz <<= 1, height++; data.assign(2 * sz, M1); lazy.assign(2 * sz, OM0); } LazySegmentTree(const F f, const G g, const H h, const Monoid &M1, const OperatorMonoid OM0) : f(f), g(g), h(h), M1(M1), OM0(OM0) {} void set(int k, const Monoid &x) { data[k + sz] = x; } void build() { for(int k = sz - 1; k > 0; k--) { data[k] = f(data[2 * k + 0], data[2 * k + 1]); } } void build(const vector<Monoid> &A) { int n = A.size(); sz = 1; height = 0; while(sz < n) sz <<= 1, height++; data.assign(2 * sz, M1); lazy.assign(2 * sz, OM0); rep(i, n) set(i, A[i]); build(); } inline void propagate(int k) { if(lazy[k] == OM0) return; lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]); lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]); data[k] = apply(k); lazy[k] = OM0; } inline Monoid apply(int k) { return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]); } inline void recalc(int k) { while(k >>= 1) data[k] = f(apply(2 * k + 0), apply(2 * k + 1)); } inline void thrust(int k) { for(int i = height; i > 0; i--) propagate(k >> i); } void update(int a, int b, const OperatorMonoid &x) { if(a >= b) return; thrust(a += sz); thrust(b += sz - 1); for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) { if(l & 1) lazy[l] = h(lazy[l], x), ++l; if(r & 1) --r, lazy[r] = h(lazy[r], x); } recalc(a); recalc(b); } Monoid query(int a, int b) { if(a >= b) return M1; thrust(a += sz); thrust(b += sz - 1); Monoid L = M1, R = M1; for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) { if(l & 1) L = f(L, apply(l++)); if(r & 1) R = f(apply(--r), R); } return f(L, R); } Monoid operator[](const int &k) { return query(k, k + 1); } void update(int i, const OperatorMonoid &x) { update(i, i+1, x); } template<typename P=ll> void print(int n) { rep(i, n) { cout << (P)query(i, i+1); if (i == n-1) cout << endl; else cout << ' '; } } template<typename C> int find_subtree(int a, const C &check, Monoid &M, bool type) { while(a < sz) { propagate(a); Monoid nxt = type ? f(apply(2 * a + type), M) : f(M, apply(2 * a + type)); if(check(nxt)) a = 2 * a + type; else M = nxt, a = 2 * a + 1 - type; } return a - sz; } template<typename C> int find_first(int a, const C &check) { Monoid L = M1; if(a <= 0) { if(check(f(L, apply(1)))) return find_subtree(1, check, L, false); return -1; } thrust(a + sz); int b = sz; for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) { if(a & 1) { Monoid nxt = f(L, apply(a)); if(check(nxt)) return find_subtree(a, check, L, false); L = nxt; ++a; } } return -1; } template<typename C> int find_last(int b, const C &check) { Monoid R = M1; if(b >= sz) { if(check(f(apply(1), R))) return find_subtree(1, check, R, true); return -1; } thrust(b + sz - 1); int a = sz; for(b += sz; a < b; a >>= 1, b >>= 1) { if(b & 1) { Monoid nxt = f(apply(--b), R); if(check(nxt)) return find_subtree(b, check, R, true); R = nxt; } } return -1; } }; template<typename F, typename G, typename H, typename T, typename E> LazySegmentTree<F, G, H, T, E> get_Lazy_segment_tree(const F& f, const G& g, const H& h, const T& ti, const E& ei) { return {f, g, h, ti, ei}; } template<typename F, typename G, typename H, typename T, typename E> LazySegmentTree<F, G, H, T, E> get_Lazy_segment_tree(int N, const F& f, const G& g, const H& h, const T& ti, const E& ei) { return {N, f, g, h, ti, ei}; }

// from strings.cpp
const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;
string replace(string str, const string& replace, const string& with) { if(!replace.empty()) { size_t pos = 0; while ((pos = str.find(replace, pos)) != string::npos) { str.replace(pos, replace.length(), with); pos += with.length(); } } return str; }
string zfill(string str, int len) { string zeros; int n = str.size(); rep(i, len-n) zeros += '0'; return zeros+str; }
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if(res == "") res += '0'; return res; }

const ll MX = 1000007;
BIT<ll> xbit(MX);

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    auto X = LIST(N);
    auto Y = LIST(M);

    vector<pll> P;
    rep(i, K) {
        ll x, y;
        cin >> x >> y;
        P.eb(x, y);
    }

    set<ll> xse, yse;
    rep(i, N) xse.insert(X[i]);
    rep(i, M) yse.insert(Y[i]);
    map<ll, vector<pll>> events;
    rep(i, M) {
        events[Y[i]].eb(0, -1);
    }
    for (auto [x, y] : P) {
        if (not xse.count(x)) events[y].eb(1, x);
        if (not yse.count(y)) events[y].eb(2, x);
    }

    ll ans = 0;
    vector<ll> xvec, yvec(N);
    for (auto& [y, ev] : events) {
        vector<ll> ytmp;
        for (auto& [op, x] : ev) {
            if (op == 0) {
                for (ll xx : xvec) {
                    xbit.add(xx, -1);
                }
                xvec.clear();
            } elif (op == 1) {
                ll i = bisect_left(X, x);
                ans += yvec[i];
                ytmp.eb(i);
            } else {
                ans += xbit.query(0, MX);
                ans -= xbit[x];
                xbit.add(x, 1);
                xvec.eb(x);
            }
        }
        for (ll i : ytmp) {
            yvec[i]++;
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
