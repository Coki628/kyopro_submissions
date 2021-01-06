/**
 * 参考：http://www.utpc.jp/2013/slides/J.pdf
 * ・蟻本演習4-5-3
 * ・A*(エースター)
 * ・自力ならず。。
 * ・予測に使う評価値は頂点0への距離でいいだろうは合ってたのに、有向グラフなのに逆辺にしてなくてNG。。
 * 　これ前もハマったことあるなー。。
 * ・後は普通で、実際のコストに、上の評価値を追加したものをキーにしてダイクストラっぽく。
 * 　頂点0を通って何回でも行き来するので、訪問済管理はしない。
 * ・WAが取れなくて散々悩んで結局最後の原因はansがllじゃなくてintになってたこと。。
 * 　今回はダイクストラのキューのメモリが気になったからint混ぜてたけど、
 * 　ほんとよっぽどの理由がない時は全部llがいいね。頂点番号だけintとか思ってても
 * 　絶対うっかりコストでintとか見落としある。。
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
            if (dist + cost < res[v]) {
                res[v] = dist + cost;
                que.push({dist+cost, v});
            }
        }
    }
    return res;
}

ll calc_exp(const vector<ll> &dist, int u) {
    return dist[u];
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N, M, K;
    cin >> N >> M >> K;
    vvpll nodes(N), nodesrev(N);
    rep(i, 0, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        nodes[u].pb({v, c});
        nodesrev[v].pb({u, c});
    }

    auto res = dijkstra(nodesrev, 0);

    vector<ll> ans;
    using P = tuple<ll, ll, int>;
    priority_queue<P, vector<P>, greater<P>> que;
    que.push({0, 0, 0});
    while (!que.empty() and ans.size() < K) {
        auto [_, dist, u] = que.top(); que.pop();
        if (dist != 0 and u == 0) {
            ans.pb(dist);
            if (ans.size() == K) break;
        }
        for (auto [v, c] : nodes[u]) {
            ll exp = calc_exp(res, v);
            if (exp == INF) continue;
            que.push({dist+c+exp, dist+c, v});
        }
    }
    while (ans.size() < K) ans.pb(-1);
    for (ll a : ans) print(a);
    return 0;
}
