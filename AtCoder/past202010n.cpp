/**
 * ・一応自力AC！だいぶ前にTLでヒントっぽいのは聞いてたけど。
 * ・グリッド、直前の状態をビットで持つbitDP
 * ・詳細はソース内コメントにて。
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

vector<string> build_grid(int H, int W, char intv, int offset=1) {

    vector<string> res(H+offset*2);
    rep(h, 0, offset) res[h] = string(W+offset*2, intv);
    rep(h, offset, H+offset) {
        string s;
        cin >> s;
        res[h] = string(offset, intv) + s + string(offset, intv);
    }
    rep(h, H+offset, H+offset*2) res[h] = string(W+offset*2, intv);
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll H = 18, W = 6;
    auto grid = build_grid(H, W, '0', 0);
    grid.insert(grid.begin(), string(W, '0'));
    grid.insert(grid.begin(), string(W, '0'));
    grid.pb(string(W, '0'));

    // dp[i][j][k] := i行目まで見て、2行前がj、1行前がkの状態の時の通り数
    auto dp = list3d(H+4, 1LL<<W, 1LL<<W, 0LL);
    dp[2][0][0] = 1;
    rep(i, 2, H+3) {
        // この行で置換できる箇所を確認
        vector<ll> A;
        rep(j, 0, W) {
            if (grid[i][j] == '?') {
                A.pb(j);
            }
        }
        ll n = A.size();
        rep(bit, 0, 1LL<<n) {
            // ?を0,1に置換
            string row = grid[i];
            rep(k, 0, n) {
                if (bit>>k & 1) {
                    row[A[k]] = '1';
                } else {
                    row[A[k]] = '0';
                }
            }
            // この行の状態をビットにする
            ll bit2 = 0;
            rep(k, 0, W) {
                if (row[k] == '1') {
                    bit2 |= 1LL<<k;
                }
            }
            rep(bit0, 0, 1LL<<W) {
                rep(bit1, 0, 1LL<<W) {
                    if (!dp[i][bit0][bit1]) continue;
                    bool ok = 1;
                    rep(k, 0, W) {
                        // 関係する5マスの0,1の数を確認
                        ll cnt0 = 0, cnt1 = 0;
                        if (bit0>>k & 1) cnt1++;
                        if (bit1>>k & 1) cnt1++;
                        if (k != 0 and bit1>>(k-1) & 1) cnt1++;
                        if (k != W-1 and bit1>>(k+1) & 1) cnt1++;
                        if (bit2>>k & 1) cnt1++;
                        cnt0 = 5 - cnt1;
                        // 条件を満たさないマスが1つでもあればこの行はNG
                        if (bit1>>k & 1 and cnt1 < 3 or !(bit1>>k & 1) and cnt0 < 3) {
                            ok = false;
                            break;
                        }
                    }
                    // 行全体としてOKなら遷移させる
                    if (ok) {
                        dp[i+1][bit1][bit2] += dp[i][bit0][bit1];
                    }
                }
            }
        }
    }
    ll ans = 0;
    rep(i, 0, 1LL<<W) {
        rep(j, 0, 1LL<<W) {
            ans += dp[H+3][i][j];
        }
    }
    print(ans);
    return 0;
}
