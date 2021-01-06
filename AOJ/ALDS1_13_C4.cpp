/**
 * 参考：螺旋本P.462
 * ・ちょうど螺旋本で飛ばしてたテーマが出てきたので。
 * ・蟻本演習4-5-3
 * ・反復深化、IDA*(反復深化エースター)
 * ・各盤面から「この先でかかる最低手数」を予測して、
 * 　現在+予測値 > 深さ制限 になったら枝刈りする。これでAC0.63秒。速いね。
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

const int N = 4;
const int LIMIT = 45;
const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 最低残り手数を予測
int calc_exp(vector<vector<int>> &grid, map<int, pii> &goal) {
    int res = 0;
    rep(i, 1, N+1) {
        rep(j, 1, N+1) {
            if (grid[i][j] == 0) continue;
            auto [h, w] = goal[grid[i][j]];
            res += abs(i-h) + abs(j-w);
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    auto grid = list2d(N+2, N+2, -1);
    pii s;
    rep(i, 1, N+1) {
        rep(j, 1, N+1) {
            int a;
            cin >> a;
            if (a == 0) {
                s = {i, j};
            }
            grid[i][j] = a;
        }
    }

    map<int, pii> goal;
    int num = 1;
    rep(i, 1, N+1) {
        rep(j, 1, N+1) {
            goal[num%16] = {i, j};
            num++;
        }
    }

    int ans = -1;
    auto rec = [&](auto&& f, vector<vector<int>> &grid, pii cur, pii prv, int depth, int limit) -> bool {
        int exp = calc_exp(grid, goal);
        if (!exp) {
            ans = depth;
            return true;
        }
        if (depth+exp > limit) {
            return false;
        }
        auto [h, w] = cur;
        for (auto& [dh, dw] : directions) {
            pii nxt = {h+dh, w+dw};
            if (nxt == prv) continue;
            auto [nh, nw] = nxt;
            if (grid[nh][nw] != -1) {
                swap(grid[h][w], grid[nh][nw]);
                if (f(f, grid, nxt, cur, depth+1, limit)) {
                    return true;
                }
                swap(grid[h][w], grid[nh][nw]);
            }
        }
        return false;
    };
    rep(limit, 1, LIMIT+1) {
        if (rec(rec, grid, s, {-1, -1}, 0, limit)) {
            break;
        }
    }
    print(ans);
    return 0;
}
