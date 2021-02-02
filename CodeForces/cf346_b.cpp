/**
 * ・蟻本演習4-7-1
 * ・なんとか自力ACー？テストケースは見ちゃったけど。。
 * ・LCSのDP、文字列DP、復元
 * ・基本はLCSのDPなんだけど、色々あって大変。
 * ・禁止文字列があるので、それと一致しないように遷移を制限する必要がある。
 * 　nxt[i][c] := 今までi文字一致していて、今回追加する文字がcの時に遷移先となるi
 * 　みたいな前計算を用意して対応する。
 * ・メインのDPはLCSのDPに添字kを足して、
 * 　dp[i][j][k] := Sをi文字目、Tをj文字目まで見て、禁止文字列との一致がk文字の時の最大値
 * 　といったものを使う。
 * ・また今回は復元パートがあり、添字kの遷移元は結果からでは分からないので、
 * 　値として、(最大値, 遷移元のk)みたいなペアを持って復元時にはこれを使う。
 * 　kに対すること以外の基本的な復元の流れは、edpc_fを参考にする。
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

    string S, T, U;
    cin >> S >> T >> U;
    ll N = S.size();
    ll M = T.size();
    ll L = U.size();

    // nxt[i][c] := 今までi文字一致していて、今回追加する文字がcの時に遷移先となるi
    auto nxt = list2d(L, 26, 0);
    rep(i, 0, L) {
        for (char c : ascii_uppercase) {
            // i文字一致した状態から任意の1文字が追加された場合を考える
            string s = U.substr(0, i) + c;
            ll j = 0;
            while (i-j >= 0 and s.substr(j, i-j+1) != U.substr(0, i-j+1)) j++;
            nxt[i][ord(c)-'A'] = i-j+1;
        }
    }

    // dp[i][j][k] := Sをi文字目、Tをj文字目まで見て、禁止文字列との一致がk文字の時の最大値
    auto dp = list3d(N+1, M+1, L, pll({0, -1}));
    rep(i, 0, N+1) {
        rep(j, 0, M+1) {
            rep(k, 0, L) {
                if (i < N) {
                    // 文字S[i]を使わない
                    chmax(dp[i+1][j][k], dp[i][j][k]);
                }
                if (j < M) {
                    // 文字T[j]を使わない
                    chmax(dp[i][j+1][k], dp[i][j][k]);
                }
                // 一致したら文字S[i]とT[j]を使う
                if (i < N and j < M and S[i] == T[j]) {
                    // ここからのkの遷移先がL文字に達しないなら遷移できる
                    if (nxt[k][ord(S[i])-'A'] < L) {
                        pll p = {dp[i][j][k].first+1, k};
                        chmax(dp[i+1][j+1][nxt[k][ord(S[i])-'A']], p);
                    }
                }
            }
        }
    }
    ll cnt = 0, k = -1;
    rep(i, 0, L) {
        if (cnt < dp[N][M][i].first) {
            cnt = dp[N][M][i].first;
            k = i;
        }
    }
    if (cnt == 0) {
        print(0);
    } else {
        // ここから復元パート
        ll i = N;
        ll j = M;
        string ans;
        while (k >= 0 and i > 0 and j > 0) {
            if (dp[i-1][j][k] == dp[i][j][k]) i--;
            elif (dp[i][j-1][k] == dp[i][j][k]) j--;
            else {
                ans = S[i-1] + ans;
                cnt--;
                k = dp[i][j][k].second;
                i--;
                j--;
            }
        }
        print(ans);
    }
    return 0;
}
