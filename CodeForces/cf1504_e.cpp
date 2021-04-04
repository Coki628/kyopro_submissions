/*
参考：https://twitter.com/SSRS_cp/status/1378389668895416320
・自力ならず。
・セグ木でDP、区間chmin、SegTreeBeats
・後半、割と近い方針に進んでたけど詰めきれず。
・まずCのコストは必ずかかるものとして、最初から別にしてしまえば、
　Aのコストだけを考えてどう進めるかになる。これだと、
　Cのコストだけで行ける範囲は全てコスト0となり、戻る方向への移動は
　全てコスト0とできる。これなら前からDPできる。
・遷移方法はもっと簡単にもできるみたいだけど、
　自分としてはこれが思いつきやすいと思ったのでこれでやる。
　自分から先Cまでの範囲はノーコストで遷移できるので、ここに区間chmin。
　その1つ先は、Cで足りない差分がかかるのでそれを足して1点更新。
　その先への遷移は、結局座標上の距離なので、
　1つ先に進んだ時に、また1つ先だけやれば問題ない。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
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
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;
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
int bit_length(ll x) { return floor(log2(x))+1; }
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if(res == "") res += '0'; return res; }

ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename T> unordered_map<T, ll> Counter(vector<T> &A) { unordered_map<T, ll> res; for (T a : A) res[a]++; return res; }
unordered_map<char, ll> Counter(string &S) { unordered_map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }

template<typename T> struct Accumulate {
    vector<T> acc; int N;
    Accumulate(vector<T> &A) { N = A.size(); acc = A; rep(i, N-1) acc[i+1] += acc[i]; acc.insert(acc.begin(), 0); }
    T query(int l, int r) { assert(0 <= l and l <= N and 0 <= r and r <= N); return acc[r]-acc[l]; }
    T get(int i) { return query(i, i+1); }
    T operator[](int i) { return get(i); }
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
template<class T> class SegTreeBeats {
    T inf;
    size_t length;
    vector<T>
    node_max_first,node_max_second,count_max_first,
    node_min_first,node_min_second,count_min_first,
    node_sum,lazy_add,lazy_update;
    vector<pair<int,int>> range;
    stack<int> down,up;
    inline void internal_chmax(int k, long long x) {
        node_sum[k] += (x - node_max_first[k]) * count_max_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_first[k] == node_min_second[k]) node_max_first[k] = node_min_second[k] = x;
        else node_max_first[k] = x;
        if(lazy_update[k] != inf && x < lazy_update[k]) lazy_update[k] = x;
    }
    inline void internal_chmin(int k, long long x) {
        node_sum[k] += (x - node_min_first[k]) * count_min_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_second[k] == node_min_first[k]) node_min_first[k] = node_max_second[k] = x;
        else node_min_first[k] = x;
        if(lazy_update[k] != inf && lazy_update[k] < x) lazy_update[k] = x;
    }
    inline void internal_add(int k, long long x) {
        node_max_first[k] += x;
        if(node_max_second[k] != -inf) node_max_second[k] += x;
        node_min_first[k] += x;
        if(node_min_second[k] != inf) node_min_second[k] += x;
        node_sum[k] += x * (range[k].second - range[k].first);
        (lazy_update[k] != inf ? lazy_update[k]:lazy_add[k]) += x;
    }
    inline void internal_update(int k, long long x) {
        node_max_first[k] = x; node_max_second[k] = -inf;
        node_min_first[k] = x; node_min_second[k] = inf;
        count_max_first[k] = count_min_first[k] = (range[k].second - range[k].first);
        node_sum[k] = x * (range[k].second - range[k].first);
        lazy_update[k] = x;
        lazy_add[k] = 0;
    }
    inline void propagate(int k) {
        if(length-1 <= k) return;
        if(lazy_update[k] != inf) {
            internal_update(2*k+0, lazy_update[k]);
            internal_update(2*k+1, lazy_update[k]);
            lazy_update[k] = inf;
            return;
        }
        if(lazy_add[k] != 0) {
            internal_add(2*k+0, lazy_add[k]);
            internal_add(2*k+1, lazy_add[k]);
            lazy_add[k] = 0;
        }
        if(node_max_first[k] < node_max_first[2*k+0]) {
            internal_chmax(2*k+0, node_max_first[k]);
        }
        if(node_min_first[2*k+0] < node_min_first[k]) {
            internal_chmin(2*k+0, node_min_first[k]);
        }
        if(node_max_first[k] < node_max_first[2*k+1]) {
            internal_chmax(2*k+1, node_max_first[k]);
        }
        if(node_min_first[2*k+1] < node_min_first[k]) {
            internal_chmin(2*k+1, node_min_first[k]);
        }
    }
    inline void merge(int k) {
        node_sum[k] = node_sum[2*k+0] + node_sum[2*k+1];
        if(node_max_first[2*k+0] < node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+1];
            count_max_first[k] = count_max_first[2*k+1];
            node_max_second[k] = max(node_max_first[2*k+0], node_max_second[2*k+1]);
        }
        else if(node_max_first[2*k+0] > node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_first[2*k+1]);
        }
        else {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0] + count_max_first[2*k+1];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_second[2*k+1]);
        }
        if(node_min_first[2*k+0] < node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_first[2*k+1]);
        }
        else if(node_min_first[2*k+0] > node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+1];
            count_min_first[k] = count_min_first[2*k+1];
            node_min_second[k] = min(node_min_first[2*k+0], node_min_second[2*k+1]);
        }
        else {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0] + count_min_first[2*k+1];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_second[2*k+1]);
        }
    }
    inline void up_merge(void){
        while(up.size()) {
            merge(up.top());
            up.pop();
        }
    }
    inline void down_propagate(const int& k) {
        propagate(k);
        down.push(2*k+0);
        down.push(2*k+1);
    }
public:
    SegTreeBeats(const int num,const T inf = (1LL<<60)) {
        vector<T> a(num,0);
        *this = SegTreeBeats(a,inf);
    }
    SegTreeBeats(const vector<T>& a,const T inf = (1LL<<60)) : inf(inf){
        int num = a.size();
        for (length = 1; length <= num; length *= 2);
        node_max_first.resize(2*length);
        node_max_second.resize(2*length);
        count_max_first.resize(2*length);
        node_min_first.resize(2*length);
        node_min_second.resize(2*length);
        count_min_first.resize(2*length);
        node_sum.resize(2*length);
        range.resize(2*length);
        lazy_add.resize(2*length);
        lazy_update.resize(2*length);

        for(int i=0; i<2*length; ++i) lazy_add[i] = 0, lazy_update[i] = inf;
        for(int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for(int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);

        for(int i=0; i<num; ++i) {
            node_max_first[length+i] = node_min_first[length+i] = node_sum[length+i] = a[i];
            node_max_second[length+i] = -inf;
            node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 1;
        }
        for(int i=num; i<length; ++i) {
            node_max_first[length+i] = node_max_second[length+i] = -inf;
            node_min_first[length+i] = node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 0;
        }
        for(int i=length-1; i; --i) merge(i);
    }
    inline void range_chmin(int a, int b, long long x) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || node_max_first[k] <= x) continue;
            if(a <= range[k].first && range[k].second <= b && node_max_second[k] < x) {
                internal_chmax(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_chmax(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || x <= node_min_first[k]) continue;
            if(a <= range[k].first && range[k].second <= b && x < node_min_second[k]) {
                internal_chmin(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_add(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_add(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_update(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_update(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline T get_max(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = max(v,node_max_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_min(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = min(v,node_min_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_sum(int a, int b, int k = 1) {
        down.push(1);
        long long v = 0;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v += node_sum[k];
                continue;
            }
            down_propagate(k);
        }
        return v;
    }

    T get(int i) {
        return get_sum(i, i+1);
    }

    T operator[](int i) {
        return get(i);
    }

    void update(int i, T x) {
        range_update(i, i+1, x);
    }

    void add(int i, T x) {
        range_add(i, i+1, x);
    }
};

void solve() {
    ll N;
    cin >> N;
    vector<pll> AC;
    ll base = 0;
    rep(i, N) { 
        ll a, c;
        cin >> a >> c;
        AC.pb({a, c});
        base += c;
    }
    sort(ALL(AC));
    auto [A, C] = zip(AC);

    SegTreeBeats<ll> dp(vector<ll>(N, INF), INF);
    dp.update(0, 0);
    rep(i, N-1) {
        ll j = bisect_right(A, A[i]+C[i])-1;
        dp.range_chmin(i, j+1, dp[i]);
        if (j+1 < N) {
            dp.update(j+1, min(dp[j+1], dp[i]+(A[j+1]-(A[i]+C[i]))));
        }
    }
    ll ans = base+dp[N-1];
    print(ans);
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
