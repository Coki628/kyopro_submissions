/**
 * ・蟻本演習4-4-3
 * ・自力AC！頑張った。さすがにJOI問題は1問がぶ厚い。
 * ・半分全列挙、3^N全列挙、セグ木で最大値取得
 * ・N<=30と問題内容の雰囲気から半分全列挙を疑う。状態選択が3つあるので全列挙すると3^N、
 * 　手元の計算機で3^15すると1430万、C++なら多分何とかなりそう。
 * 　で、ペアのマージを考えると、集合1のある状態とペアにできる集合2の状態は、アンナの条件に従うと区間になる。
 * 　ここでこの区間に対して、ブルーノの条件に合う最大値取得ができればOK。
 * ・方針は割とすんなり立ったけど、計算量間に合うかどうかと、実装が重い。
 * ・結果、3^N=1430万は再帰で列挙しても全然間に合う。ここは問題なかった。これだけなら2秒どころか1秒に間に合いそう。
 * ・で、これにソートかけてlogつくとちょっと2秒きついっぽい。(この問題は制約10秒だから問題ない)
 * ・その後、左端と右端を見つけるにぶたん2回とセグ木の区間max取得でlogがついて、
 * 　これでも間に合ってAC9.14秒。C++速いねー。。
 * ・ちょっと速度改善。アンナの条件に合う区間はにぶたんで取れるけど、両方の数列をxでソート(片方は逆順)しておけば、
 * 　値を単調増加にできるので、尺取りっぽく左端と右端を動かせる。
 * 　これでそこのパートのlogはセグ木のやつだけになる。なんとなくlower_boundのlogって軽くて、
 * 　セグ木のlogが重いだろうからこっちがなくなっても大して変化ないのかと思ってたけど全然そんなことなくて、
 * 　めっちゃ速くなってAC3.97秒。
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
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

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

ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

template<typename Monoid>
struct SegTree {
    using F = function<Monoid(Monoid, Monoid)>;
    
    int sz;
    vector<Monoid> seg;
    
    const F f;
    const Monoid M1;
    
    SegTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.resize(2 * sz, M1);
    }

    void clear() {
        seg.clear();
    }
    
    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }
 
    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = f(L, seg[a++]);
            if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }

    Monoid all() {
        return seg[1];
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, D;
    cin >> N >> D;
    vector<pll> XY1;
    rep(i, 0, N/2) {
        ll x, y;
        cin >> x >> y;
        XY1.pb({x, y});
    }
    vector<pll> XY2;
    rep(i, N/2, N) {
        ll x, y;
        cin >> x >> y;
        XY2.pb({x, y});
    }

    if (N == 1) {
        if (XY2[0].first <= D) {
            print(XY2[0].second);
        } else {
            print(0);
        }
        return 0;
    }
    ll N1 = XY1.size();
    ll N2 = XY2.size();

    vector<pll> V1, V2;
    auto rec = [&](auto&& f, ll sz, vector<pll> &v, vector<pll> &res, ll i, ll ax, ll ay, ll bx, ll by) -> void {
        if (i == sz) {
            res.pb({bx-ax, by-ay});
            return;
        }
        f(f, sz, v, res, i+1, ax+v[i].first, ay+v[i].second, bx, by);
        f(f, sz, v, res, i+1, ax, ay, bx+v[i].first, by+v[i].second);
        f(f, sz, v, res, i+1, ax, ay, bx, by);
    };
    rec(rec, N1, XY1, V1, 0, 0, 0, 0, 0);
    rec(rec, N2, XY2, V2, 0, 0, 0, 0, 0);
    ll M1 = V1.size();
    ll M2 = V2.size();

    sort(ALL(V1));
    reverse(ALL(V1));
    sort(ALL(V2));
    SegTree<ll> seg(M2, [](ll a, ll b) { return max(a, b); }, -INF);
    vector<ll> X2(M2);
    rep(i, 0, M2) {
        seg.set(i, V2[i].second);
        X2[i] = V2[i].first;
    }
    seg.build();

    ll ans = 0;
    ll l = 0, r = 0;
    for (auto [x1, y1] : V1) {
        while (l < M2 and X2[l] < -D-x1) l++;
        while (r < M2 and X2[r] <= D-x1) r++;
        if (l < r) {
            ll y2 = seg.query(l, r);
            chmax(ans, y1+y2);
        }
    }
    print(ans);
    return 0;
}
