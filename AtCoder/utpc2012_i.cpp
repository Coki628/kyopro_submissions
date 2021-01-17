/**
 * 参考：http://www.utpc.jp/2012/slides/shortestQuery.pdf
 * ・蟻本演習4-6-1
 * ・分割統治法
 * ・横幅全部を半分にしながら全ての段階で最短経路を取るので、ダイクストラの検索結果を
 * 　最大で多分横幅*2=2万個くらいは取ることになって、計算量やばくない？ってなるけど、
 * 　探索する横幅が毎回半分になっていくのがかなり効いているらしくて間に合う。
 * ・分割統治むずい。境界でめっちゃバグる。。すごい苦労してやっとサンプル全部通るようになって、
 * 　ここから長いだろうなーって思いながら投げたら一発で通ってびっくり。
 * ・最初閉区間でやろうとしたら、区間を狭めるところが幅2より狭くならなくて結局半開区間に戻した。。
 * ・これ制約6秒あるんだけど、1.95秒でACした。mapにすごい重たい感じの情報の詰め方してるし、
 * 　間に合うのがなんか不思議ー。logは強い。
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

ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

template<typename T>
void transpose(vector<vector<T>> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(W, H, (T)0);
    rep(i, 0, H) {
        rep(j, 0, W) {
            res[j][i] = grid[i][j];
        }
    }
    swap(res, grid);
}

using P = tuple<ll, int, int>;
vvl dijkstra(vvl &grid, pii src) {

    int H = grid.size();
    int W = grid[0].size();
    auto res = list2d(H, W, INF);
    const vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    priority_queue<P, vector<P>, greater<P>> que;
    auto [sh, sw] = src;
    // 出発マス分もコストに入れておく
    que.push({grid[sh][sw], sh, sw});
    res[sh][sw] = grid[sh][sw];

    while (!que.empty()) {
        auto [dist, h, w] = que.top(); que.pop();
        if (res[h][w] < dist) {
            continue;
        }
        for (auto [dh, dw] : directions) {
            int nh = h + dh;
            int nw = w + dw;
            if (grid[nh][nw] == -1) {
                continue;
            }
            ll cost = grid[nh][nw];
            if (dist + cost < res[nh][nw]) {
                res[nh][nw] = dist + cost;
                que.push({dist+cost, nh, nw});
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll W, H, Q;
    cin >> W >> H >> Q;
    auto grid = list2d(H+2, W+2, -1LL);
    rep(i, 1, H+1) {
        rep(j, 1, W+1) {
            cin >> grid[i][j];
        }
    }
    // 見やすさのため横長にしておく
    transpose(grid);
    swap(H, W);

    // 前計算：区間[l,r)を範囲、出発点の横位置をmとした最短路を計算する
    // memo[(左端,右端)][縦位置] := そこを出発点とした最短経路を示す2次元配列
    map<pll, vector<vvl>> memo;
    auto rec = [&](auto&& f, ll l, ll m, ll r) -> void {

        if (memo.count({l, r})) return;

        // 今の横幅に合わせて小さくしたグリッドを構築
        ll W2 = r-l;
        auto grid2 = list2d(H+2, W2+2, -1LL);
        rep(i, 1, H+1) {
            rep(j, 1, W2+1) {
                grid2[i][j] = grid[i][j+l-1];
            }
        }
        // 縦位置全てについてを出発点として最短経路を出す
        rep(i, 1, H+1) {
            auto res = dijkstra(grid2, {i, m-l+1});
            memo[{l, r}].pb(res);
        }
        // 区間幅が残っている限り再帰的にやる
        if (l < m) f(f, l, (l+m)/2, m);
        if (m < r) f(f, m, (m+r)/2, r);
    };
    rec(rec, 1, (W+2)/2, W+1);

    rep(i, 0, Q) {
        ll sw, sh, gw, gh;
        cin >> sh >> sw >> gh >> gw;
        if (sw > gw) {
            swap(sw, gw);
            swap(sh, gh);
        }

        // クエリに答える
        auto rec = [&](auto&& f, ll l, ll m, ll r) -> ll {
            ll res = INF;
            // この区間幅での最短経路を、全ての縦位置で見て最小を取る
            rep(i, 0, H) {
                // (sh,sw)~出発マス + 出発マス~(gh,gw) - 出発マスのコスト(2回足してるので)
                chmin(res, memo[{l, r}][i][sh][sw-l+1]+memo[{l, r}][i][gh][gw-l+1]-memo[{l, r}][i][i+1][m-l+1]);
            }
            // 区間幅が残っている限り再帰的に調べて、最小を取ってくる
            if (gw < m) chmin(res, f(f, l, (l+m)/2, m));
            if (m < sw) chmin(res, f(f, m, (m+r)/2, r));
            return res;
        };
        ll ans = rec(rec, 1, (W+2)/2, W+1);
        print(ans);
    }
    return 0;
}
