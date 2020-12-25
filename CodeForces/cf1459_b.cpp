/**
 * 参考：https://oeis.org/A241496
 * ・終了後自力AC。。
 * ・実験、OEIS
 * ・参戦中は色々規則性を探るも、答えに辿り着けず。
 * ・終わってからゆっくり愚直書いて、20くらいまででOEISに投げたらそのものずばりが出た。。
 * ・なんか1つめの式？はうまくいかなくて、FORMULAの2つめの式入れたらうまくいった。
 * 　自分で調べてOEISで通したのは初めてだね。。
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;

    // auto grid = list2d(2, N+1, set<pll>());
    // grid[0][1].insert({0, -1});
    // grid[0][1].insert({0, 1});
    // grid[1][1].insert({-1, 0});
    // grid[1][1].insert({1, 0});
    // rep(i, 1, N) {
    //     for (auto [h, w] : grid[0][i]) {
    //         grid[1][i+1].insert({h-1, w});
    //         grid[1][i+1].insert({h+1, w});
    //     }
    //     for (auto [h, w] : grid[1][i]) {
    //         grid[0][i+1].insert({h, w-1});
    //         grid[0][i+1].insert({h, w+1});
    //     }
    // }
    // vector<ll> ans(N+1);
    // ans[0] = 1;
    // rep(i, 1, N+1){
    //     set<pll> cnt;
    //     rep(j, 0, 2) {
    //         for (auto [h, w] : grid[j][i]) {
    //             cnt.insert({h, w});
    //         }
    //     }
    //     ans[i] = cnt.size();
    // }
    // print(ans);

    ll ans = 1 + ( 3*N*(N + 4) + 2 - pow(-1, N)*(N*(N + 4) + 2) )/8;
    print(ans);
    return 0;
}
