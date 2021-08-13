/*
・PAST未ACのupsolve
・自力AC！！頑張った。
・DP高速化、Segment Tree Beats、区間chmin、二分探索
・大変だった。多分考察2時間実装1時間くらいやってたと思う。。
・色々考えたけど、2乗DPを作って遷移高速化する方針に最終的に落ち着く。
・まずAは累積和してBは累積maxしておく。で、
　dp[i] := i日目まで見て、使うコストの最小値
　みたいな形にすると、i日目にi+...日目まで使えるコンピュータを買う遷移
　みたいなやつをすることで最適っぽい動きを作れる。
・でもこのままだと遷移がNあって間に合わない。まとめてやりたいけど、
　貰うDPで考えると、そこで増えるコストは一定だけど、遷移元が区間にならないのでまとめられず。
　配るDPで考えると、遷移先は区間になるけど、遷移先によって増えるコストが変化してしまう。
　ここで詰んだかと思ったけど、配るDPの方は遷移の時にコスト足さないで、
　遷移元として出番が回ってきた時に足すことで、遷移時に使う値を一定にできると気付いた。
　(本当はpriqueとかmultisetをうまく使えば貰うDPでも遷移してこれるらしい。
　はまやんさんの丁寧な解説もあったので、そっちもそのうちやった方がいいかもしれない。)
・さて、これで考察は整った。区間chminと一点加算したいので、Beatsを召喚する。
　遷移をどこまで伸ばせるかは単調性があるので、にぶたんできる。
・これで最初WAになって、サンプルが薄いのもあってしばらく悩んだけど、
　結局累積maxの方で見なきゃいけない所をBを見てたのがいけなかった。しょうもない。。
・計算量は20万のNににぶたんとBeatsでlog2つ乗ってもAC0.53秒。
　よく見るとにぶたん内は一点取得で先に取っておけるので、これでlog1つ外したら0.21秒。
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

template<typename T> int bisect_left(vector<T> &A, T val, int lo=0) { return lower_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val, int lo=0) { return upper_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }

template<typename T> map<T, ll> Counter(vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
map<char, ll> Counter(string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }

template<typename T> struct Accumulate {
    vector<T> acc; int N;
    Accumulate() {}
    Accumulate(int N) : N(N) { acc.resize(N); }
    Accumulate(vector<T> &A) { N = A.size(); acc = A; build(); }
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
    bool operator<(const ModInt &p) const { return x < p.x; }
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

// Segment Tree Beats
class SegmentTreeBeats {
    static const ll inf = 1e18;
    struct Node {
        Node *left, *right;
        ll max_v, smax_v, max_c;
        ll min_v, smin_v, min_c;
        ll sum;
        ll len, ladd, lval;
 
        Node() : left(0), right(0), ladd(0), lval(inf) {}
 
        void init(ll x) {
            max_v = min_v = sum = x;
            smax_v = -inf;
            smin_v = inf;
            max_c = min_c = 1;
        }
 
        void init_empty() {
            max_v = smax_v = -inf;
            min_v = smin_v = inf;
            max_c = min_c = 0;
        }
 
        void update_max(ll x) {
            sum += (x - max_v) * max_c;
 
            if (max_v == min_v) {
                max_v = min_v = x;
            } else if (max_v == smin_v) {
                max_v = smin_v = x;
            } else {
                max_v = x;
            }
 
            if (lval != inf && x < lval) {
                lval = x;
            }
        }
 
        void update_min(ll x) {
            sum += (x - min_v) * min_c;
 
            if (max_v == min_v) {
                max_v = min_v = x;
            } else if (max_v == smin_v) {
                min_v = smax_v = x;
            } else {
                min_v = x;
            }
 
            if (lval != inf && lval < x) {
                lval = x;
            }
        }
 
        void addall(ll x) {
            max_v += x;
            if (smax_v != -inf) smax_v += x;
            min_v += x;
            if (smin_v != inf) smin_v += x;
 
            sum += len * x;
            if (lval != inf) {
                lval += x;
            } else {
                ladd += x;
            }
        }
 
        void updateall(ll x) {
            max_v = min_v = x;
            smax_v = -inf;
            smin_v = inf;
            max_c = min_c = len;
 
            sum = len * x;
            lval = x;
            ladd = 0;
        }
 
        void push() {
            if (lval != inf) {
                left->updateall(lval);
                right->updateall(lval);
                lval = inf;
                return;
            }
 
            if (ladd != 0) {
                left->addall(ladd);
                right->addall(ladd);
                ladd = 0;
            }
 
            if (max_v < left->max_v) {
                left->update_max(max_v);
            }
            if (left->min_v < min_v) {
                left->update_min(min_v);
            }
 
            if (max_v < right->max_v) {
                right->update_max(max_v);
            }
            if (right->min_v < min_v) {
                right->update_min(min_v);
            }
        }
 
        void update() {
            sum = left->sum + right->sum;
 
            if (left->max_v < right->max_v) {
                max_v = right->max_v;
                max_c = right->max_c;
                smax_v = max(left->max_v, right->smax_v);
            } else if (left->max_v > right->max_v) {
                max_v = left->max_v;
                max_c = left->max_c;
                smax_v = max(left->smax_v, right->max_v);
            } else {
                max_v = left->max_v;
                max_c = left->max_c + right->max_c;
                smax_v = max(left->smax_v, right->smax_v);
            }
 
            if (left->min_v < right->min_v) {
                min_v = left->min_v;
                min_c = left->min_c;
                smin_v = min(left->smin_v, right->min_v);
            } else if (left->min_v > right->min_v) {
                min_v = right->min_v;
                min_c = right->min_c;
                smin_v = min(left->min_v, right->smin_v);
            } else {
                min_v = left->min_v;
                min_c = left->min_c + right->min_c;
                smin_v = min(left->smin_v, right->smin_v);
            }
        }
    };
 
    int n, n0;
    Node *root;
 
    void _update_min(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a || nd->max_v <= x) {
            return;
        }
        if (a <= l && r <= b && nd->smax_v < x) {
            nd->update_max(x);
            return;
        }
 
        nd->push();
        _update_min(x, a, b, nd->left, l, (l + r) / 2);
        _update_min(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    void _update_max(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a || x <= nd->min_v) {
            return;
        }
        if (a <= l && r <= b && x < nd->smin_v) {
            nd->update_min(x);
            return;
        }
 
        nd->push();
        _update_max(x, a, b, nd->left, l, (l + r) / 2);
        _update_max(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    void _add_val(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return;
        }
        if (a <= l && r <= b) {
            nd->addall(x);
            return;
        }
 
        nd->push();
        _add_val(x, a, b, nd->left, l, (l + r) / 2);
        _add_val(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    void _update_val(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return;
        }
        if (a <= l && r <= b) {
            nd->updateall(x);
            return;
        }
 
        nd->push();
        _update_val(x, a, b, nd->left, l, (l + r) / 2);
        _update_val(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    ll _query_max(int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return -inf;
        }
        if (a <= l && r <= b) {
            return nd->max_v;
        }
        nd->push();
        ll lv = _query_max(a, b, nd->left, l, (l + r) / 2);
        ll rv = _query_max(a, b, nd->right, (l + r) / 2, r);
        return max(lv, rv);
    }
 
    ll _query_min(int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return inf;
        }
        if (a <= l && r <= b) {
            return nd->min_v;
        }
        nd->push();
        ll lv = _query_min(a, b, nd->left, l, (l + r) / 2);
        ll rv = _query_min(a, b, nd->right, (l + r) / 2, r);
        return min(lv, rv);
    }
 
    ll _query_sum(int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return 0;
        }
        if (a <= l && r <= b) {
            return nd->sum;
        }
        nd->push();
        ll lv = _query_sum(a, b, nd->left, l, (l + r) / 2);
        ll rv = _query_sum(a, b, nd->right, (l + r) / 2, r);
        return lv + rv;
    }
 
public:
    SegmentTreeBeats(vector<ll> a) : n(a.size()) {
        n0 = 1;
        while (n0 < n) n0 <<= 1;
 
        Node *nds = new Node[2 * n0];
        root = nds;
 
        nds[0].len = n0;
        for (int i = 0; i < n0 - 1; ++i) {
            nds[i].left = &nds[2 * i + 1];
            nds[i].right = &nds[2 * i + 2];
            nds[2 * i + 1].len = nds[2 * i + 2].len = (nds[i].len >> 1);
        }
 
        for (int i = 0; i < n; ++i) nds[n0 - 1 + i].init(a[i]);
        for (int i = n; i < n0; ++i) nds[n0 - 1 + i].init_empty();
        for (int i = n0 - 2; i >= 0; i--) nds[i].update();
    }
    SegmentTreeBeats(int n) : SegmentTreeBeats(vector<ll>(n, 0)) {}
 
    void update_min(int a, int b, ll x) { _update_min(x, a, b, root, 0, n0); }
 
    void update_max(int a, int b, ll x) { _update_max(x, a, b, root, 0, n0); }
 
    void add_val(int a, int b, ll x) { _add_val(x, a, b, root, 0, n0); }
 
    void update_val(int a, int b, ll x) { _update_val(x, a, b, root, 0, n0); }
 
    ll query_max(int a, int b) { return _query_max(a, b, root, 0, n0); }
 
    ll query_min(int a, int b) { return _query_min(a, b, root, 0, n0); }
 
    ll query_sum(int a, int b) { return _query_sum(a, b, root, 0, n0); }

    ll get(int i) {
        return query_sum(i, i+1);
    }

    ll operator[](int i) {
        return query_sum(i, i+1);
    }

    void update(int i, ll x) {
        update_val(i, i+1, x);
    }

    void add(int i, ll x) {
        add_val(i, i+1, x);
    }

    void print(int n) {
        rep(i, n) {
            cout << query_sum(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }
};

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    auto acc = A;
    rep(i, N-1) acc[i+1] += acc[i];
    B.insert(B.begin(), 0);
    auto accmx = B;
    rep(i, N) chmax(accmx[i+1], accmx[i]);

    SegmentTreeBeats dp(vector<ll>(N+1, INF));
    dp.update(0, 0);
    rep(i, N) {
        dp.add(i, accmx[i]);
        ll cur = dp[i];
        ll j = bisearch_max(i, N+1, [&](ll m) {
            return accmx[m] <= acc[i]-cur;
        });
        if (j == i) continue;
        dp.update_min(i+1, j+1, cur);
        // dp.print(N+1);
    }
    ll ans = sum(A)-(dp[N]+accmx[N]);
    if (ans >= 0) {
        print(ans);
    } else {
        print(-1);
    }
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
