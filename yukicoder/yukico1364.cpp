/**
 * 参考：https://drive.google.com/file/d/1cwROAy4t7eQXZurA_ypDvZGNKqPrZVw2/view
 * 　　　https://twitter.com/SSRS_cp/status/1352630536636776455
 * 　　　https://yukicoder.me/submissions/609463
 * ・自力ならず。このレベルのグラフ問題を通せるようになっていきたいね。。
 * ・SCC(強連結成分分解)、DAGのDP
 * ・ACLのSCC初めて使った。ちょうどよくverifyできた。
 * ・比較的近いことはやろうとしてたんだけど、色々考察が足りず。。
 * ・まず無理なケースを弾くパートで、SCCしようとしたのはよかったんだけど、
 * 　そこから必要な部分だけでDPしようとして詰まってしまった。
 * ・先にグラフを必要な部分だけに絞り込むべきだった。今回の問題で答えに必要なのは、
 * 　「頂点0から到達できる頂点」でかつ「頂点Nに到達できる頂点」な場所だけなので、
 * 　先にグラフをこれらの頂点だけに減らしておくと、関係ないところの閉路をどう無視するかとか、
 * 　頂点0じゃないところからNに着いてしまう道の通り数をどう弾くかとか、
 * 　色々な面倒を考えなくて済むようになる。
 * 　全てが必要な頂点になるので、閉路検出は1つでも見つかればNGにできるし、
 * 　頂点0から到達できる頂点しか入れてないので、頂点0より手前から遷移されることもなくなる。
 * ・で、ここがクリアできても、DP遷移がうまく作れず。。
 * 　今回の辺には長さと個数という2つの属性があるので、これらを適切に遷移に織り込む必要がある。
 * 　公式解説のシグマの式変形はよく分からなくなったので、mugenさんのコードを参考にした。
 * 　ようは「その頂点に至る道の本数の通り数」と「その頂点に至る道の長さの総和」を
 *   分けて管理する必要があった。全社の遷移はよく通し数数える時にやるやつなのでいいとして、
 * 　後者の遷移が自分で導くのは難しいなぁとなった。その手前までの通り数に今回の長さを掛けて、
 * 　それをこの手前までの長さに足して、それに今回の本数を掛ける、
 * 　って文面にすると余計やこしい気がする。。まあコードの遷移見て。。
 * ・最後に、遷移で掛け算が複数回出るのもあり、MOD取り適当にやっててWA。。大人しくModint使ったよ。
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

vector<ll> LIST(ll N) { vector<ll> A(N); rep(i, 0, N) cin >> A[i]; return A; }

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
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <vector>
namespace atcoder {
namespace internal {
template <class E> struct csr {
    std::vector<int> start;
    std::vector<E> elist;
    csr(int n, const std::vector<std::pair<int, E>>& edges)
        : start(n + 1), elist(edges.size()) {
        for (auto e : edges) {
            start[e.first + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            start[i] += start[i - 1];
        }
        auto counter = start;
        for (auto e : edges) {
            elist[counter[e.first]++] = e.second;
        }
    }
};
}  // namespace internal
}  // namespace atcoder
#include <algorithm>
#include <cassert>
#include <vector>
#include <algorithm>
#include <utility>
#include <vector>
namespace atcoder {
namespace internal {
struct scc_graph {
  public:
    scc_graph(int n) : _n(n) {}
    int num_vertices() { return _n; }
    void add_edge(int from, int to) { edges.push_back({from, {to}}); }
    std::pair<int, std::vector<int>> scc_ids() {
        auto g = csr<edge>(_n, edges);
        int now_ord = 0, group_num = 0;
        std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
        visited.reserve(_n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = ord[v] = now_ord++;
            visited.push_back(v);
            for (int i = g.start[v]; i < g.start[v + 1]; i++) {
                auto to = g.elist[i].to;
                if (ord[to] == -1) {
                    self(self, to);
                    low[v] = std::min(low[v], low[to]);
                } else {
                    low[v] = std::min(low[v], ord[to]);
                }
            }
            if (low[v] == ord[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    ord[u] = _n;
                    ids[u] = group_num;
                    if (u == v) break;
                }
                group_num++;
            }
        };
        for (int i = 0; i < _n; i++) {
            if (ord[i] == -1) dfs(dfs, i);
        }
        for (auto& x : ids) {
            x = group_num - 1 - x;
        }
        return {group_num, ids};
    }
    std::vector<std::vector<int>> scc() {
        auto ids = scc_ids();
        int group_num = ids.first;
        std::vector<int> counts(group_num);
        for (auto x : ids.second) counts[x]++;
        std::vector<std::vector<int>> groups(ids.first);
        for (int i = 0; i < group_num; i++) {
            groups[i].reserve(counts[i]);
        }
        for (int i = 0; i < _n; i++) {
            groups[ids.second[i]].push_back(i);
        }
        return groups;
    }
  private:
    int _n;
    struct edge {
        int to;
    };
    std::vector<std::pair<int, edge>> edges;
};
}  // namespace internal
}  // namespace atcoder
namespace atcoder {
struct scc_graph {
  public:
    scc_graph() : internal(0) {}
    scc_graph(int n) : internal(n) {}
    void add_edge(int from, int to) {
        int n = internal.num_vertices();
        assert(0 <= from && from < n);
        assert(0 <= to && to < n);
        internal.add_edge(from, to);
    }
    std::vector<std::vector<int>> scc() { return internal.scc(); }
  private:
    internal::scc_graph internal;
};
}  // namespace atcoder
using namespace atcoder;

template<int mod>
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while(b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while(n > 0) {
        if(n & 1) ret *= mul;
        mul *= mul;
        n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    static int get_mod() { return mod; }
};
using mint = ModInt<MOD>;

vector<int> bfs(vvi &nodes, int src) {

    int N = nodes.size();
    vector<int> res(N, -1);
    queue<int> que;
    res[src] = 0;
    que.push(src);

    while(!que.empty()) {
        int u = que.front(); que.pop();
        for (auto v: nodes[u]) {
            if (res[v] == -1) {
                res[v] = res[u]+1;
                que.push(v);
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;
    N++;
    vvi nodes(N), nodesrev(N);
    vector<tuple<ll, ll, ll, ll>> edges;
    rep(i, 0, M) {
        ll u, v, l, a;
        cin >> u >> v >> l >> a;
        nodes[u].pb(v);
        nodesrev[v].pb(u);
        edges.pb({u, v, l, a});
    }

    // 頂点0から到達できる頂点と頂点Nに到達できる頂点だけに絞り込む
    auto res = bfs(nodes, 0);
    auto resrev = bfs(nodesrev, N-1);
    set<ll> need;
    rep(i, 0, N) {
        if (res[i] != -1 and resrev[i] != -1) {
            need.insert(i);
        }
    }
    // 必要な頂点だけでグラフを再構築
    vector<vector<tuple<ll, ll, ll>>> nodes2(N);
    scc_graph scc(N);
    for (auto& [u, v, l, a] : edges) {
        if (need.count(u) and need.count(v)) {
            nodes2[u].pb({v, l, a});
            scc.add_edge(u, v);
        }
    }

    auto groups = scc.scc();
    // dp1[i] := その頂点に至る道の本数の通り数
    // dp2[i] := その頂点に至る道の長さの総和
    vector<mint> dp1(N), dp2(N);
    dp1[0] = 1;
    for (auto &group : groups) {
        if (group.size() >= 2) {
            print("INF");
            return 0;
        }
        // SCCの結果がトポソ順になっているので、そのままDPできる
        for (ll u : group) {
            for (auto [v, l, a] : nodes2[u]) {
                dp1[v] += dp1[u]*a;
                dp2[v] += (dp2[u]+dp1[u]*l)*a;
            }
        }
    }
    mint ans = dp2[N-1];
    print(ans);
    return 0;
}
