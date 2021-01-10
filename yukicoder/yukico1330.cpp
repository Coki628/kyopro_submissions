/**
 * 参考：https://yukicoder.me/problems/no/1330/editorial
 * ・難しかった。
 * ・場合分けして貪欲頑張る感じかと思ったらDPできるんだね。。
 * ・ナップザックの価値と重さ逆にもつDPみたいなやつをmapでやる。
 * 　掛け算だから値がすぐ大きくなるのもあってか、操作回数が取りうる状態数はかなり少ないみたいで、
 * 　毎回N回全部遷移させても余裕で間に合う。
 * ・C++のmapはイテレート中にキー増えてもちゃんとそのまま動くんだね。便利ー。
 * 　pythonのdictはこれやると壊れるのに。
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

    ll N, M, P;
    cin >> N >> M >> P;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    // 最初から一発で達成できるやつを例外処理
    ll mx = max(A);
    if (mx > M) {
        print(1);
        return 0;
    }

    // B[i] := A[i]を1回選んだ時に掛けれる値
    // C[i] := A[i]を1回選んだ時に使う操作回数
    vector<ll> C(N, 1), B(N);
    rep(i, 0, N) {
        ll cur = A[i];
        while (cur % P == 0) {
            cur /= P;
            C[i]++;
        }
        B[i] = cur;
    }

    // 全部1だったら数を増やせないのでNG
    if (max(B) == 1) {
        print(-1);
        return 0;
    }

    // dp[k] := 操作回数k回の時、取りうるxの最大値
    map<ll, ll> dp;
    dp[0] = 1;
    ll ans = -1;
    for (auto [k, x] : dp) {
        // M超なら即終了
        if (x > M) {
            ans = k;
            break;
        }
        // 最大値掛けてM超なら操作回数+1して即終了
        if (x*mx > M) {
            ans = k+1;
            break;
        }
        // 各A[i]を選ぶ遷移を全部できる
        rep(i, 0, N) {
            chmax(dp[k+C[i]], x*B[i]);
        }
    }
    print(ans);
    return 0;
}
