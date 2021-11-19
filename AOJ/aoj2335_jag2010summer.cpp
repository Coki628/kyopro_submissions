/*
参考：https://mayokoex.hatenablog.com/entry/2015/09/06/112749
　　　https://kanpurin.hatenablog.com/entry/2021/06/13/224011
　　　https://a-iine.net/catalan/
・新履修：カタラン数、nCr系数え上げ、直線の対称点
・考察むずい。知らなきゃ解けないけど、聞いても理解にしばらく時間かかった。
・この問題はグリッドの経路が題材だけど、説明に出てくるグリッドみたいのはそれとは関係なくて、
　例えば横軸で右に行くか左に行くか、の2択に対してx,y座標を割り当ててる感じ。
　その座標上で、y = x+1 の直線より下を進んで目的の左右の回数に当たるx,y座標を目指す通り数を求めるのが、
　今回のテーマとなるカタラン数。
・まずnCrで上下と左右をどう割り当てるかの通り数を求める。これで縦横を独立した問題にできる。
・左と右をどう割り当てるかの通り数を求めるが、ここで0より左に行けない制約がかかるため、カタラン数の出番となる。
　その考え方は、言ったらダメなラインに境界を引いて、その直線で折り返して終点の座標を反対側に回すと、
　始点からそっちの座標に行く通り数が、ダメなラインを超えて終点に着く通り数と一致するので、これを全体から引く。
・これと同じことを縦軸でもやる。K回を縦横どっちに割り振るかを全探索して、
　上記の通り数を足し合わせれば全体の答えになる。
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

template<typename T>
struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    Point operator+(const Point &p) { return {x+p.x, y+p.y}; }
    Point operator-(const Point &p) { return {x-p.x, y-p.y}; }
    Point operator*(const Point &p) { return {x*p.x, y*p.y}; }
    Point operator/(const Point &p) { return {x/p.x, y/p.y}; }
    Point operator*(T k) { return {x*k, y*k}; }
    Point operator/(T k) { return {x/k, y/k}; }
    T norm() { return x*x + y*y; }
    T abs() { return sqrt(norm()); }
    T abs(const Point &p) { return hypot(x-p.x, y-p.y); }
    T manhattan(const Point &p) { return std::abs(x-p.x) + std::abs(y-p.y); }
    void print() { cout << x << ' ' << y << '\n'; }
};

template<typename T> struct Segment { Point<T> p1, p2; };
template<typename T> using Line = Segment<T>;

// 内積
template<typename T> T dot(const Point<T> a, const Point<T> b) { return a.x*b.x + a.y*b.y; }
// 外積
template<typename T> T cross(const Point<T> a, const Point<T> b) { return a.x*b.y - a.y*b.x; }
// 線分segに対する点pの射影
template<typename T> 
Point<T> project(Segment<T> seg, Point<T> p) {
    auto base = seg.p2 - seg.p1;
    T r = dot(p-seg.p1, base) / base.norm();
    return seg.p1 + base*r;
}
// 線分segを対称軸とした点pの線対称の点
template<typename T>
Point<T> reflect(Segment<T> seg, Point<T> p) {
    return p + (project(seg, p) - p) * (T)2;
}

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;

    ModTools<mint> mt(N+M+K*2);
    mint ans = 0;
    rep(i, K+1) {
        ll j = K-i;
        Point<ld> p1(N+i, i), p2(M+j, j);
        // y = x+1 の直線で折り返した点
        auto p3 = reflect(Segment<ld>({{0, 1}, {1, 2}}), p1);
        auto p4 = reflect(Segment<ld>({{0, 1}, {1, 2}}), p2);
        ans += (
            // 上下と左右をどう割り当てるかの通り数
            mt.nCr(N+M+K*2, N+i*2)
            // 左と右をどう割り当てるかの通り数(0より左に行かない)
            * (mt.nCr(p1.x+p1.y, p1.x) - (p3.x >= 0 ? mt.nCr(p3.x+p3.y, p3.x) : 0))
            // 上と下をどう割り当てるかの通り数(0より下に行かない)
            * (mt.nCr(p2.x+p2.y, p2.x) - (p4.x >= 0 ? mt.nCr(p4.x+p4.y, p4.x) : 0))
        );
    }
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
