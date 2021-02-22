/**
 * ・普通に貪欲がWAで通らないので怒りの遅延セグ木。
 * ・遅延セグ木、区間和取得・区間更新、後ろから貪欲
 * ・アルファベット26文字分の遅延セグ木を生やすと、文字列の変化を全部愚直シミュできる。
 * ・さすがにこの荒技は重くて、20万文字列*種類数26*セグ木のlogが乗って、AC1.35秒。
 * ・試しに旧式の再帰セグ木の方使ったら、AC1.68秒。やっぱちょっと遅くなるか。
 * 　こっちだと区間和取得ちょっと楽なんだけどねー。
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
};
using mint = ModInt<MOD>;

template<typename T, typename E>
struct LazySegTree {
    typedef function<T(T, T)> F;
    typedef function<T(T, E)> G;
    typedef function<E(E, E)> H;
    typedef function<E(E, int)> P;
    int n;
    F f;
    G g;
    H h;
    P p;
    T d1;
    E d0;
    vector<T> dat;
    vector<E> laz;
    LazySegTree(int n_, F f, G g, H h, T d1, E d0,
            vector<T> v=vector<T>(), P p=[](E a, int b){ return a; }):
            f(f), g(g), h(h), d1(d1), d0(d0), p(p) {
        init(n_);
        if (n_==(int)v.size()) build(n_, v);
    }
    void init(int n_) {
        n = 1;
        while (n<n_) n *= 2;
        dat.clear();
        dat.resize(2*n-1, d1);
        laz.clear();
        laz.resize(2*n-1, d0);
    }
    void build(int n_, vector<T> v) {
        for (int i=0;i<n_;i++) dat[i+n-1] = v[i];
        for (int i=n-2;i>=0;i--)
            dat[i] = f(dat[i*2+1], dat[i*2+2]);
    }
    inline void eval(int len, int k) {
        if (laz[k]==d0) return;
        if (k*2+1<n*2-1) {
            laz[k*2+1] = h(laz[k*2+1], laz[k]);
            laz[k*2+2] = h(laz[k*2+2], laz[k]);
        }
        dat[k] = g(dat[k], p(laz[k], len));
        laz[k] = d0;
    }
    T update(int a, int b, E x, int k, int l, int r) {
        eval(r-l, k);
        if (r<=a||b<=l) return dat[k];
        if (a<=l&&r<=b) {
            laz[k] = h(laz[k], x);
            return g(dat[k], p(laz[k], r-l));
        }
        return dat[k] = f(update(a, b, x, k*2+1, l, (l+r)/2),
                          update(a, b, x, k*2+2, (l+r)/2, r));
    }
    T update(int a, int b, E x) {
        return update(a, b, x, 0, 0, n);
    }
    T update(int i, E x) {
        return update(i, i+1, x);
    }
    T query(int a, int b, int k, int l, int r) {
        eval(r-l, k);
        if(r<=a||b<=l) return d1;
        if(a<=l&&r<=b) return dat[k];
        T vl = query(a, b, k*2+1, l, (l+r)/2);
        T vr = query(a, b, k*2+2, (l+r)/2, r);
        return f(vl, vr);
    }
    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }
};

// 区間和取得・区間更新
auto f = [](ll a, ll b) -> ll { return a + b; };
auto g = [](ll a, ll b) -> ll { return b; };
auto h = [](ll a, ll b) -> ll { return b; };
auto p = [](ll a, ll b) -> ll { return a * b; };

void solve() {
    string S;
    cin >> S;
    ll N = S.size();
    ll M = 26;

    vector<ll> A(N);
    rep(i, N) A[i] = S[i]-'a';

    vector<LazySegTree<ll, ll>> seg(M, {N, f, g, h, 0, INF, vector<ll>(N, 0), p});
    rep(i, N) {
        seg[A[i]].update(i, 1);
    }

    ll ans = 0;
    rep(i, N-3, -1, -1) {
        if (A[i] == A[i+1] and A[i+1] != A[i+2]) {
            ans += N-i - seg[A[i]].query(i, N);
            rep(c, M) {
                if (c == A[i]) {
                    seg[c].update(i, N, 1);
                } else {
                    seg[c].update(i, N, 0);
                }
            }
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    solve();

    return 0;
}
