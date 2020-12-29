/**
 * 参考：https://twitter.com/kawara_y_kyopro/status/1343597554475266061
 * 　　　https://codeforces.com/contest/1469/submission/102584817
 * ・自力ならず。。
 * ・数列操作、構築
 * ・色んな方法があるみたいだ。自分が見た中ではかわらさんの方針が綺麗だったので真似させていただいた。
 * ・8をうまく使う。基本はNを使って全部1にしていくんだけど、残ったNは8を使うと最大でも6回で1にできる。
 * 　これで残り回数は3。8を1にするのは2を使ってちょうど3回でいけるので達成。
 * 　Nが8以下の時は直接2で8を割ればいい。
 * ・Nで他を1にしまくる方針は考えたんだけど、最後にNを2で割っても到底5回じゃ間に合わないし、、
 * 　って詰まってたけど、8くらいだったら意外と6回で終わるんだな。。
 * ・ちょっともう少し考察してみたんだけど、この中継に使う数字は8じゃなくても、
 * 　8,16,32,64ならどれでもOKっぽい。。N/中継の回数と中継/2の回数が1回ずつ変わるだけだから。
 * 　これは試しに64でやってみたんだけど問題なくAC。すげーな、よくできてる。。
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

ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N+1);
    rep(i, 1, N+1) A[i] = i;
    vector<pll> ans;
    rep(i, 3, N) {
        if (i != 64) {
            ans.pb({i, N});
            A[i] = ceil(A[i], A[N]);
        }
    }
    if (N > 64) {
        while (A[N] > 1) {
            ans.pb({N, 64});
            A[N] = ceil(A[N], A[64]);
        }
        while (A[64] > 1) {
            ans.pb({64, 2});
            A[64] = ceil(A[64], A[2]);
        }
    } else {
        while (A[N] > 1) {
            ans.pb({N, 2});
            A[N] = ceil(A[N], A[2]);
        }
    }
    // print(A);
    print(ans.size());
    for (auto p : ans) {
        print(p);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
