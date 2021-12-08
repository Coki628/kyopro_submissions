/*
参考：https://tsuchi.hateblo.jp/entry/2021/10/09/124804
　　　https://ei1333.github.io/library/
　　　https://atcoder.jp/contests/arc118/submissions/22491460
・ライブラリ整備：BM、復元
・普通の10^9くらいのmodより大きくなるものを求めるには復元が必要になる。
　(試しにでかい素数modにしたらダメだった。。)
・これは別の素数modで2回やって、Garnerのアルゴリズムで突き合わせるとできる。
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
using pil = pair<int, ll>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
using vvpil = vector<vector<pil>>;
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(const vector<T> &A) { rep(i, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(const deque<T> &A) { vector<T> V(A.begin(), A.end()); print(V); }
template<typename T> void print(const set<T> &S) { vector<T> A(S.begin(), S.end()); print(A); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

// from common.cpp
ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
ll floor(ll a, ll b) { if (a < 0) return (a-b+1) / b; else return a / b; }
ll ceil(ll a, ll b) { if (a >= 0) return (a+b-1) / b; else return a / b; }
ll modulo(ll a, ll b) { return ((a % b) + b) % b; }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }
template<typename T> T sum(const vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename key, typename val> val sum(const map<key, val> &mp) { val res = 0; for (auto [k, v] : mp) res += v; return res; }
template<typename T> T max(const vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(const vector<T> &A) { return *min_element(ALL(A)); }
ll pow(int x, int n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(int x, ll n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(ll x, int n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(ll x, ll n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { x %= mod; ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }
int popcount(ll S) { return __builtin_popcountll(S); }
int bit_length(ll x) { return x != 0 ? floor(log2((ld)x))+1 : 0; }
template<typename T> int bisect_left(const vector<T> &A, T val, int lo=0) { return lower_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> int bisect_right(const vector<T> &A, T val, int lo=0) { return upper_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> map<T, ll> Counter(const vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
template<typename T> vector<ll> Counter(const vector<T> &A, T mx) { vector<ll> res(mx+1); for (T a : A) { res[a]++; } return res; }
map<char, ll> Counter(const string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(const vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }
template<typename T1, typename T2, typename T3> tuple<vector<T1>, vector<T2>, vector<T3>> zip(const vector<tuple<T1, T2, T3>> &A) { int N = A.size(); tuple<vector<T1>, vector<T2>, vector<T3>> res = {vector<T1>(N), vector<T2>(N), vector<T3>(N)}; rep(i, N) { get<0>(res)[i] = get<0>(A[i]); get<1>(res)[i] = get<1>(A[i]); get<2>(res)[i] = get<2>(A[i]); } return res; }
template<typename T> struct Compress { int N; vector<T> dat; Compress(vector<T> A) { sort(A.begin(), A.end()); A.erase(unique(A.begin(), A.end()), A.end()); N = A.size(); dat = A; } int zip(T x) { return bisect_left(dat, x); } T unzip(int x) { return dat[x]; } int operator[](T x) { return zip(x); } int size() { return dat.size(); } vector<T> zip(const vector<T> &A) { int M = A.size(); vector<T> res(M); rep(i, M) res[i] = zip(A[i]); return res; } };
template<typename T> vector<pair<T, int>> RLE(const vector<T> &A) { if (A.empty()) return {}; int N = A.size(); vector<pair<T, int>> res; T cur = A[0]; int cnt = 1; rep(i, 1, N) { if (A[i] == A[i-1]) { cnt++; } else { res.pb({cur, cnt}); cnt = 1; cur = A[i]; } } res.pb({cur, cnt}); return res; }
vector<pair<char, int>> RLE(const string &S) { if (S.empty()) return {}; int N = S.size(); vector<pair<char, int>> res; char cur = S[0]; int cnt = 1; rep(i, 1, N) { if (S[i] == S[i-1]) { cnt++; } else { res.pb({cur, cnt}); cnt = 1; cur = S[i]; } } res.pb({cur, cnt}); return res; }
bool mul_overflow(ll x, ll y) { ll z; return __builtin_mul_overflow(x, y, &z); }
vector<ll> split(const string &S, char separator) { int N = S.size(); vector<ll> res; string cur; rep(i, N) { if (S[i] == separator) { res.eb(toint(cur)); cur = ""; } else { cur += S[i]; } } if (cur.size()) res.eb(toint(cur)); return res; }
string to_string(const string &S) { return S; }
string to_string(char c) { return {c}; }
template<typename T> string join(const vector<T> &A, char separator=0) { int N = A.size(); string res; rep(i, N) { res += tostr(A[i]); if (separator != 0 and i != N-1) res += separator; } return res; }

// from combinatorics.cpp
template<int mod>
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator++() {
        x++;
        if (x == mod) x = 0;
        return *this;
    }

    ModInt &operator--() {
        if (x == 0) x = mod;
        x--;
        return *this;
    }

    ModInt &operator+=(const ModInt &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator++(int) {
        ModInt result = *this;
        ++*this;
        return result;
    }

    ModInt operator--(int) {
        ModInt result = *this;
        --*this;
        return result;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while(b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while(n > 0) {
            if(n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    static int get_mod() { return mod; }

    operator ll() const { return x; }
};
using mint = ModInt<MOD>;
template<typename T=mint> struct ModTools { int MAX; vector<T> fact, factinv; ModTools() {}; ModTools(int mx) { build(mx); } void build(int mx) { MAX = ++mx; fact.resize(MAX); factinv.resize(MAX); fact[0] = fact[1] = 1; rep(i, 2, MAX) { fact[i] = fact[i-1] * i; } factinv[MAX-1] = (T)1 / fact[MAX-1]; rep(i, MAX-2, -1, -1) { factinv[i] = factinv[i+1] * (i+1); } } T factorial(int x) { return fact[x]; } T inverse(int x) { return factinv[x]; } T nCr(int n, int r) { if (n < r or r < 0) return 0; r = min(r, n-r); T num = fact[n]; T den = factinv[r] * factinv[n-r]; return num * den; } T nHr(int n, int r) { return nCr(r+n-1, r); } T nPr(int n, int r) { if (n < r or r < 0) return 0; return fact[n] * factinv[n-r]; } };
template<typename T> vector<vector<T>> permutations(const vector<T> &A, int N=-1) { if (N == -1) N = A.size(); int M = A.size(); vector<vector<T>> comb; rep(bit, 1<<M) { if (popcount(bit) != N) continue; vector<T> res; rep(i, M) { if (bit>>i & 1) { res.pb(A[i]); } } comb.pb(res); } vector<vector<T>> res; for (auto &perm : comb) { sort(ALL(perm)); do { res.pb(perm); } while (next_permutation(ALL(perm))); } return res; }
template<typename T> vector<vector<T>> combinations(const vector<T> &A, int N) { int M = A.size(); vector<vector<T>> res; auto rec = [&](auto&& f, vector<T> &cur, ll x, ll n) -> void { if (n == N) { res.pb(cur); return; } rep(i, x, M) { cur.pb(A[i]); f(f, cur, i+1, n+1); cur.pop_back(); } }; vector<T> cur; rec(rec, cur, 0, 0); return res; }
template<typename T> T factorial(T x) { T res = 1; for (T i=1; i<=x; i++) res *= i; return res; }

// from graph.cpp
struct UnionFind { int n, groupcnt; vector<int> par, rank, sz; vector<bool> tree; UnionFind(int n) : n(n) { par.resize(n); rank.resize(n); sz.resize(n, 1); tree.resize(n, 1); rep(i, n) par[i] = i; groupcnt = n; } UnionFind() {} void resize(int _n) { n = _n; par.resize(n); rank.resize(n); sz.resize(n, 1); rep(i, n) par[i] = i; groupcnt = n; } int find(int x) { if (par[x] == x) { return x; } else { par[x] = find(par[x]); return par[x]; } } int merge(int a, int b) { int x = find(a); int y = find(b); if (x == y) { tree[x] = false; return x; } if (!tree[x] or !tree[y]) { tree[x] = tree[y] = false; } groupcnt--; if (rank[x] < rank[y]) { par[x] = y; sz[y] += sz[x]; return y; } else { par[y] = x; sz[x] += sz[y]; if (rank[x] == rank[y]) { rank[x]++; } return x; } } bool same(int a, int b) { return find(a) == find(b); } ll size(int x) { return sz[find(x)]; } int size() { return groupcnt; } bool is_tree(int x) { return tree[find(x)]; } set<int> get_roots() { set<int> res; rep(i, n) { res.insert(find(i)); } return res; } };

// from grid.cpp
const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
ll gridtoid(ll i, ll j, ll W) { return i*W+j; }
pll idtogrid(ll id, ll W) { return divmod(id, W); }
template<typename T> vector<vector<T>> transpose(const vector<vector<T>> &grid) { int H = grid.size(); int W = grid[0].size(); auto res = list2d(W, H, (T)0); rep(i, H) { rep(j, W) { res[j][i] = grid[i][j]; } } return res; }
vector<string> transpose(const vector<string> &grid) { int H = grid.size(); int W = grid[0].size(); vector<string> res(W, string(H, '*')); rep(i, H) { rep(j, W) { res[j][i] = grid[i][j]; } } return res; }
vector<string> rot90(const vector<string> &grid) { int H = grid.size(); int W = grid[0].size(); vector<string> res(W, string(H, '*')); rep(i, H) { rep(j, W) { res[j][H-i-1] = grid[i][j]; } } return res; }

// from mystl.cpp
template<typename _Key, typename _Tp, typename _Compare=less<_Key>, typename _Alloc=allocator<pair<const _Key, _Tp>>> struct defaultdict : public map<_Key, _Tp, _Compare, _Alloc> { const _Tp init; defaultdict() : init(_Tp()) {}; defaultdict(_Tp init) : init(init) {} _Tp& operator[](const _Key& k) { if (this->count(k)) { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k); } else { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k) = init; } } _Tp& operator[](_Key&& k) { if (this->count(k)) { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k); } else { return map<_Key, _Tp, _Compare, _Alloc>::operator[](k) = init; } } };

// from numbers.cpp
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }
template<typename T> vector<pair<T, int>> factorize(T n) { vector<pair<T, int>> ret; for(T i=2; i*i<=n; i++) { int cnt = 0; while(n % i == 0) { n /= i; cnt++; } if(cnt) ret.emplace_back(i, cnt); } if(n > 1) ret.emplace_back(n, 1); return ret; }
vector<ll> divisors(ll n) { vector<ll> res; for (ll i=1; i*i<=n; i++) { if (n%i == 0) { res.pb(i); if (n/i != i) res.pb(n/i); } } return res; }
ll ntod(string S, ll n) { ll res = 0, k = 1; reverse(ALL(S)); for (char &c : S) { res += k*toint(c); k *= n; } return res; }
string dton(ll num, ll n, char base='0') { string res; while (abs(num) > 0) { ll m = num % abs(n); num -= m; res += base+m; num /= n; } reverse(ALL(res)); if (res != "") { return res; } else { return res+base; } }
ll isqrt(ll n, bool ceil=false) { ll ok = 0; ll ng = 3037000500; while (ng - ok > 1) { ll m = ok + (ng - ok) / 2; if (m * m <= n) { ok = m; } else { ng = m; } } if (ceil and ok*ok != n) ok++; return ok; }
ll digit_sum(ll n) { ll res = 0; while (n > 0) { res += n % 10; n /= 10; } return res; }
ll digit_sum(string S) { ll res = 0; rep(i, S.size()) { res += toint(S[i]); } return res; }

// from segment.cpp
template<typename T> struct Accumulate { vector<T> acc; int N; Accumulate() {} Accumulate(int N) : N(N) { acc.resize(N); } Accumulate(const vector<T> &A) { N = A.size(); acc = A; build(); } void set(int i, T a) { acc[i] = a; } void build() { rep(i, N-1) { acc[i+1] += acc[i]; } acc.insert(acc.begin(), 0); } T query(int l, int r) { assert(0 <= l and l <= N and 0 <= r and r <= N); return acc[r]-acc[l]; } T get(int i) { return query(i, i+1); } T operator[](int i){ return query(i, i+1); } ll bisearch_fore(int l, int r, ll x) { if (l > r) return -1; ll l_sm = query(0, l); int ok = r + 1; int ng = l - 1; while (ng+1 < ok) { int mid = (ok+ng) / 2; if (query(0, mid+1) - l_sm >= x) { ok = mid; } else { ng = mid; } } if (ok != r+1) { return ok; } else { return -1; } } ll bisearch_back(int l, int r, ll x) { if (l > r) return -1; ll r_sm = query(0, r+1); int ok = l - 1; int ng = r + 1; while (ok+1 < ng) { int mid = (ok+ng) / 2; if (r_sm - query(0, mid) >= x) { ok = mid; } else { ng = mid; } } if (ok != l-1) { return ok; } else { return -1; } } };
template<typename T> struct BIT { int sz; vector<T> tree; BIT(int n) { n++; sz = 1; while (sz < n) { sz *= 2; } tree.resize(sz); } T sum(int i) { T s = 0; i++; while (i > 0) { s += tree[i-1]; i -= i & -i; } return s; } void add(int i, T x) { i++; while (i <= sz) { tree[i-1] += x; i += i & -i; } } T query(int l, int r) { return sum(r-1) - sum(l-1); } T get(int i) { return query(i, i+1); } void update(int i, T x) { add(i, x - get(i)); } T operator[](int i) { return query(i, i+1); } void print(int n) { rep(i, n) { cout << query(i, i+1); if (i == n-1) cout << endl; else cout << ' '; } } ll bisearch_fore(int l, int r, ll x) { if (l > r) return -1; ll l_sm = sum(l-1); int ok = r + 1; int ng = l - 1; while (ng+1 < ok) { int mid = (ok+ng) / 2; if (sum(mid) - l_sm >= x) { ok = mid; } else { ng = mid; } } if (ok != r+1) { return ok; } else { return -1; } } ll bisearch_back(int l, int r, ll x) { if (l > r) return -1; ll r_sm = sum(r); int ok = l - 1; int ng = r + 1; while (ok+1 < ng) { int mid = (ok+ng) / 2; if (r_sm - sum(mid-1) >= x) { ok = mid; } else { ng = mid; } } if (ok != l-1) { return ok; } else { return -1; } } };
template<typename Monoid, typename F> struct SegmentTree { int sz; vector<Monoid> seg; const F f; const Monoid M1; SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) { sz = 1; while(sz < n) sz <<= 1; seg.assign(2 * sz, M1); } SegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {} void resize(int n) { sz = 1; while(sz < n) sz <<= 1; seg.resize(2 * sz, M1); } void clear() { seg.clear(); } void set(int k, const Monoid &x) { seg[k+sz] = x; } void build() { for(int k = sz - 1; k > 0; k--) { seg[k] = f(seg[2*k], seg[2*k+1]); } } void build(const vector<Monoid> &A) { int n = A.size(); resize(n); rep(i, 0, n) set(i, A[i]); build(); } void update(int k, const Monoid &x) { k += sz; seg[k] = x; while(k >>= 1) { seg[k] = f(seg[2*k], seg[2*k+1]); } } Monoid query(int a, int b) { Monoid L = M1, R = M1; for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) { if(a & 1) L = f(L, seg[a++]); if(b & 1) R = f(seg[--b], R); } return f(L, R); } Monoid operator[](const int &k) const { return seg[k+sz]; } Monoid all() { return seg[1]; } void print(int n) { rep(i, n) { cout << query(i, i+1); if (i == n-1) cout << endl; else cout << ' '; } } template<typename C> int find_subtree(int a, const C &check, Monoid &M, bool type) { while(a < sz) { Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]); if(check(nxt)) a = 2 * a + type; else M = nxt, a = 2 * a + 1 - type; } return a - sz; } template<typename C> int find_first(int a, const C &check) { Monoid L = M1; if(a <= 0) { if(check(f(L, seg[1]))) return find_subtree(1, check, L, false); return -1; } int b = sz; for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) { if(a & 1) { Monoid nxt = f(L, seg[a]); if(check(nxt)) return find_subtree(a, check, L, false); L = nxt; ++a; } } return -1; } template<typename C> int find_last(int b, const C &check) { Monoid R = M1; if(b >= sz) { if(check(f(seg[1], R))) return find_subtree(1, check, R, true); return -1; } int a = sz; for(b += sz; a < b; a >>= 1, b >>= 1) { if(b & 1) { Monoid nxt = f(seg[--b], R); if(check(nxt)) return find_subtree(b, check, R, true); R = nxt; } } return -1; } }; template<typename Monoid, typename F> SegmentTree<Monoid, F> get_segment_tree(int N, const F& f, const Monoid& M1) { return {N, f, M1}; } template<typename Monoid, typename F> SegmentTree<Monoid, F> get_segment_tree(const F& f, const Monoid& M1) { return {f, M1}; }

// from strings.cpp
const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;
string replace(string str, const string& replace, const string& with) { if(!replace.empty()) { size_t pos = 0; while ((pos = str.find(replace, pos)) != string::npos) { str.replace(pos, replace.length(), with); pos += with.length(); } } return str; }
string zfill(string str, int len) { string zeros; int n = str.size(); rep(i, len-n) zeros += '0'; return zeros+str; }
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if (res == "") res += '0'; return res; }

namespace FastFourierTransform {
    using real = double;

    struct C {
        real x, y;

        C() : x(0), y(0) {}

        C(real x, real y) : x(x), y(y) {}

        inline C operator+(const C &c) const { return C(x + c.x, y + c.y); }

        inline C operator-(const C &c) const { return C(x - c.x, y - c.y); }

        inline C operator*(const C &c) const { return C(x * c.x - y * c.y, x * c.y + y * c.x); }

        inline C conj() const { return C(x, -y); }
    };

    const real PI = acosl(-1);
    int base = 1;
    vector< C > rts = { {0, 0},
                                         {1, 0} };
    vector< int > rev = {0, 1};


    void ensure_base(int nbase) {
        if(nbase <= base) return;
        rev.resize(1 << nbase);
        rts.resize(1 << nbase);
        for(int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        while(base < nbase) {
            real angle = PI * 2.0 / (1 << (base + 1));
            for(int i = 1 << (base - 1); i < (1 << base); i++) {
                rts[i << 1] = rts[i];
                real angle_i = angle * (2 * i + 1 - (1 << base));
                rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
            }
            ++base;
        }
    }

    void fft(vector< C > &a, int n) {
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for(int i = 0; i < n; i++) {
            if(i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for(int k = 1; k < n; k <<= 1) {
            for(int i = 0; i < n; i += 2 * k) {
                for(int j = 0; j < k; j++) {
                    C z = a[i + j + k] * rts[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }

    vector< int64_t > multiply(const vector< int > &a, const vector< int > &b) {
        int need = (int) a.size() + (int) b.size() - 1;
        int nbase = 1;
        while((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        vector< C > fa(sz);
        for(int i = 0; i < sz; i++) {
            int x = (i < (int) a.size() ? a[i] : 0);
            int y = (i < (int) b.size() ? b[i] : 0);
            fa[i] = C(x, y);
        }
        fft(fa, sz);
        C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
        for(int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
            fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
            fa[i] = z;
        }
        for(int i = 0; i < (sz >> 1); i++) {
            C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
            C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz >> 1) + i];
            fa[i] = A0 + A1 * s;
        }
        fft(fa, sz >> 1);
        vector< int64_t > ret(need);
        for(int i = 0; i < need; i++) {
            ret[i] = llround(i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
        }
        return ret;
    }
};

/*
 * @brief Arbitrary Mod Convolution(任意mod畳み込み)
 */
template< typename T >
struct ArbitraryModConvolution {
    using real = FastFourierTransform::real;
    using C = FastFourierTransform::C;

    ArbitraryModConvolution() = default;

    static vector< T > multiply(const vector< T > &a, const vector< T > &b, int need = -1) {
        if(need == -1) need = a.size() + b.size() - 1;
        int nbase = 0;
        while((1 << nbase) < need) nbase++;
        FastFourierTransform::ensure_base(nbase);
        int sz = 1 << nbase;
        vector< C > fa(sz);
        for(int i = 0; i < a.size(); i++) {
            fa[i] = C(a[i].x & ((1 << 15) - 1), a[i].x >> 15);
        }
        fft(fa, sz);
        vector< C > fb(sz);
        if(a == b) {
            fb = fa;
        } else {
            for(int i = 0; i < b.size(); i++) {
                fb[i] = C(b[i].x & ((1 << 15) - 1), b[i].x >> 15);
            }
            fft(fb, sz);
        }
        real ratio = 0.25 / sz;
        C r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
        for(int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            C a1 = (fa[i] + fa[j].conj());
            C a2 = (fa[i] - fa[j].conj()) * r2;
            C b1 = (fb[i] + fb[j].conj()) * r3;
            C b2 = (fb[i] - fb[j].conj()) * r4;
            if(i != j) {
                C c1 = (fa[j] + fa[i].conj());
                C c2 = (fa[j] - fa[i].conj()) * r2;
                C d1 = (fb[j] + fb[i].conj()) * r3;
                C d2 = (fb[j] - fb[i].conj()) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        fft(fa, sz);
        fft(fb, sz);
        vector< T > ret(need);
        for(int i = 0; i < need; i++) {
            int64_t aa = llround(fa[i].x);
            int64_t bb = llround(fb[i].x);
            int64_t cc = llround(fa[i].y);
            aa = T(aa).x, bb = T(bb).x, cc = T(cc).x;
            ret[i] = aa + (bb << 15) + (cc << 30);
        }
        return ret;
    }
};

/**
 * @brief Formal Power Series(形式的冪級数)
 */
template< typename T >
struct FormalPowerSeries : vector< T > {
    using vector< T >::vector;
    using P = FormalPowerSeries;
    using Conv = ArbitraryModConvolution< T >;

    P pre(int deg) const {
        return P(begin(*this), begin(*this) + min((int) this->size(), deg));
    }

    P rev(int deg = -1) const {
        P ret(*this);
        if(deg != -1) ret.resize(deg, T(0));
        reverse(begin(ret), end(ret));
        return ret;
    }

    void shrink() {
        while(this->size() && this->back() == T(0)) this->pop_back();
    }

    P operator+(const P &r) const { return P(*this) += r; }

    P operator+(const T &v) const { return P(*this) += v; }

    P operator-(const P &r) const { return P(*this) -= r; }

    P operator-(const T &v) const { return P(*this) -= v; }

    P operator*(const P &r) const { return P(*this) *= r; }

    P operator*(const T &v) const { return P(*this) *= v; }

    P operator/(const P &r) const { return P(*this) /= r; }

    P operator%(const P &r) const { return P(*this) %= r; }

    P &operator+=(const P &r) {
        if(r.size() > this->size()) this->resize(r.size());
        for(int i = 0; i < r.size(); i++) (*this)[i] += r[i];
        return *this;
    }

    P &operator-=(const P &r) {
        if(r.size() > this->size()) this->resize(r.size());
        for(int i = 0; i < r.size(); i++) (*this)[i] -= r[i];
        return *this;
    }

    // https://judge.yosupo.jp/problem/convolution_mod
    P &operator*=(const P &r) {
        if(this->empty() || r.empty()) {
            this->clear();
            return *this;
        }
        auto ret = Conv::multiply(*this, r);
        return *this = {begin(ret), end(ret)};
    }

    P &operator/=(const P &r) {
        if(this->size() < r.size()) {
            this->clear();
            return *this;
        }
        int n = this->size() - r.size() + 1;
        return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
    }

    P &operator%=(const P &r) {
        return *this -= *this / r * r;
    }

    // https://judge.yosupo.jp/problem/division_of_polynomials
    pair< P, P > div_mod(const P &r) {
        P q = *this / r;
        return make_pair(q, *this - q * r);
    }

    P operator-() const {
        P ret(this->size());
        for(int i = 0; i < this->size(); i++) ret[i] = -(*this)[i];
        return ret;
    }

    P &operator+=(const T &r) {
        if(this->empty()) this->resize(1);
        (*this)[0] += r;
        return *this;
    }

    P &operator-=(const T &r) {
        if(this->empty()) this->resize(1);
        (*this)[0] -= r;
        return *this;
    }

    P &operator*=(const T &v) {
        for(int i = 0; i < this->size(); i++) (*this)[i] *= v;
        return *this;
    }

    P dot(P r) const {
        P ret(min(this->size(), r.size()));
        for(int i = 0; i < ret.size(); i++) ret[i] = (*this)[i] * r[i];
        return ret;
    }

    P operator>>(int sz) const {
        if(this->size() <= sz) return {};
        P ret(*this);
        ret.erase(ret.begin(), ret.begin() + sz);
        return ret;
    }

    P operator<<(int sz) const {
        P ret(*this);
        ret.insert(ret.begin(), sz, T(0));
        return ret;
    }

    T operator()(T x) const {
        T r = 0, w = 1;
        for(auto &v : *this) {
            r += w * v;
            w *= x;
        }
        return r;
    }

    P diff() const {
        const int n = (int) this->size();
        P ret(max(0, n - 1));
        for(int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);
        return ret;
    }

    P integral() const {
        const int n = (int) this->size();
        P ret(n + 1);
        ret[0] = T(0);
        for(int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);
        return ret;
    }

    // https://judge.yosupo.jp/problem/inv_of_formal_power_series
    // F(0) must not be 0
    P inv(int deg = -1) const {
        assert(((*this)[0]) != T(0));
        const int n = (int) this->size();
        if(deg == -1) deg = n;
        P ret({T(1) / (*this)[0]});
        for(int i = 1; i < deg; i <<= 1) {
            ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);
        }
        return ret.pre(deg);
    }

    // https://judge.yosupo.jp/problem/log_of_formal_power_series
    // F(0) must be 1
    P log(int deg = -1) const {
        assert((*this)[0] == T(1));
        const int n = (int) this->size();
        if(deg == -1) deg = n;
        return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
    }

    // https://judge.yosupo.jp/problem/sqrt_of_formal_power_series
    P sqrt(int deg = -1, const function< T(T) > &get_sqrt = [](T) { return T(1); }) const {
        const int n = (int) this->size();
        if(deg == -1) deg = n;
        if((*this)[0] == T(0)) {
            for(int i = 1; i < n; i++) {
                if((*this)[i] != T(0)) {
                    if(i & 1) return {};
                    if(deg - i / 2 <= 0) break;
                    auto ret = (*this >> i).sqrt(deg - i / 2, get_sqrt);
                    if(ret.empty()) return {};
                    ret = ret << (i / 2);
                    if(ret.size() < deg) ret.resize(deg, T(0));
                    return ret;
                }
            }
            return P(deg, 0);
        }
        auto sqr = T(get_sqrt((*this)[0]));
        if(sqr * sqr != (*this)[0]) return {};
        P ret{sqr};
        T inv2 = T(1) / T(2);
        for(int i = 1; i < deg; i <<= 1) {
            ret = (ret + pre(i << 1) * ret.inv(i << 1)) * inv2;
        }
        return ret.pre(deg);
    }

    P sqrt(const function< T(T) > &get_sqrt, int deg = -1) const {
        return sqrt(deg, get_sqrt);
    }

    // https://judge.yosupo.jp/problem/exp_of_formal_power_series
    // F(0) must be 0
    P exp(int deg = -1) const {
        if(deg == -1) deg = this->size();
        assert((*this)[0] == T(0));
        const int n = (int) this->size();
        if(deg == -1) deg = n;
        P ret({T(1)});
        for(int i = 1; i < deg; i <<= 1) {
            ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);
        }
        return ret.pre(deg);
    }

    // https://judge.yosupo.jp/problem/pow_of_formal_power_series
    P pow(int64_t k, int deg = -1) const {
        const int n = (int) this->size();
        if(deg == -1) deg = n;
        for(int i = 0; i < n; i++) {
            if((*this)[i] != T(0)) {
                T rev = T(1) / (*this)[i];
                P ret = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));
                if(i * k > deg) return P(deg, T(0));
                ret = (ret << (i * k)).pre(deg);
                if(ret.size() < deg) ret.resize(deg, T(0));
                return ret;
            }
        }
        return *this;
    }

    // https://yukicoder.me/problems/no/215
    P mod_pow(int64_t k, P g) const {
        P modinv = g.rev().inv();
        auto get_div = [&](P base) {
            if(base.size() < g.size()) {
                base.clear();
                return base;
            }
            int n = base.size() - g.size() + 1;
            return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);
        };
        P x(*this), ret{1};
        while(k > 0) {
            if(k & 1) {
                ret *= x;
                ret -= get_div(ret) * g;
                ret.shrink();
            }
            x *= x;
            x -= get_div(x) * g;
            x.shrink();
            k >>= 1;
        }
        return ret;
    }

    // https://judge.yosupo.jp/problem/polynomial_taylor_shift
    P taylor_shift(T c) const {
        int n = (int) this->size();
        vector< T > fact(n), rfact(n);
        fact[0] = rfact[0] = T(1);
        for(int i = 1; i < n; i++) fact[i] = fact[i - 1] * T(i);
        rfact[n - 1] = T(1) / fact[n - 1];
        for(int i = n - 1; i > 1; i--) rfact[i - 1] = rfact[i] * T(i);
        P p(*this);
        for(int i = 0; i < n; i++) p[i] *= fact[i];
        p = p.rev();
        P bs(n, T(1));
        for(int i = 1; i < n; i++) bs[i] = bs[i - 1] * c * rfact[i] * fact[i - 1];
        p = (p * bs).pre(n);
        p = p.rev();
        for(int i = 0; i < n; i++) p[i] *= rfact[i];
        return p;
    }
};
template< typename Mint >
using FPS = FormalPowerSeries< Mint >;

/**
 * @brief Coeff of Rational Function
 * @docs docs/coeff-of-rational-function.md
 */
template< template< typename > class FPS, typename Mint >
Mint coeff_of_rational_function(FPS< Mint > P, FPS< Mint > Q, int64_t k) {
    // compute the coefficient [x^k] P/Q of rational power series
    Mint ret = 0;
    if(P.size() >= Q.size()) {
        auto R = P / Q;
        P -= R * Q;
        P.shrink();
        if(k < (int) R.size()) ret += R[k];
    }
    if(P.empty()) return ret;
    P.resize((int) Q.size() - 1);
    auto sub = [&](const FPS< Mint > &as, bool odd) {
        FPS< Mint > bs((as.size() + !odd) / 2);
        for(int i = odd; i < (int) as.size(); i += 2) bs[i >> 1] = as[i];
        return bs;
    };
    while(k > 0) {
        auto Q2(Q);
        for(int i = 1; i < (int) Q2.size(); i += 2) Q2[i] = -Q2[i];
        P = sub(P * Q2, k & 1);
        Q = sub(Q * Q2, 0);
        k >>= 1;
    }
    return ret + P[0];
}

/**
 * @brief Kth Term of Linearly Recurrent Sequence
 * @docs docs/kth-term-of-linearly-recurrent-sequence.md
 */
template< template< typename > class FPS, typename Mint >
Mint kth_term_of_linearly_recurrent_sequence(const FPS< Mint > &a, FPS< Mint > c, int64_t k) {
    assert(a.size() == c.size());
    c = FPS< Mint >{1} - (c << 1);
    return coeff_of_rational_function((a * c).pre(a.size()), c, k);
}

/**
 * @brief Berlekamp Massey
 */
template< template< typename > class FPS, typename Mint >
FPS< Mint > berlekamp_massey(const FPS< Mint > &s) {
    const int N = (int) s.size();
    FPS< Mint > b = {Mint(-1)}, c = {Mint(-1)};
    Mint y = Mint(1);
    for(int ed = 1; ed <= N; ed++) {
        int l = int(c.size()), m = int(b.size());
        Mint x = 0;
        for(int i = 0; i < l; i++) x += c[i] * s[ed - l + i];
        b.emplace_back(0);
        m++;
        if(x == Mint(0)) continue;
        Mint freq = x / y;
        if(l < m) {
            auto tmp = c;
            c.insert(begin(c), m - l, Mint(0));
            for(int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];
            b = tmp;
            y = x;
        } else {
            for(int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];
        }
    }
    return c;
}

template<template<typename> class FPS, typename Mint>
Mint BM(FPS<Mint> A, ll K) {
    auto bm = berlekamp_massey(A);
    bm.pop_back();
    reverse(ALL(bm));
    A.resize(bm.size());
    return kth_term_of_linearly_recurrent_sequence(A, bm, K);
}

constexpr int m1 = 998244353;
constexpr int m2 = 1004535809;
constexpr int inv_m1_mod_m2 = 669690699;
using mint1 = ModInt<m1>;
using mint2 = ModInt<m2>;

long long garner(long long r1, long long r2) {
    long long t = (r2 - r1) * inv_m1_mod_m2;
    while (t < 0) t += m2;
    t %= m2;
    r1 += t * m1;
    return r1;
}

void solve() {
    ll t, K;
    cin >> t >> K;

    auto calc = [&](ll a) {
        return (100+t)*a/100;
    };
    ll N = 100;
    FPS<mint1> A;
    FPS<mint2> B;
    ll a = 0;
    while (A.size() < N) {
        if (calc(a)+1 < calc(a+1)) {
            A.eb(calc(a)+1);
            B.eb(calc(a)+1);
        }
        a++;
    }

    auto res1 = BM(A, K-1);
    auto res2 = BM(B, K-1);
    auto ans = garner(res1, res2);
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
