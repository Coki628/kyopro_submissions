/**
 * 参考：https://img.atcoder.jp/abc150/editorial.pdf
 * 　　　https://drken1215.hatenablog.com/entry/2020/01/12/115800
 * ・E8さん精選100+50問埋め：Rolling Hash
 * ・よく見たら公式の方針結構違ったので、こっちでもやっておこうか。
 * ・XOR系、XORの性質、ローリングハッシュ、数列に使うロリハ
 * ・結論から言えば、隣り合う要素同士のxorに注目する。
 * 　全ての位置で Ai xor x = Bi となるためには、
 * 　Ai xor Ai+1 と Bi xor Bi+1 が、つまり隣り合う要素の差分xorが等しい必要がある。
 * 　2つの要素をいじって、結果的にxorした値を同じにしないといけないので、
 * 　それなら変化する量を合わせたら0にならないといけない、といった感じになる。(多分)
 * 　公式にも書いてあったけど足し算でイメージしたらちょっと分かった。
 * ・数列が全位置で一致しているかを一度に見れるので、これはビット毎にしなくていい。
 * 　となるとやっぱりだいぶ速い。AC0.08秒。
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
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr ld EPS = 1e-10;

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
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(deque<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

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
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename T> unordered_map<T, ll> Counter(vector<T> &A) { unordered_map<T, ll> res; for (T a : A) res[a]++; return res; }
unordered_map<char, ll> Counter(string &S) { unordered_map<char, ll> res; for (char c : S) res[c]++; return res; }

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

struct RollingHash {
    static const uint64_t mod = (1ull << 61ull) - 1;
    using uint128_t = __uint128_t;
    vector< uint64_t > power;
    const uint64_t base;

    static inline uint64_t add(uint64_t a, uint64_t b) {
        if((a += b) >= mod) a -= mod;
        return a;
    }

    static inline uint64_t mul(uint64_t a, uint64_t b) {
        uint128_t c = (uint128_t) a * b;
        return add(c >> 61, c & mod);
    }

    // 2^61-1以下の乱数を返す。これをbaseとするとHackされにくい
    static inline uint64_t generate_base() {
        mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution< uint64_t > rand(1, RollingHash::mod - 1);
        return rand(mt);
    }

    inline void expand(size_t sz) {
        if(power.size() < sz + 1) {
            int pre_sz = (int) power.size();
            power.resize(sz + 1);
            for(int i = pre_sz - 1; i < sz; i++) {
                power[i + 1] = mul(power[i], base);
            }
        }
    }

    // 基数baseのローリングハッシュを構築する
    explicit RollingHash(uint64_t base = generate_base()) : base(base), power{1} {}

    // 文字列sのハッシュテーブルを返す：O(n)
    vector< uint64_t > build(const string &s) const {
        int sz = s.size();
        vector< uint64_t > hashed(sz + 1);
        for(int i = 0; i < sz; i++) {
            hashed[i + 1] = add(mul(hashed[i], base), s[i]);
        }
        return hashed;
    }

    template< typename T >
    vector< uint64_t > build(const vector< T > &s) const {
        int sz = s.size();
        vector< uint64_t > hashed(sz + 1);
        for(int i = 0; i < sz; i++) {
            hashed[i + 1] = add(mul(hashed[i], base), s[i]);
        }
        return hashed;
    }

    // sの区間[l,r)のハッシュ値を返す：O(1)
    uint64_t query(const vector< uint64_t > &s, int l, int r) {
        expand(r - l);
        return add(s[r], mod - mul(s[l], power[r - l]));
    }

    // ハッシュ値h1と長さh2lenのハッシュ値h2を結合する
    uint64_t combine(uint64_t h1, uint64_t h2, size_t h2len) {
        expand(h2len);
        return add(mul(h1, power[h2len]), h2);
    }

    // ハッシュテーブルaの区間[l1,r1)と、ハッシュテーブルbの区間[l2,r2)の文字列の最長共通接頭辞の長さを返す：O(logn)
    int lcp(const vector< uint64_t > &a, int l1, int r1, const vector< uint64_t > &b, int l2, int r2) {
        int len = min(r1 - l1, r2 - l2);
        int low = 0, high = len + 1;
        while(high - low > 1) {
            int mid = (low + high) / 2;
            if(query(a, l1, l1 + mid) == query(b, l2, l2 + mid)) low = mid;
            else high = mid;
        }
        return low;
    }

    uint64_t get_hash(const string &s, int l, int r) {
        auto table = build(s);
        return query(table, l, r);
    }

    // 長さlenの文字列のhashのx文字目(0-indexed)をaからbに変える
    uint64_t update(uint64_t hash, int len, int x, char a, char b) {
        if (b >= a) return add(hash, mul(b-a, power[len-x-1]));
        else return add(hash, mul(mod+(b-a), power[len-x-1]));
    }
};

void solve() {
    const ll MXLOG = 30;
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    rep(i, N) A.pb(A[i]);
    vector<ll> A2(N*2-1), B2(N-1);
    rep(i, N*2-1) {
        A2[i] = A[i]^A[i+1];
    }
    rep(i, N-1) {
        B2[i] = B[i]^B[i+1];
    }

    RollingHash rh;
    auto a_table = rh.build(A2);
    auto b_table = rh.build(B2);
    rep(i, N) {
        if (rh.query(a_table, i, i+N-1) == rh.query(b_table, 0, N-1)) {
            ll x = A[i]^B[0];
            pll ans = {i, x};
            print(ans);
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
