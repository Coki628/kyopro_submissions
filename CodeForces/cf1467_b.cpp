/**
 * ・自力ならず。。。
 * ・全探索
 * ・条件整えたつもりがWA貰って終了。。
 * ・結局、場合分けに固執するとハマって、全探索すると通るやつだった。
 * ・各位置について、最善となりうるのは左の値に合わせるか右の値に合わせるかしかないので、
 * 　両方試してみて、そこを動かした時に条件が変わりうる3つだけ毎回チェックする。
 * ・この方針、参戦中もちらっと頭をよぎったんだけど、実装めんどそうだなって後回しにしちゃって
 * 　後ろの問題の考察してたんだよね。。
 * ・今書いてみたら案外すぐ書けたので、これならさっさとやればよかった。。
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

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

bool check(vector<ll> &A, ll i) {
    return (A[i-1] < A[i] and A[i] > A[i+1] or A[i-1] > A[i] and A[i] < A[i+1]);
}

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    // 動かす前の状態チェック
    vector<ll> C(N);
    rep(i, 1, N-1) {
        if (check(A, i)) {
            C[i]++;
        }
    }
    ll base = sum(C);
    ll ans = base;
    rep(i, 1, N-1) {
        // 左に合わせて、いくつ減らせるか
        ll sub = 0;
        ll tmp = A[i];
        A[i] = A[i-1];
        if (C[i] and !check(A, i)) sub++;
        elif (!C[i] and check(A, i)) sub--;
        if (i >= 2) {
            if (C[i-1] and !check(A, i-1)) sub++;
            elif (!C[i-1] and check(A, i-1)) sub--;
        }
        if (i < N-2) {
            if (C[i+1] and !check(A, i+1)) sub++;
            elif (!C[i+1] and check(A, i+1)) sub--;
        }
        chmin(ans, base-sub);
        // 右に合わせて、いくつ減らせるか
        sub = 0;
        A[i] = A[i+1];
        if (C[i] and !check(A, i)) sub++;
        elif (!C[i] and check(A, i)) sub--;
        if (i >= 2) {
            if (C[i-1] and !check(A, i-1)) sub++;
            elif (!C[i-1] and check(A, i-1)) sub--;
        }
        if (i < N-2) {
            if (C[i+1] and !check(A, i+1)) sub++;
            elif (!C[i+1] and check(A, i+1)) sub--;
        }
        chmin(ans, base-sub);
        A[i] = tmp;
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
