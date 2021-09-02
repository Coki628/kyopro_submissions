/**
 * ・ライブラリ整備：ダブリングのverify
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

// ダブリング
vvl doubling(int MAX, vector<ll> &A) {

    int N = A.size();
    auto nxt = list2d(MAX, N, -1LL);
    rep(i, 0, N) {
        nxt[0][i] = A[i];
    }
    rep(k, 1, MAX) {
        rep(i, 0, N) {
            nxt[k][i] = nxt[k-1][nxt[k-1][i]];
        }
    }
    return nxt;
}

template<typename F>
ll bisearch_min(ll mn, ll mx, const F &func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

template<typename T, typename F>
struct Doubling {

    int N;
    vector<vector<T>> dat;
    const int MXLOG;
    const F f;

    Doubling(int MXLOG, const vector<T> &A, T init, const F f) : MXLOG(MXLOG), f(f) {
        N = A.size();
        dat = list2d(MXLOG, N, init);
        rep(i, N) {
            dat[0][i] = A[i];
        }
        rep(k, 1, MXLOG) {
            rep(i, N) {
                dat[k][i] = f(dat[k-1][i], dat[k-1][dat[k-1][i]]);
            }
        }
    }

    // stから始めてK個先を返す
    T get(T st, ll K) {
        T res = st;
        rep(k, MXLOG-1, -1, -1) {
            if (K>>k & 1) {
                res = f(res, dat[k][res]);
            }
        }
        return res;
    }

    // stから始めて1個先を返す
    T next(T st) {
        return f(st, dat[0][st]);
    }

    // stから始めてgに到達するまでの回数を返す
    ll times(T st, ll g) {
        T cur = st;
        ll res = 0;
        rep(k, MXLOG-1, -1, -1) {
            if (dat[k][cur] < g) {
                res += 1LL<<k;
                cur = dat[k][cur];
            }
        }
        res++;
        return res;
    }
};

// ll cur = l, res = 0;
// rep(i, MXLOG-1, -1, -1) {
//     if (nxt[i][cur] < r) {
//         res += 1LL<<i;
//         cur = nxt[i][cur];
//     }
// }
// res++;
// print(res);

template<typename T, typename F>
Doubling<T, F> get_doubling(int MXLOG, const vector<T> &A, T init, const F f) {
    return {MXLOG, A, init, f};
}

auto f = [](ll prev, ll power) {
    return power;
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];
    ll L;
    cin >> L;

    vector<ll> B(N);
    rep(i, 0, N) {
        B[i] = bisect_right(A, A[i]+L) - 1;
    }

    ll MX = 32;
    auto db = get_doubling(MX, B, -1LL, f);

    ll Q;
    cin >> Q;
    rep(_, 0, Q) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        if (a > b) swap(a, b);
        ll res = db.times(a, b);
        print(res);
    }
    return 0;
}
