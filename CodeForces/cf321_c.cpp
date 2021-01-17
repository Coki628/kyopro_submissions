/**
 * 参考：https://qiita.com/drken/items/4b4c3f1824339b090202
 * 　　　http://techtipshoge.blogspot.com/2016/09/centroid-decomposition.html
 * ・蟻本演習4-6-2
 * ・分割統治法、重心分解
 * ・木の重心を求めるのは前やったことあったけど、重心分解は初めてやった。
 * 　部分木の重心を求めるDFSと部分木のサイズを再計算するDFS、
 * 　求めた重心から木を分割していく再帰探索で、再帰3本立てみたいになってる。
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

vvl nodes;
vector<ll> dp;
vector<bool> used;
vector<ll> centroids;

// uを根とした部分木の重心を求めるDFS
void dfs(ll u, ll prv, ll sz) {
    dp[u] = 1;
    for (ll v : nodes[u]) {
        if (v == prv or used[v]) continue;
        dfs(v, u, sz);
        dp[u] += dp[v];
    }
    bool iscent = true;
    for (ll v : nodes[u]) {
        if (v == prv or used[v]) continue;
        if (dp[v] > sz/2) {
            iscent = false;
            break;
        }
    }
    if (iscent and sz-dp[u] <= sz/2) {
        centroids.pb(u);
    }
}

// 部分木サイズの再計算
void dfs_sz(ll u, ll prv) {
    dp[u] = 1;
    for (ll v : nodes[u]) {
        if (v == prv or used[v]) continue;
        dfs_sz(v, u);
        dp[u] += dp[v];
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    nodes.resize(N);
    dp.resize(N);
    used.resize(N);
    rep(i, 0, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].pb(v);
        nodes[v].pb(u);
    }

    vector<char> ans(N);
    auto rec = [&](auto&& f, ll u, ll prv, ll sz, ll depth) -> bool {
        if (depth > 25) return false;
        // uを根とした部分木の重心vを求める
        centroids.clear();
        dfs(u, prv, sz);
        ll v = centroids[0];
        used[v] = 1;
        dfs_sz(v, -1);
        ans[v] = 'A'+depth;
        // 重心vの子を根とした部分木を再帰的に見ていく
        for (ll w : nodes[v]) {
            if (used[w]) continue;
            if (!f(f, w, v, dp[w], depth+1)) return false;
        }
        return true;
    };
    if (rec(rec, 0, -1, N, 0)) {
        print(ans);
    } else {
        print(-1);
    }
    return 0;
}
