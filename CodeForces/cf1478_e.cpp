/**
 * 参考：ツイート色々
 * ・遅延セグ木、区間和取得・区間更新、逆操作
 * ・逆操作を考えると、やらなきゃいけないことが一意になる。
 * ・シミュるには、区間和取得・区間更新ができるといいので、遅延セグ木を用意。
 * ・区間和取得があるので、要素数も一緒に持つタイプのモノイドを使う。
 * ・あと作用素の初期値がなんか区間和だし0でもいい気がしちゃうんだけど、
 * 　更新側は、更新で有り得ない値にしないといけないんだった。INFでOK。
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
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define ALL(A) A.begin(), A.end()
#define elif else if
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll INF = 1e18;
constexpr ll MOD = 1000000007;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

vector<ll> LIST(ll N) { vector<ll> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

template<typename T, typename E>
struct SegmentTree {
    using F = function<T(T, T)>;
    using G = function<T(T, E)>;
    using H = function<E(E, E)>;
    int n, height;
    F f;
    G g;
    H h;
    T ti;
    E ei;
    vector<T> dat;
    vector<E> laz;
    SegmentTree(F f, G g, H h, T ti, E ei):
        f(f), g(g), h(h), ti(ti), ei(ei) {}

    void init(int n_){
        n = 1; height = 0;
        while (n<n_) n<<=1, height++;
        dat.assign(2*n, ti);
        laz.assign(2*n, ei);
    }

    void build(int n_) {
        init(n_);
    }

    void build(const vector<T> &v){
        int n_ = v.size();
        init(n_);
        for (int i=0;i<n_;i++) dat[n+i] = v[i];
        for (int i=n-1;i;i--)
        dat[i] = f(dat[(i<<1)|0], dat[(i<<1)|1]);
    }

    inline T reflect(int k){
        return laz[k]==ei?dat[k]:g(dat[k], laz[k]);
    }

    inline void propagate(int k){
        if (laz[k]==ei) return;
        laz[(k<<1)|0] = h(laz[(k<<1)|0], laz[k]);
        laz[(k<<1)|1] = h(laz[(k<<1)|1], laz[k]);
        dat[k] = reflect(k);
        laz[k] = ei;
    }

    inline void thrust(int k){
        for (int i=height;i;i--) propagate(k>>i);
    }

    inline void recalc(int k){
        while (k>>=1)
        dat[k] = f(reflect((k<<1)|0), reflect((k<<1)|1));
    }

    void update(int a,int b, E x){
        if (a>=b) return;
        thrust(a+=n);
        thrust(b+=n-1);
        for (int l=a,r=b+1;l<r;l>>=1,r>>=1) {
            if (l&1) laz[l] = h(laz[l], x), l++;
            if (r&1) --r, laz[r] = h(laz[r], x);
        }
        recalc(a);
        recalc(b);
    }

    void set_val(int a, T x){
        thrust(a+=n);
        dat[a] = x; laz[a] = ei;
        recalc(a);
    }

    T query(int a, int b){
        if (a>=b) return ti;
        thrust(a+=n);
        thrust(b+=n-1);
        T vl = ti, vr = ti;
        for (int l=a,r=b+1;l<r;l>>=1,r>>=1) {
            if (l&1) vl = f(vl, reflect(l++));
            if (r&1) vr = f(reflect(--r), vr);
        }
        return f(vl, vr);
    }

    template<typename C>
    int find(int st, C &check, T &acc, int k, int l, int r){
        if (l+1==r) {
            acc = f(acc, reflect(k));
            return check(acc)?k-n:-1;
        }
        propagate(k);
        int m = (l+r)>>1;
        if (m<=st) return find(st, check, acc, (k<<1)|1, m, r);
        if (st<=l&&!check(f(acc,dat[k]))) {
            acc = f(acc,dat[k]);
            return -1;
        }
        int vl = find(st, check, acc, (k<<1)|0, l, m);
        if (~vl) return vl;
        return find(st, check, acc, (k<<1)|1, m, r);
    }

    template<typename C>
    int find(int st, C &check){
        T acc = ti;
        return find(st, check, acc, 1, 0, n);
    }
};

// 区間和取得・区間更新
auto f = [](pll a, pll b) -> pll { return { a.first+b.first, a.second+b.second }; };
auto g = [](pll a, ll b) -> pll { return { a.second*b, a.second }; };
auto h = [](ll a, ll b) -> ll { return b; };

void solve() {
    ll N, Q;
    cin >> N >> Q;
    string S, T;
    cin >> S >> T;

    SegmentTree<pll, ll> seg(f, g, h, {0, 0}, INF);
    vector<pll> A(N, {0, 1});
    rep(i, 0, N) {
        if (T[i] == '1') A[i].first = 1;
    }
    seg.build(A);

    vector<pll> LR(Q);
    rep(i, 0, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        LR[i] = {l, r};
    }
    // 逆操作にする
    reverse(ALL(LR));
    for (auto& [l, r] : LR) {
        ll len = r-l;
        ll sm = seg.query(l, r).first;
        // ちょうど半分だと、どっちに倒すにも半分未満にできないので即NG
        if (len%2 == 0 and sm == len/2) {
            NO();
            return;
        }
        // 0,1少ない方に揃える
        if (sm > len/2) {
            seg.update(l, r, 1);
        } else {
            seg.update(l, r, 0);
        }
    }
    string S2;
    rep(i, 0, N) {
        ll val = seg.query(i, i+1).first;
        if (val) S2 += '1';
        else S2 += '0';
    }
    // 元の数列Sと一致すればOK
    if (S == S2) YES();
    else NO();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
