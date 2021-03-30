/*
参考：https://atcoder.jp/contests/abc197/editorial
　　　https://kanpurin.hatenablog.com/entry/2021/03/28/034311
・むずい。
・回文、グラフ
・2つのルートがうまく合流する場所を見つけるため、
　{頂点1から始める文字列, 頂点Nから始める文字列} のペアを頂点とした、
　N*N頂点の新たなグラフを構築する。
・ぱっと見、この頂点ペアが元のグラフの辺を表しそうな見た目をしているが違う。
　この頂点ペアはあくまで上で定義したようなものなので、元の辺とは
　直接の関係はない。ここがまたややこしい。
・このグラフに張る必要のある辺は、
　・奇数長回文の終点への辺
　・偶数長回文の終点への辺
　・同じ文字の辺同士の関係を表す辺
　の3種類で、順番に説明する。
・上2つはまあそんなに難しくない。1とNから始めた2つの文字列が、
　元のグラフで同じ頂点に辿り着くなら、それは偶数長の回文になるし、
　元のグラフで隣接した頂点に辿り着くなら、間の辺の文字が何であれ奇数長の回文になる。
　それぞれコスト0とコスト1で終点への辺を繋げばいい。
・3つ目がややこしい。元のグラフに張ってある2つの辺で、文字が同じであるなら、
　その2つを使って2つの文字列は移動ができる。それぞれにどちら側から
　移動するかがあるので、2*2=4通りの動き方がある。これに合わせて辺を張る。
　なんか思わず元の辺があるところに張りたくなってしまうのだが、
　そうではなく互い違いみたいな位置に張る。分かりにくい。
・これらを準備したグラフに{1, N}の頂点からダイクストラを流せば答えが出る。
・頂点ペアを頂点にした新たなグラフを構築して、頂点ペアの動き方から
　2つのパスに対応する答えを見つける方針は目から鱗だったな。
　前に似たような話で、辺を頂点に見立てて別グラフを構築する問題があって(ABC139e)、
　確かに似てるんだけど、今回は元の辺とは別モノの頂点ペアを頂点としているので、
　解説ちょっと見た時に同じように考えようとして混乱した。
　やってることは似てるんだけど、今回は2つのパスに対応する頂点ペアで
　グラフを考えるんだよね。ちゃんと理解して次に繋げたいな。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
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
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr ld EPS = 1e-10;
constexpr ld PI = M_PI;

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
int bit_length(ll x) { return floor(log2(x))+1; }
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if(res == "") res += '0'; return res; }

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
    bool operator<(const ModInt &p) const { return x < p.x; }
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

template<typename T>
vector<T> dijkstra(vector<vector<pair<ll, T>>> &nodes, int src) {

    int N = nodes.size();
    vector<T> res(N, INF);
    priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> que;
    res[src] = 0;
    que.push({0, src});

    pair<T, ll> p;
    T dist, cost;
    int u, v;
    while(!que.empty()) {
        p = que.top(); que.pop();
        tie(dist, u) = p;
        if (res[u] < dist) {
            continue;
        }
        for (auto p: nodes[u]) {
            tie(v, cost) = p;
            if (dist+cost < res[v]) {
                res[v] = dist+cost;
                que.push({dist+cost, v});
            }
        }
    }
    return res;
}

ll gridtoid(ll i, ll j, ll W) {
    return i*W+j;
}

pll idtogrid(ll id, ll W) {
    return divmod(id, W);
}

void solve() {
    ll N, M;
    cin >> N >> M;
    ll L = N*N;

    vvpll nodes(L+1);
    ll s = gridtoid(0, N-1, N);
    ll t = L;
    vector<vector<pll>> edges(26);
    rep(_, M) {
        ll u, v;
        char c;
        cin >> u >> v >> c;
        u--; v--;
        edges[c-'a'].pb({u, v});
        // 奇数長回文の終点
        ll a = gridtoid(u, v, N);
        ll b = gridtoid(v, u, N);
        nodes[a].pb({t, 1});
        nodes[b].pb({t, 1});
    }
    rep(i, N) {
        // 偶数長回文の終点
        ll a = gridtoid(i, i, N);
        nodes[a].pb({t, 0});
    }
    rep(c, 26) {
        ll m = edges[c].size();
        for (auto [u1, v1] : edges[c]) {
            for (auto [u2, v2] : edges[c]) {
                // 同じ文字の辺同士の関係
                ll a = gridtoid(u1, u2, N);
                ll b = gridtoid(v1, v2, N);
                nodes[a].pb({b, 2});
                nodes[b].pb({a, 2});
                a = gridtoid(u1, v2, N);
                b = gridtoid(v1, u2, N);
                nodes[a].pb({b, 2});
                nodes[b].pb({a, 2});
            }
        }
    }

    auto res = dijkstra(nodes, s);
    ll ans = res[t];
    if (ans < INF) {
        print(ans);
    } else {
        print(-1);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
