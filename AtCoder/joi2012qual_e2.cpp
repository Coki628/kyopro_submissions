/**
 * ・E8さん精選100+50問埋め：幅優先探索
 * ・自力AC！結構時間かかった。。
 * ・六角形グリッド、BFS
 * ・移動に斜めが半分入るのは覚えてたんだけど、サンプル合わなくてちょっと悩んだ。
 * 　結局、縦の偶奇で行ける斜めが変わるのを考慮してなかった。そこ合わせて無事AC。
 * ・実装面で、画面外の外周を通れる場所にするために、さらに外側に壁作って、
 * 　2回り大きいグリッドにした。これなら適当な外周1箇所始点にすれば全部見れる。
 * ・塗る壁の管理は、BFSの入りの方向を状態に持った。
 * 　グリッドで入りの方向を状態に持つの、ちょくちょく出てくるね。
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
#define ALL(A) A.begin(), A.end()
#define elif else if
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

vector<ll> LIST(ll N) { vector<ll> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
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

template<typename T> T sum(vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> &A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(int x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) { ok = mid; } else { ng = mid; } } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) { ok = mid; } else { ng = mid; } } return ok; }

template<int mod> struct ModInt {
    int x;
    ModInt() : x(0) {}
    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; }
    ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; }
    ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; }
    ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; }
    ModInt operator-() const { return ModInt(-x); }
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    bool operator==(const ModInt &p) const { return x == p.x; }
    bool operator!=(const ModInt &p) const { return x != p.x; }
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
};
using mint = ModInt<MOD>;

vector<vector<vector<bool>>> bfs(vvi &grid, vector<pii> src) {

    int H = grid.size();
    int W = grid[0].size();
    auto visited = list2d(H, W, false);
    // res[d][i][j] := 方向dからマス(i,j)に入れるか
    auto res = list3d(8, H, W, false);
    const vector<pii> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    queue<pii> que;
    for (auto [h, w] : src) {
        que.push({h, w});
        visited[h][w] = 1;
    }
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        rep(i, 0, 8) {
            // 縦の偶奇で斜めに行ける方向を管理
            if (h % 2 == 0 and (i == 4 or i == 5)) continue;
            if (h % 2 == 1 and (i == 6 or i == 7)) continue;
            auto& [dh, dw] = directions[i];
            int nh = h + dh;
            int nw = w + dw;
            // 枠外
            if (grid[nh][nw] == -1) continue;
            // 建物
            elif (grid[nh][nw] == 1) {
                // 今回の向きからの入りを記録する
                res[i][nh][nw] = 1;
            // 移動
            } elif (!visited[nh][nw]) {
                visited[nh][nw] = 1;
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
    cin >> W >> H;
    // 2回り大きいグリッド
    auto grid = list2d(H+4, W+4, 0);
    rep(i, 0, H+4) {
        grid[i][0] = -1;
        grid[i][W+3] = -1;
    }
    rep(j, 0, W+4) {
        grid[0][j] = -1;
        grid[H+3][j] = -1;
    }
    rep(i, 2, H+2) {
        rep(j, 2, W+2) {
            cin >> grid[i][j];
        }
    }
    auto res = bfs(grid, {{1, 1}});

    // 全マス、全方向を合計
    ll ans = 0;
    rep(d, 0, 8) {
        rep(i, 2, H+2) {
            rep(j, 2, W+2) {
                ans += res[d][i][j];
            }
        }
    }
    print(ans);
    return 0;
}
