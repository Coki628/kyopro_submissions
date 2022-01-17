/*
・遅延セグ木、Functionなしラムダ版のverifyと速度チェック
・1.67秒→0.97秒。めっちゃ良くなった。やっぱ速度厳しめなやつほど変わるな。
・うしさん版も使ってみた。
・座圧のlogをメイン処理でやらないで前処理した。
　あと座圧ライブラリの型が違ってるの直した。
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
// constexpr ll MOD = 1000000007;
constexpr int MOD = 998244353;
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
    // operator ll() const { return x; }
};
using mint = ModInt<MOD>;

// 遅延評価セグメント木(非再帰)
template<typename F, typename G, typename H, typename Monoid, typename OperatorMonoid>
struct LazySegmentTree {
    int sz, height;
    vector< Monoid > data;
    vector< OperatorMonoid > lazy;
    const F f;
    const G g;
    const H h;
    const Monoid M1;
    const OperatorMonoid OM0;

    LazySegmentTree(int n, const F f, const G g, const H h,
                                    const Monoid &M1, const OperatorMonoid OM0)
            : f(f), g(g), h(h), M1(M1), OM0(OM0) {
        sz = 1;
        height = 0;
        while(sz < n) sz <<= 1, height++;
        data.assign(2 * sz, M1);
        lazy.assign(2 * sz, OM0);
    }

    LazySegmentTree(const F f, const G g, const H h,
                                    const Monoid &M1, const OperatorMonoid OM0)
            : f(f), g(g), h(h), M1(M1), OM0(OM0) {}

    void set(int k, const Monoid &x) {
        data[k + sz] = x;
    }

    void build() {
        for(int k = sz - 1; k > 0; k--) {
            data[k] = f(data[2 * k + 0], data[2 * k + 1]);
        }
    }

    void build(vector<Monoid> &A) {
        int n = A.size();
        sz = 1;
        height = 0;
        while(sz < n) sz <<= 1, height++;
        data.assign(2 * sz, M1);
        lazy.assign(2 * sz, OM0);
        rep(i, n) set(i, A[i]);
        build();
    }

    inline void propagate(int k) {
        if(lazy[k] == OM0) return;
        lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
        lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
        data[k] = apply(k);
        lazy[k] = OM0;
    }

    inline Monoid apply(int k) {
        return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]);
    }

    inline void recalc(int k) {
        while(k >>= 1) data[k] = f(apply(2 * k + 0), apply(2 * k + 1));
    }

    inline void thrust(int k) {
        for(int i = height; i > 0; i--) propagate(k >> i);
    }

    void update(int a, int b, const OperatorMonoid &x) {
        if(a >= b) return;
        thrust(a += sz);
        thrust(b += sz - 1);
        for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) lazy[l] = h(lazy[l], x), ++l;
            if(r & 1) --r, lazy[r] = h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }

    Monoid query(int a, int b) {
        if(a >= b) return M1;
        thrust(a += sz);
        thrust(b += sz - 1);
        Monoid L = M1, R = M1;
        for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) L = f(L, apply(l++));
            if(r & 1) R = f(apply(--r), R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) {
        return query(k, k + 1);
    }

    void update(int i, OperatorMonoid &x) {
        update(i, i+1, x);
    }

    void print(int n) {
        rep(i, n) {
            cout << query(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }

    template< typename C >
    int find_subtree(int a, const C &check, Monoid &M, bool type) {
        while(a < sz) {
            propagate(a);
            Monoid nxt = type ? f(apply(2 * a + type), M) : f(M, apply(2 * a + type));
            if(check(nxt)) a = 2 * a + type;
            else M = nxt, a = 2 * a + 1 - type;
        }
        return a - sz;
    }

    template< typename C >
    int find_first(int a, const C &check) {
        Monoid L = M1;
        if(a <= 0) {
            if(check(f(L, apply(1)))) return find_subtree(1, check, L, false);
            return -1;
        }
        thrust(a + sz);
        int b = sz;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) {
                Monoid nxt = f(L, apply(a));
                if(check(nxt)) return find_subtree(a, check, L, false);
                L = nxt;
                ++a;
            }
        }
        return -1;
    }
    
    template< typename C >
    int find_last(int b, const C &check) {
        Monoid R = M1;
        if(b >= sz) {
            if(check(f(apply(1), R))) return find_subtree(1, check, R, true);
            return -1;
        }
        thrust(b + sz - 1);
        int a = sz;
        for(b += sz; a < b; a >>= 1, b >>= 1) {
            if(b & 1) {
                Monoid nxt = f(apply(--b), R);
                if(check(nxt)) return find_subtree(b, check, R, true);
                R = nxt;
            }
        }
        return -1;
    }
};

template<typename F, typename G, typename H, typename T, typename E>
LazySegmentTree<F, G, H, T, E> get_Lazy_segment_tree(const F& f, const G& g, const H& h, const T& ti, const E& ei) {
    return {f, g, h, ti, ei};
}

// 座標圧縮
template<typename T>
struct Compress {

    int N;
    vector<T> dat;

    Compress(vector<T> A) {
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        N = A.size();
        dat = A;
    }

    int zip(T x) {
        return bisect_left(dat, x);
    }

    T unzip(int x) {
        return dat[x];
    }

    int operator[](T x) {
        return zip(x);
    }

    int size() {
        return dat.size();
    }

    vector<T> zip(vector<T> &A) {
        int M = A.size();
        vector<T> res(M);
        rep(i, M) res[i] = zip(A[i]);
        return res;
    }
};

// 区間和取得・区間加算・区間更新
struct Node {
    mint val, sz;
    operator mint() const { return val; }
};
struct Func {
    mint add, assign;
    bool update;
    bool operator==(const Func &f) const {
        return add == f.add and assign == f.assign and update == f.update;
    }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, Func b) -> Node {
    if (b.update) {
        return { a.sz*(b.add+b.assign), a.sz };
    } else {
        return { a.val+a.sz*b.add, a.sz };
    }
};
auto h = [](Func a, Func b) -> Func { 
    if (not b.update) {
        a.add += b.add;
    } else {
        a.update = 1;
        a.add = 0;
        a.assign = b.add+b.assign;
    }
    return a;
};
const Node T = {0, 0};
const Func E = {0, 0, 0};

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    A.insert(A.begin(), 0);
    Compress<ll> cp(A);
    ll M = cp.size();
    A = cp.zip(A);

    vector<ll> B(M);
    rep(i, 0, M-1) {
        B[i] = cp.unzip(i+1)-cp.unzip(i);
    }
    vector<Node> B2(M);
    //  値と圧縮した区間長をペアで持つ
    rep(i, M) B2[i] = {0, B[i]};

    auto seg = get_Lazy_segment_tree(f, g, h, T, E);
    seg.build(B2);
    seg.update(0, A[1], {1, 0, 0});
    rep(i, 2, N+1) {
        mint sm = seg.query(0, M);
        // if (i%2 == 1) print(sm*-1);
        // else print(sm);
        ll mi = A[i];
        // 今回遷移がある位置(区間加算で総和を引く)
        seg.update(0, mi, {-sm, 0, 0});
        // 今回遷移がない位置(区間更新で0にする)
        seg.update(mi, M, {0, 0, 1});
    }
    mint ans = seg.query(0, M);
    if (N%2 == 0) ans = -ans;
    print(ans);
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
