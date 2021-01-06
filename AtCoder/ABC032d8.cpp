/**
 * 参考：https://qiita.com/hamko/items/cceb1a92da14e2755527
 * 　　　https://ikatakos.com/pot/programming_algorithm/dynamic_programming/branch_and_bound
 * ・蟻本演習4-5-2
 * ・分枝限定法
 * ・貪欲にやれる緩和問題を先に処理してその値を上限とし、その値からして既に現在の最善より
 * 　悪い場合はその先を探索しない、といった方法を取る。
 * ・DPテーブルすら作ってないのに、これでちゃんとACする。しかも速い。すごいねー。
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

ll N, W;

// 緩和問題の解を取得
ld get_relax(vector<pll> &VW, ll i, ll v, ll w) {
    ld res = v;
    // 普通に比率のいい方から貪欲に取る
    while (i < N and w <= W) {
        res += VW[i].first;
        w += VW[i].second;
        i++;
    }
    // 最後に余った重さの端数で小数めいっぱいまで取る
    if (i < N) {
        res += VW[i].first * ((W-w)/(ld)VW[i].second);
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> W;
    vector<pll> VW(N);
    rep(i, 0, N) {
        cin >> VW[i].first >> VW[i].second;
    }
    // 緩和問題を貪欲に解けるように予めソートしておく
    sort(ALL(VW), [](pll a, pll b) { return a.first/(ld)a.second > b.first/(ld)b.second; });

    ll ans = 0;
    auto rec = [&](auto&& f, ll i, ll v, ll w) {
        if (i == N) {
            chmax(ans, v);
            return v;
        }
        // 先に緩和問題の解を取得
        ld relax = get_relax(VW, i, v, w);
        // 緩和問題が現在の最善より悪いことが分かった場合はその先を探索しない
        if (relax <= ans) return ans;

        ll res = -INF;
        if (w+VW[i].second <= W) {
            chmax(res, f(f, i+1, v+VW[i].first, w+VW[i].second));
        }
        chmax(res, f(f, i+1, v, w));
        // 許容解(本当の解)を更新
        chmax(ans, res);
        return res;
    };

    rec(rec, 0, 0, 0);
    print(ans);
    return 0;
}
