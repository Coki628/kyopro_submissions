/*
参考：https://blog.hamayanhamayan.com/entry/2019/08/14/131223
　　　https://ferin-tech.hatenablog.com/entry/2019/08/11/%E3%83%A9%E3%82%B0%E3%83%A9%E3%83%B3%E3%82%B8%E3%83%A5%E8%A3%9C%E9%96%93
　　　https://ei1333.github.io/library/math/combinatorics/lagrange-polynomial-2.cpp
・ABC高難度埋め
・新しい知見の履修。今まで名前聞いただけだったやつ。
・ラグランジュ補間
・N次式のy=f(x)のペア(x,y)がN+1個分かっていれば、この式について色々分かるというもの。
　ferinさんの記事の説明が分かりやすかった。
　これはy=f(x)の各項の係数を求める、つまりy=ax^0+bx^1+cx^2+...のa,b,cを返すタイプ。計算量はO(N^2)。
・そうと分かって挑めばほぼ貼るだけだけど、自力考察できるかと言われると。。
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
#define rep1(i, a) for(ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for(ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for(ll i = a, _bb = b; (c > 0 && a <= i && i < _bb) or (c < 0 && a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr ld EPS = 1e-10;
constexpr ld PI = M_PI;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
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

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(const vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(const vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(const vector<T> &A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(int x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
int bit_length(ll x) { return x != 0 ? floor(log2(x))+1 : 0; }
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if(res == "") res += '0'; return res; }

ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

ld degrees(ld radians) { return radians * 180.0 / PI; }
ld radians(ld degrees) { return degrees * PI / 180.0; }

template<typename T> int bisect_left(const vector<T> &A, T val, int lo=0) { return lower_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> int bisect_right(const vector<T> &A, T val, int lo=0) { return upper_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }

template<typename T> map<T, ll> Counter(const vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
map<char, ll> Counter(string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }

template<typename T> struct Accumulate {
    vector<T> acc; int N;
    Accumulate() {}
    Accumulate(int N) : N(N) { acc.resize(N); }
    Accumulate(const vector<T> &A) { N = A.size(); acc = A; build(); }
    void set(int i, T a) { acc[i] = a; }
    void build() { rep(i, N-1) acc[i+1] += acc[i]; acc.insert(acc.begin(), 0); }
    T query(int l, int r) { assert(0 <= l and l <= N and 0 <= r and r <= N); return acc[r]-acc[l]; }
    T get(int i) { return query(i, i+1); }
    T operator[](int i) { return query(i, i+1); }
};

template<int mod> struct ModInt {
    int x;
    ModInt() : x(0) {}
    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; }
    ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; }
    ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; }
    ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; }
    ModInt operator-() const { return ModInt(-x); }
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    bool operator==(const ModInt &p) const { return x == p.x; }
    bool operator!=(const ModInt &p) const { return x != p.x; }
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

// 任意ModInt
struct ArbitraryModInt {

    int x;

    ArbitraryModInt() : x(0) {}

    ArbitraryModInt(int64_t y) : x(y >= 0 ? y % get_mod() : (get_mod() - (-y) % get_mod()) % get_mod()) {}

    static int &get_mod() {
        static int mod = 0;
        return mod;
    }

    static void set_mod(int md) {
        get_mod() = md;
    }

    ArbitraryModInt &operator+=(const ArbitraryModInt &p) {
        if((x += p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    ArbitraryModInt &operator-=(const ArbitraryModInt &p) {
        if((x += get_mod() - p.x) >= get_mod()) x -= get_mod();
        return *this;
    }

    ArbitraryModInt &operator*=(const ArbitraryModInt &p) {
        unsigned long long a = (unsigned long long) x * p.x;
        unsigned xh = (unsigned) (a >> 32), xl = (unsigned) a, d, m;
        asm("divl %4; \n\t" : "=a" (d), "=d" (m) : "d" (xh), "a" (xl), "r" (get_mod()));
        x = m;
        return *this;
    }

    ArbitraryModInt &operator/=(const ArbitraryModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ArbitraryModInt operator-() const { return ArbitraryModInt(-x); }

    ArbitraryModInt operator+(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) += p; }

    ArbitraryModInt operator-(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) -= p; }

    ArbitraryModInt operator*(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) *= p; }

    ArbitraryModInt operator/(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) /= p; }

    bool operator==(const ArbitraryModInt &p) const { return x == p.x; }

    bool operator!=(const ArbitraryModInt &p) const { return x != p.x; }

    ArbitraryModInt inverse() const {
        int a = x, b = get_mod(), u = 1, v = 0, t;
        while(b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ArbitraryModInt(u);
    }

    ArbitraryModInt pow(int64_t n) const {
        ArbitraryModInt ret(1), mul(x);
        while(n > 0) {
            if(n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ArbitraryModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ArbitraryModInt &a) {
        int64_t t;
        is >> t;
        a = ArbitraryModInt(t);
        return (is);
    }
};

// ラグランジュ補間：係数を求める
template<typename T>
vector<T> lagrange_polynomial(const vector<T> &x, const vector<T> &y) {
    int k = (int) x.size() - 1;

    vector<T> f(k + 1), dp(k + 2);
    dp[0] = 1;
    for(int j = 0; j <= k; j++) {
        for(int l = k + 1; l > 0; l--) {
            dp[l] = dp[l] * -x[j] + dp[l - 1];
        }
        dp[0] *= -x[j];
    }

    for(int i = 0; i <= k; i++) {
        T d = 1;
        for(int j = 0; j <= k; j++) {
            if(i != j) {
                d *= x[i] - x[j];
            }
        }
        T mul = y[i] / d;
        if(x[i] == 0) {
            for(int j = 0; j <= k; j++) {
                f[j] += dp[j + 1] * mul;
            }
        } else {
            T inv = T(1) / (-x[i]), pre = 0;
            for(int j = 0; j <= k; j++) {
                T cur = (dp[j] - pre) * inv;
                f[j] += cur * mul;
                pre = cur;
            }
        }
    }
    return f;
}

void solve() {
    ll P;
    cin >> P;
    ArbitraryModInt::set_mod(P);
    using mint = ArbitraryModInt;

    auto A = LIST<mint>(P);
    vector<mint> ids(P);
    rep(i, P) ids[i] = i;

    auto res = lagrange_polynomial(ids, A);
    print(res);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
