/**
 * 参考：https://yukicoder.me/problems/no/1331/editorial
 * ・難しかったけど、新しい知見も得られてためになった。
 * ・平方分割、MOD累積和、累積和同時進行DP
 * ・累積和同時進行DPについてはお気持ちがメモに書いてあるのと、ABC183e,cf1452dを見るとよくて、
 * 　これらと同じような遷移を、MOD毎の複数箇所から行なっている感じになる。
 * 　配列の管理方法はMOD累積和をやる時みたいな感じ。これも複数のMODを管理してるからややこしいけど。
 * ・で、本題の平方分割は、A[i]の値が小さいところは累積和を持って上記のように遷移、
 * 　A[i]の値の大きいところは、遷移回数が少ないので毎回直接遷移させる、といったことをやる。
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    ll D = ceil(sqrt(N));
    // sm[j][k] := i≡k mod jを満たすマス目iに移動する通り数
    auto sm = list2d(D, D, 0);
    vector<ll> dp(N);
    dp[0] = 1;
    rep(i, 0, N) {
        // 貰う遷移
        rep(j, 1, D) {
            dp[i] += sm[j][i%j];
            dp[i] %= MOD;
        }
        // 配る遷移
        if (A[i] < D) {
            // 小さいA[i]は累積和への遷移
            sm[A[i]][i%A[i]] += dp[i];
            sm[A[i]][i%A[i]] %= MOD;
        } else {
            // 大きいA[i]は遷移回数が少ないので直接DPへ遷移
            for (ll j=i+A[i]; j<N; j+=A[i]) {
                dp[j] += dp[i];
                dp[j] %= MOD;
            }
        }
        // i+1への遷移を別処理
        if (i+1 < N and A[i] != 1) {
            dp[i+1] += dp[i];
            dp[i+1] %= MOD;
        }
    }
    ll ans = dp[N-1];
    print(ans);
    return 0;
}
