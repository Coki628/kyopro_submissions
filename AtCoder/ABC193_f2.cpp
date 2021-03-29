/*
参考：https://nullkara.jp/2021/02/28/atcoder_abc193/#toc9
　　　https://www.slideshare.net/shindannin/project-selection-problem
・E8さん精選100+50問埋め：最大流／最小カット
・ちょうど最近ABCで出たやつがあったのでupsolveした。
・最小カット、Project Selection Problem(燃やす埋める)、二部グラフ
・いやーむずい。グラフの繋ぎ方がいまいち分からずいくつか解説読んだ。
　自分的に一番入ってきたものを参考に挙げておく。
　あとこっちは前にも読んだけど、やっぱり診断人さんのスライドは
　詳しくしっかり書かれているので、これも入れておいた。
・単に最小カットと言うだけなら、最大流を流せばいいのでそこまで難しく感じない。
　燃やす埋めるがややこしく感じるのは、最小カットをするけど、
　求めたいのは最大値だったりして利益最大化を損失最小化に読み替える必要が
　出てくるあたりにあると思う。今回もそれを使う。
・今回のケースで損失にポイントを付けたい場合、同じ色のマスが接する時になるが、
　これだと黒→黒みたいになってしまって、黒→白とフローを流したいのに使えない。
　そこで、市松の片方を色反転させて、黒→白に損失が付くようにする。
・色の選択については、色が決まっているところは逆の選択肢が選べないように、
　無理な方をINFにする。これで最大流は絶対INF側を流れるので、
　最小カットで切る方(選択で選ぶ方)が定まる。
・?マスはどちらも選べるので、両側をコスト0にする。
　これだと白黒両方選ぶみたいな変なフローが流れて壊れてしまいそうな気になるが、
　選ぶのはカットの方なので0の辺にフローは流れないし、
　実際うまく全て0になってるなら損失0(完全な白黒市松になっていて利得最大)
　ということなので、それも成り立つことがある状態なので問題ない。
・マス同士の辺については、隣接するものは全てつないでおく。
　通るかどうかは始点・終点との辺が決めるので、こちらは現在の白黒の状態が
　どうなのかは考えなくていい。
・昔の問題復習したりで噛み砕いたので、一般的な話をもう少し。
　燃やす埋めるの基本構造は、始点、終点、選択の対象物となる頂点、
　選択肢Aを表す始点との辺、選択肢Bを表す終点との辺、対象物同士の関連を表す辺、
　あたりで成り立っている。
　今回は色を塗った時点では、それ単体では損失が変化しないので、
　INF以外の選択肢を表す辺は全てコスト0になっているが、これが変化する場合、
　ここの辺にコストが発生してくる。選択できないものはINFとする。
　関連を表す辺には、ある対象物でAを選んで、別のある対象物でBを選んだ場合、
　損失が発生するような場合に辺を張る。今回の隣接マスがこれ。
　ここでもそういう組み合わせが選べないようなところにはINFを張る。
　やっぱり利益なのに損失に読み替えて色々考えなきゃいけないのが
　話をややこしくしてると思うんだよなぁ。
　まあそうしないと求まらないんだからしょうがないんだけど。
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
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for(ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for(ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for(ll i = a, _bb = b; (a <= i && i < _bb) or (a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define elif else if
// constexpr ll INF = 1e18;
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;
constexpr ld EPS = 1e-10;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(deque<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
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
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename T> unordered_map<T, ll> Counter(vector<T> &A) { unordered_map<T, ll> res; for (T a : A) res[a]++; return res; }
unordered_map<char, ll> Counter(string &S) { unordered_map<char, ll> res; for (char c : S) res[c]++; return res; }

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

////////// 最大流 //////////
// --- ACL start --- //
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>
namespace atcoder {
namespace internal {
template <class T> struct simple_queue {
    std::vector<T> payload;
    int pos = 0;
    void reserve(int n) { payload.reserve(n); }
    int size() const { return int(payload.size()) - pos; }
    bool empty() const { return pos == int(payload.size()); }
    void push(const T& t) { payload.push_back(t); }
    T& front() { return payload[pos]; }
    void clear() {
        payload.clear();
        pos = 0;
    }
    void pop() { pos++; }
};
}  // namespace internal
}  // namespace atcoder
namespace atcoder {
template <class Cap> struct mf_graph {
  public:
    mf_graph() : _n(0) {}
    mf_graph(int n) : _n(n), g(n) {}
    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = int(pos.size());
        pos.push_back({from, int(g[from].size())});
        int from_id = int(g[from].size());
        int to_id = int(g[to].size());
        if (from == to) to_id++;
        g[from].push_back(_edge{to, to_id, cap});
        g[to].push_back(_edge{from, from_id, 0});
        return m;
    }
    struct edge {
        int from, to;
        Cap cap, flow;
    };
    edge get_edge(int i) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    std::vector<edge> edges() {
        int m = int(pos.size());
        std::vector<edge> result;
        for (int i = 0; i < m; i++) {
            result.push_back(get_edge(i));
        }
        return result;
    }
    void change_edge(int i, Cap new_cap, Cap new_flow) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto& _e = g[pos[i].first][pos[i].second];
        auto& _re = g[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }
    Cap flow(int s, int t) {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }
    Cap flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        std::vector<int> level(_n), iter(_n);
        internal::simple_queue<int> que;
        auto bfs = [&]() {
            std::fill(level.begin(), level.end(), -1);
            level[s] = 0;
            que.clear();
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto e : g[v]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return;
                    que.push(e.to);
                }
            }
        };
        auto dfs = [&](auto self, int v, Cap up) {
            if (v == s) return up;
            Cap res = 0;
            int level_v = level[v];
            for (int& i = iter[v]; i < int(g[v].size()); i++) {
                _edge& e = g[v][i];
                if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                Cap d =
                    self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));
                if (d <= 0) continue;
                g[v][i].cap += d;
                g[e.to][e.rev].cap -= d;
                res += d;
                if (res == up) return res;
            }
            level[v] = _n;
            return res;
        };
        Cap flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) break;
            std::fill(iter.begin(), iter.end(), 0);
            Cap f = dfs(dfs, t, flow_limit - flow);
            if (!f) break;
            flow += f;
        }
        return flow;
    }
    std::vector<bool> min_cut(int s) {
        std::vector<bool> visited(_n);
        internal::simple_queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            visited[p] = true;
            for (auto e : g[p]) {
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return visited;
    }
  private:
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;
    };
    std::vector<std::pair<int, int>> pos;
    std::vector<std::vector<_edge>> g;
};
}  // namespace atcoder
// --- ACL end --- //
using namespace atcoder;

ll gridtoid(ll i, ll j, ll W) {
    return i*W+j;
}

pll idtogrid(ll id, ll W) {
    return divmod(id, W);
}

void solve() {
    ll N;
    cin >> N;
    vector<string> grid(N);
    rep(i, N) cin >> grid[i];

    // 市松の片方を反転させておく
    rep(i, N) {
        rep(j, N) {
            if ((i+j)%2 == 1) {
                if (grid[i][j] == 'B') {
                    grid[i][j] = 'W';
                } elif (grid[i][j] == 'W') {
                    grid[i][j] = 'B';
                }
            }
        }
    }

    mf_graph<ll> mf(N*N+2);
    ll s = N*N;
    ll t = N*N+1;
    rep(h, N) {
        rep(w, N) {
            ll i = gridtoid(h, w, N);
            // 始点・終点との辺
            if (grid[h][w] == 'B') {
                // 色が決まってる時はカットで選びたくない方をINFに
                mf.add_edge(s, i, 0);
                mf.add_edge(i, t, INF);
            } elif (grid[h][w] == 'W') {
                mf.add_edge(s, i, INF);
                mf.add_edge(i, t, 0);
            } else {
                mf.add_edge(s, i, 0);
                mf.add_edge(i, t, 0);
            }
            // マス同士の辺
            if (h != N-1) {
                ll j = gridtoid(h+1, w, N);
                mf.add_edge(i, j, 1);
                mf.add_edge(j, i, 1);
            }
            if (w != N-1) {
                ll j = gridtoid(h, w+1, N);
                mf.add_edge(i, j, 1);
                mf.add_edge(j, i, 1);
            }
        }
    }
    // 最大利得から、最小カットを引く
    ll total = N*(N-1)*2;
    ll ans = total - mf.flow(s, t);
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    solve();

    return 0;
}
