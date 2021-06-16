/*
・なんとか自力AC！
・場合分けコーナーケース、高速素因数分解
・K==1は場合分けして、残りは素因数の個数の和。
　TL厳しくて自前のやつTLEしたので、
　うしさんところから高速素因数分解を召喚した。AC0.66秒。(TL2秒)
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
#define rep3(i, a, b, c) for(ll i = a, _bb = b; (a <= i && i < _bb) or (a >= i && i > _bb); i += c)
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

template<typename T> T sum(vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> &A) { return *min_element(ALL(A)); }

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

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }

template<typename T> map<T, ll> Counter(vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
map<char, ll> Counter(string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }

template<typename T> struct Accumulate {
    vector<T> acc; int N;
    Accumulate(vector<T> &A) { N = A.size(); acc = A; rep(i, N-1) acc[i+1] += acc[i]; acc.insert(acc.begin(), 0); }
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
    bool operator<(const ModInt &p) const { return x < p.x; }
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

namespace FastPrimeFactorization {

    template< typename word, typename dword, typename sword >
    struct UnsafeMod {
        UnsafeMod() : x(0) {}

        UnsafeMod(word _x) : x(init(_x)) {}

        bool operator==(const UnsafeMod &rhs) const {
            return x == rhs.x;
        }

        bool operator!=(const UnsafeMod &rhs) const {
            return x != rhs.x;
        }

        UnsafeMod &operator+=(const UnsafeMod &rhs) {
            if((x += rhs.x) >= mod) x -= mod;
            return *this;
        }

        UnsafeMod &operator-=(const UnsafeMod &rhs) {
            if(sword(x -= rhs.x) < 0) x += mod;
            return *this;
        }

        UnsafeMod &operator*=(const UnsafeMod &rhs) {
            x = reduce(dword(x) * rhs.x);
            return *this;
        }

        UnsafeMod operator+(const UnsafeMod &rhs) const {
            return UnsafeMod(*this) += rhs;
        }

        UnsafeMod operator-(const UnsafeMod &rhs) const {
            return UnsafeMod(*this) -= rhs;
        }

        UnsafeMod operator*(const UnsafeMod &rhs) const {
            return UnsafeMod(*this) *= rhs;
        }

        UnsafeMod pow(uint64_t e) const {
            UnsafeMod ret(1);
            for(UnsafeMod base = *this; e; e >>= 1, base *= base) {
                if(e & 1) ret *= base;
            }
            return ret;
        }

        word get() const {
            return reduce(x);
        }

        static constexpr int word_bits = sizeof(word) * 8;

        static word modulus() {
            return mod;
        }

        static word init(word w) {
            return reduce(dword(w) * r2);
        }

        static void set_mod(word m) {
            mod = m;
            inv = mul_inv(mod);
            r2 = -dword(mod) % mod;
        }

        static word reduce(dword x) {
            word y = word(x >> word_bits) - word((dword(word(x) * inv) * mod) >> word_bits);
            return sword(y) < 0 ? y + mod : y;
        }

        static word mul_inv(word n, int e = 6, word x = 1) {
            return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
        }

        static word mod, inv, r2;

        word x;
    };

    using uint128_t = __uint128_t;

    using Mod64 = UnsafeMod< uint64_t, uint128_t, int64_t >;
    template<> uint64_t Mod64::mod = 0;
    template<> uint64_t Mod64::inv = 0;
    template<> uint64_t Mod64::r2 = 0;

    using Mod32 = UnsafeMod< uint32_t, uint64_t, int32_t >;
    template<> uint32_t Mod32::mod = 0;
    template<> uint32_t Mod32::inv = 0;
    template<> uint32_t Mod32::r2 = 0;

    bool miller_rabin_primality_test_uint64(uint64_t n) {
        Mod64::set_mod(n);
        uint64_t d = n - 1;
        while(d % 2 == 0) d /= 2;
        Mod64 e{1}, rev{n - 1};
        // http://miller-rabin.appspot.com/    < 2^64
        for(uint64_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if(n <= a) break;
            uint64_t t = d;
            Mod64 y = Mod64(a).pow(t);
            while(t != n - 1 && y != e && y != rev) {
                y *= y;
                t *= 2;
            }
            if(y != rev && t % 2 == 0) return false;
        }
        return true;
    }

    bool miller_rabin_primality_test_uint32(uint32_t n) {
        Mod32::set_mod(n);
        uint32_t d = n - 1;
        while(d % 2 == 0) d /= 2;
        Mod32 e{1}, rev{n - 1};
        for(uint32_t a : {2, 7, 61}) {
            if(n <= a) break;
            uint32_t t = d;
            Mod32 y = Mod32(a).pow(t);
            while(t != n - 1 && y != e && y != rev) {
                y *= y;
                t *= 2;
            }
            if(y != rev && t % 2 == 0) return false;
        }
        return true;
    }

    bool is_prime(uint64_t n) {
        if(n == 2) return true;
        if(n == 1 || n % 2 == 0) return false;
        if(n < uint64_t(1) << 31) return miller_rabin_primality_test_uint32(n);
        return miller_rabin_primality_test_uint64(n);
    }

    uint64_t pollard_rho(uint64_t n) {
        if(is_prime(n)) return n;
        if(n % 2 == 0) return 2;
        Mod64::set_mod(n);
        uint64_t d;
        Mod64 one{1};
        for(Mod64 c{one};; c += one) {
            Mod64 x{2}, y{2};
            do {
                x = x * x + c;
                y = y * y + c;
                y = y * y + c;
                d = __gcd((x - y).get(), n);
            } while(d == 1);
            if(d < n) return d;
        }
        assert(0);
    }

    vector< uint64_t > prime_factor(uint64_t n) {
        if(n <= 1) return {};
        uint64_t p = pollard_rho(n);
        if(p == n) return {p};
        auto l = prime_factor(p);
        auto r = prime_factor(n / p);
        copy(begin(r), end(r), back_inserter(l));
        return l;
    }
};
using namespace FastPrimeFactorization;

void solve() {
    ll a, b, K;
    cin >> a >> b >> K;

    if (a > b) swap(a, b);
    if ((a == b or b%a != 0) and K == 1) {
        NO();
        return;
    }

    auto fact1 = prime_factor(a);
    auto fact2 = prime_factor(b);
    if (fact1.size()+fact2.size() >= K) YES();
    else NO();
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
