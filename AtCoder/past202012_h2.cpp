/**
 * ・なんとか自力AC！
 * ・グリッドBFS応用
 * ・全マスからあるマスへの到達可否を問う問題。もちろん愚直に全部のマスから試したら間に合わないので、
 * 　ゴールから逆順に各マスを目指せるかチェックする方針を取る。
 * ・この時、1方向にしか進めない4種類のマスについては「1方向からしか入ってこれないマス」とする。
 * ・100万グリッドに4方向も付けた3次元リスト遅そうだなぁと思ったらやっぱきつくてpypyは1つだけTLE。。
 * 　C++で書き直して無事AC。
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

vector<vector<bool>> bfs(vector<string> &grid, vector<vector<vector<bool>>> &grid2, vector<pii> src) {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(H, W, false);
    const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<pii> que;
    for (auto [h, w] : src) {
        que.push({h, w});
        res[h][w] = 1;
    }
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        rep(i, 0, 4) {
            auto [dh, dw] = directions[i];
            int nh = h + dh;
            int nw = w + dw;
            if (grid[nh][nw] == '#') {
                continue;
            }
            if (!grid2[nh][nw][i]) {
                continue;
            }
            if (!res[nh][nw]) {
                res[nh][nw] = 1;
                que.push({nh, nw});
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
    ll si, sj;
    cin >> si >> sj;
    vector<string> grid(H+2);
    rep(j, 0, W+2) {
        grid[0] += '#';
        grid[H+1] += '#';
    }
    rep(i, 1, H+1) {
        string s;
        cin >> s;
        grid[i] = '#' + s + '#';
    }

    // 4種類の1方向マスについて、行ける方向を確認する
    auto grid2 = list3d(H+2, W+2, 4, true);
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            if (grid[i][j] == '<') {
                grid2[i][j] = {0, 0, 0, 0};
                grid2[i][j][3] = 1;
            } else if (grid[i][j] == '>') {
                grid2[i][j] = {0, 0, 0, 0};
                grid2[i][j][2] = 1;
            } else if (grid[i][j] == '^') {
                grid2[i][j] = {0, 0, 0, 0};
                grid2[i][j][1] = 1;
            } else if (grid[i][j] == 'v') {
                grid2[i][j] = {0, 0, 0, 0};
                grid2[i][j][0] = 1;
            }
        }
    }
    auto res = bfs(grid, grid2, {{si, sj}});

    auto ans = list2d(H+2, W+2, '#');
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            if (grid[i][j] != '#') {
                if (res[i][j]) {
                    ans[i][j] = 'o';
                } else {
                    ans[i][j] = 'x';
                }
            }
        }
    }
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
    return 0;
}
