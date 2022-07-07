/**
 * ・蟻本演習4-7-3
 * ・文字列検索、ローリングハッシュ、貰うDP高速化
 * ・自力AC！いい感じ。
 * ・やったことはtenka1_2016_final_cとかなり近い。
 * 　単語を全部setに詰めて、メイン文字列の部分文字列と一致するものがあればDP遷移をさせる。
 * 　遷移の候補としては、ある位置から単語の最大長さ分見ればいいので、
 * 　今回は単語の長さは最大で20なのでせいぜいlogが乗るような程度。問題ない。
 * ・ちょっと違うのが、単語の途中に被せる感じで繋げていいってルールなので、
 * 　一致する単語があれば区間からまとめて貰ってこれるようにセグ木を使った。
 * 　あと、最低1文字被ってないといけないので、遷移を1つ手前にするみたいな形にしてる。
 * ・制約1秒で15万のNに、単語長20*(setのlog+セグ木のlog)が乗るのでどうかと思ったけど、
 * 　きっちりAC0.53秒。C++よい。
 * ・setをunorderedに変えてlogを節約したらさらに速くなってAC0.24秒。
 * ・結局これも単語長最大20だったらsubstrしたって大して変わらないんじゃないかって思って
 * 　ロリハ外して普通に文字列のままやってみた。AC0.34秒。やっぱり。。
 * ・てかてか文字列長最大20ってむしろセグ木高速化も多分いらないんじゃん？
 * 　って思ったらやっぱりでAC0.31秒。ちょっと速くなってるしｗ
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll M;
    cin >> M;
    string S;
    cin >> S;
    ll N = S.size();
    unordered_set<string> se;
    ll L = 0;
    rep(i, 0, M) {
        string t;
        cin >> t;
        se.insert(t);
        chmax(L, (ll)t.size());
    }

    vector<ll> dp(N, INF);
    dp[0] = 0;
    rep(i, 0, N) {
        rep(j, max(i-L, 0LL), i) {
            if (se.count(S.substr(j, i-j+1))) {
                rep(k, j, i) {
                    chmin(dp[i], dp[k]+1);
                }
            }
        }
    }
    ll ans = dp[N-1];
    print(ans);
    return 0;
}
