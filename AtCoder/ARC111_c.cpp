/**
 * 参考：https://atcoder.jp/contests/arc111/editorial
 * ・自力ならず。
 * ・ソートして貪欲
 * ・結論から言えば、元々無理な場合を弾いてしまえば、あとはキャパの小さい人から順に
 * 　その人の荷物を持ってる人とスワップしてくる、を繰り返せばOK。
 * ・お気持ちとしては、最初に即NGを弾いている以上、自分のじゃない荷物を持ってる全ての人は
 * 　自分のキャパより小さい荷物を持っているはずなので、常に自分よりキャパの大きい人と
 * 　スワップすることを考えれば、渡した先で重量オーバーが発生することはない、って感じ。
 * 　逆に自分はオーバーになる可能性があるけど、自分の荷物を受け取るので問題がない。
 * ・実装は、色んな添字が出てきてゴチャゴチャするやつだけど、
 * 　P[i] := iさんが今持ってる荷物番号 が元々あるので、これと対になる
 * 　ids[i] := i番の荷物を持ってる人 を用意するとうまくやれる。
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

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);
    auto P = LIST(N);
    rep(i, 0, N) P[i]--;

    rep(i, 0, N) {
        if (P[i] != i and A[i] <= B[P[i]]) {
            print(-1);
            return 0;
        }
    }

    // ids[i] := i番の荷物を持ってる人
    vector<ll> ids(N);
    rep(i, 0, N) {
        ids[P[i]] = i;
    }
    vector<pll> AI(N);
    rep(i, 0, N) {
        AI[i].first = A[i];
        AI[i].second = i;
    }
    sort(ALL(AI));

    vector<pll> ans;
    for (auto& [_, i] : AI) {
        ll j = ids[i];
        if (i == j) continue;
        ans.pb({i+1, j+1});
        ids[P[i]] = j;
        ids[P[j]] = i;
        swap(P[i], P[j]);
    }

    print(ans.size());
    for (auto& p : ans) print(p);
    return 0;
}
