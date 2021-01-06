/**
 * 参考：螺旋本P.464
 * ・ちょうど螺旋本で飛ばしてたテーマが出てきたので。
 * ・蟻本演習4-5-3
 * ・A*(エースター)
 * ・IDA*と同じ評価値を使って、こっちはダイクストラっぽいことをする。
 * ・頑張ってグリッド文字列変換やった。意外と変更箇所多くて疲れた。。
 * 　そしてこれでもMLE。。
 * ・こっちも訪問済管理してみる。まあそれでもMLE。。。
 * ・さらにN+2の番兵部分をなくしてみた。これは結構効いたけど、それでも最大ケースはMLEだしTLE。。
 * ・訪問済mapじゃなくてsetでいいじゃん、と、判定処理をuの時じゃなくてvの時にしてみた。まあTLE。。
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
int calc_exp(const vector<vector<char>> &grid, map<char, pii> &goal) {
    int res = 0;
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (grid[i][j] == '0') continue;
            auto [h, w] = goal[grid[i][j]];
            res += abs(i-h) + abs(j-w);
        }
    }
    return res;
}

string gridtostr(vector<vector<char>> &grid) {
    string res;
    rep(i, 0, N) {
        rep(j, 0, N) {
            res += grid[i][j];
        }
    }
    return res;
}

vector<vector<char>> strtogrid(string &s) {
    auto res = list2d(N, N, '*');
    rep(i, 0, N*N) {
        auto [h, w] = divmod(i, N);
        res[h][w] = s[i];
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    auto grid = list2d(N, N, '*');
    pii s;
    rep(i, 0, N) {
        rep(j, 0, N) {
            int a;
            cin >> a;
            if (a == 0) {
                s = {i, j};
            }
            if (a < 10) {
                grid[i][j] = tochar(a);
            } else {
                grid[i][j] = 'a' + (a-10);
            }
            
        }
    }

    map<char, pii> goal;
    int num = 1;
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (num < 10 or num == 16) {
                goal[tochar(num%16)] = {i, j};
            } else {
                goal['a'+(num%16-10)] = {i, j};
            }
            num++;
        }
    }

    int ans = -1;
    using P = tuple<int, int, string>;
    priority_queue<P, vector<P>, greater<P>> que;
    que.push({0, 0, gridtostr(grid)});
    unordered_set<string> visited;
    while (!que.empty()) {
        auto [_, dist, s] = que.top(); que.pop();
        auto [h, w] = divmod(s.find('0'), N);
        visited.insert(s);
        grid = strtogrid(s);
        dist++;
        for (auto [dh, dw] : directions) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nh >= N or nw < 0 or nw >= N) continue;
            swap(grid[h][w], grid[nh][nw]);
            int exp = calc_exp(grid, goal);
            if (!exp) {
                ans = dist;
                break;
            }
            int cost = dist+exp;
            s = gridtostr(grid);
            if (!visited.count(s)) {
                que.push({cost, dist, s});
            }
            swap(grid[h][w], grid[nh][nw]);
        }
    }
    print(ans);
    return 0;
}
