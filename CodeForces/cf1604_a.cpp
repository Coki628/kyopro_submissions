/*
・きっちり自力AC！
・自由な操作が許されているが、結局は先頭に小さいのを詰めてくのが最善。
　それでボトルネックになる場所が答え。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

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
template<int mod> struct ModInt { int x; ModInt() : x(0) {} ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {} ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; } ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; } ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; } ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; } ModInt operator-() const { return ModInt(-x); } ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; } ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; } ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; } ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; } bool operator==(const ModInt &p) const { return x == p.x; } bool operator!=(const ModInt &p) const { return x != p.x; } ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); } ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; } friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; } friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); } static int get_mod() { return mod; } };
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
template<typename _Key, typename _Compare=less<_Key>, typename _Alloc=allocator<_Key>> struct my_set : public set<_Key, _Compare, _Alloc> { _Key front() { return *this->begin(); } _Key pop_front() { auto res = this->front(); this->erase(this->begin()); return res; } _Key back() { return *this->rbegin(); } _Key pop_back() { auto res = this->back(); this->erase(prev(this->end())); return res; } };
template<typename _Key, typename _Compare=less<_Key>, typename _Alloc=allocator<_Key>> struct my_multiset : public multiset<_Key, _Compare, _Alloc> { _Key front() { return *this->begin(); } _Key pop_front() { auto res = this->front(); this->erase(this->begin()); return res; } _Key back() { return *this->rbegin(); } _Key pop_back() { auto res = this->back(); this->erase(prev(this->end())); return res; } };
template<typename _Tp, typename _Sequence=vector<_Tp>, typename _Compare=less<typename _Sequence::value_type>> struct my_priority_queue : public priority_queue<_Tp, _Sequence, _Compare> { _Tp pop() { auto res = this->top(); priority_queue<_Tp, _Sequence, _Compare>::pop(); return res; } };
template<typename _Tp, typename _Sequence=deque<_Tp>> struct my_queue : public queue<_Tp, _Sequence> { _Tp pop() { auto res = this->front(); queue<_Tp, _Sequence>::pop(); return res; } };
template<typename _Tp, typename _Alloc=std::allocator<_Tp>> struct my_deque : public deque<_Tp, _Alloc> { _Tp pop_front() { auto res = this->front(); deque<_Tp, _Alloc>::pop_front(); return res; } _Tp pop_back() { auto res = this->back(); deque<_Tp, _Alloc>::pop_back(); return res; } };

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
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if(res == "") res += '0'; return res; }

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll ans = 0;
    rep(i, N) {
        chmax(ans, A[i]-(i+1));
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
