/**
 * ・すんなり自力AC
 * ・グリッドBFS
 * ・方向の状態持ってBFSする。
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

vector<vvl> bfs(vector<string> &grid, vector<pii> src) {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list3d(2, H, W, INF);
    const vector<pii> dir1 = {{1, 0}, {-1, 0}}, dir2 = {{0, 1}, {0, -1}};
    queue<tuple<ll, ll, ll>> que;
    for (auto [h, w] : src) {
        que.push({0, h, w});
        que.push({1, h, w});
        res[0][h][w] = 0;
        res[1][h][w] = 0;
    }
    while (!que.empty()) {
        auto [d, h, w] = que.front(); que.pop();
        if (d == 0) {
            for (auto [dh, dw] : dir1) {
                int nh = h + dh;
                int nw = w + dw;
                if (grid[nh][nw] == '#') {
                    continue;
                }
                if (res[1][nh][nw] == INF) {
                    res[1][nh][nw] = res[0][h][w] + 1;
                    que.push({1, nh, nw});
                }
            }
        } else {
            for (auto [dh, dw] : dir2) {
                int nh = h + dh;
                int nw = w + dw;
                if (grid[nh][nw] == '#') {
                    continue;
                }
                if (res[0][nh][nw] == INF) {
                    res[0][nh][nw] = res[1][h][w] + 1;
                    que.push({0, nh, nw});
                }
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll H, W;
    cin >> H >> W;
    ll sh, sw, gh, gw;
    cin >> sh >> sw >> gh >> gw;
    auto grid = build_grid(H, W, '#', 1);

    auto res = bfs(grid, {{sh, sw}});
    ll ans = min(res[0][gh][gw], res[1][gh][gw]);
    if (ans != INF) {
        print(ans);
    } else {
        print(-1);
    }
    return 0;
}
