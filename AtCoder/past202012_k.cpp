/**
 * 参考：https://pekempey.hatenablog.com/entry/2016/02/05/002257
 * ・終了後、デバッグを続けてやっとAC。。
 * ・期待値DP、bitDP、メモ化再帰
 * ・考え方はTDPC_Jとほぼ同じで、直線上がグリッドになっただけって感じ。
 * 　ある場所を狙って投げるだけど、空振りする遷移は自己ループになってしまうので、
 * 　式変形してよしなに処理する。
 * ・人によって具体的な実装は色々っぽいけど、参考に挙げた記事の考え方が今は一番しっくり来たので、
 * 　その方針で遷移を作った。これだと遷移先から戻ってくる時に「その先の期待値*そうなる確率」
 * 　ってなる基本の形を崩さず、最後に全体に係る係数を掛けるだけでよくなるので見通しがよさげ。
 * 　全体に係る係数は「1回の遷移の総数/自己ループにならずに遷移する数」になる。
 * ・空振り遷移の回数を意識して、この形をいつも作れるようにすれば期待値DPちょっとは
 * 　うまくやれるようになりそう？　他のやつでもうまくいくかこの後試してみる。
 * ・ちなみにバグらせて本番間に合わなかった原因は、メモ化再帰のメモのvalueがldじゃなくて
 * 　いつも通りllになってたから。しょーもないミスで時間溶かしたー。。。
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

ll gridtoid(ll i, ll j, ll W) {
    return i*W+j;
}

pll idtogrid(ll id, ll W) {
    return divmod(id, W);
}

const vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N = 4;
    vector<string> grid(N+2);
    grid[0] = string(N+2, '.');
    grid[N+1] = string(N+2, '.');
    rep(i, 1, N+1) {
        string s;
        cin >> s;
        grid[i] = '.' + s + '.';
    }
    N += 2;

    ll bit = 0;
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (grid[i][j] == '#') {
                ll id = gridtoid(i, j, N);
                bit |= 1LL<<id;
            }
        }
    }

    map<ll, ld> memo;
    auto rec = [&](auto&& f, ll bit) -> ld {
        if (memo.count(bit)) {
            return memo[bit];
        }
        // 的が全部なくなったら終了
        if (!bit) return 0;
        ld res = INF;
        ld total = 5;
        // 狙う対象にする位置を全部試す
        rep(i, 1, N-1) {
            rep(j, 1, N-1) {
                ll id = gridtoid(i, j, N);
                ld nxt = 1;
                ll cnt = 0;
                // この場所に的があるか
                if (bit>>id & 1) {
                    // その先の期待値 * そうなる確率(1/5)
                    nxt += f(f, bit^1LL<<id) / 5;
                    cnt++;
                }
                // 四方も見る
                for (auto [di, dj] : directions) {
                    ll ni = i + di;
                    ll nj = j + dj;
                    id = gridtoid(ni, nj, N);
                    if (bit>>id & 1) {
                        nxt += f(f, bit^1LL<<id) / 5;
                        cnt++;
                    }
                }
                if (cnt) {
                    // 5箇所見た全体に「1回の遷移の総数/自己ループにならずに遷移する数」を掛ける
                    nxt *= total / cnt;
                    chmin(res, nxt);
                }
            }
        }
        memo[bit] = res;
        return res;
    };
    ld res = rec(rec, bit);
    print(res);
    return 0;
}
