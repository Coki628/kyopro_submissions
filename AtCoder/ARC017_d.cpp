/**
 * 参考：https://beet-aizu.hatenablog.com/entry/2019/03/12/171221
 * ・区間加算、区間GCD取得
 * ・類題(cf1459_c)をやったのでこちらも。遅延セグ木で普通に叩くのはできないので注意。
 * ・区間のクッキーを全て均等に配れるように、は区間GCDになる。確かにそうだ。
 * 　ノーヒントですぐ区間GCDって気付けたかな？さすがにそこは大丈夫だったと思いたいけど。。
 * ・で、やり方。差分を、1点更新・区間GCD取得のセグ木で持って、
 * 　実際の値を、区間加算、1点取得できる何か(今回はBIT使った)で持つ。
 * 　すると区間GCDは、区間で先頭要素の値と、2番目以降の要素との差分のGCDを取るとできる。
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
constexpr ll INF = 1000000000000000000;
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
    int n;
    vector<Monoid> seg;
    
    const F f;
    const Monoid M1;
    
    SegTree(int n, const F f, const Monoid &M1) : n(n), f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int _n) {
        n = _n;
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

    void print() {
        rep(i, 0, n) {
            if (i == n-1) {
                ::print(seg[i+sz]);
            } else {
                cout << seg[i+sz] << ' ';
            }
        }
    }
};

// 区間加算BIT(区間加算・区間和取得)
template<typename T>
struct BIT2 {

    ll N;
    vector<T> data0, data1;

    BIT2() {};

    BIT2(int N) {
        resize(N);
    }

    void resize(int n) {
        // 添字0が使えないので、内部的には全て1-indexedとして扱う
        N = ++n;
        data0.resize(N);
        data1.resize(N);
    }

    void _add(vector<T> &data, int k, T x) {
        k++;
        while (k < N) {
            data[k] += x;
            k += k & -k;
        }
    }

    T _get(vector<T> &data, int k) {
        k++;
        T s = 0;
        while (k) {
            s += data[k];
            k -= k & -k;
        }
        return s;
    }

    // 区間[l,r)に値xを加算
    void add(int l, int r, T x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    // 1点加算
    void add(int i, T x) {
        add(i, i+1, x);
    }

    // 区間[l,r)の和を取得
    T query(int l, int r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    // 1点取得
    T get(int i) {
        return query(i, i+1);
    }

    // 1点更新
    void update(int i, T x) {
        add(i, i+1, x - get(i));
    }

    T operator[](int i) {
        return get(i);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    vector<ll> B(N);
    B[0] = A[0];
    rep(i, 1, N) {
        B[i] = A[i] - A[i-1];
    }
    // セグ木で差分を、BITで値を管理
    SegTree<ll> seg(N+1, [](ll a, ll b) { return gcd(abs(a), abs(b)); }, 0LL);
    BIT2<ll> bit(N);
    rep(i, 0, N) {
        seg.set(i, B[i]);
        bit.add(i, A[i]);
    }
    seg.build();

    ll Q;
    cin >> Q;
    rep(_, 0, Q) {
        ll t, l, r;
        cin >> t >> l >> r;
        l--;
        if (t == 0) {
            // 左端要素の値と2番目以降との差分でGCDを取る
            ll res = gcd(bit.get(l), seg.query(l+1, r));
            print(res);
        } else {
            seg.update(l, seg[l] + t);
            seg.update(r, seg[r] - t);
            bit.add(l, r, t);
        }
    }
    return 0;
}
