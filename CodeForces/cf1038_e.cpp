/**
 * 参考：https://codeforces.com/blog/entry/61692
 * 　　　https://twitter.com/_____sno_____/status/1367639734017609729
 * 　　　https://twitter.com/yuusanlondon/status/1367634514319712258
 * ・自力では全然だった。むずい。でも学びのある問題で良かった。
 * ・グラフ、ビット全探索、オイラー路、一筆書きの判定、UnionFind
 * ・題意を満たすには、元のグラフから、最も利得の大きいオイラー路(一筆書きのパス)を見つける必要があるが、まともにはできない。
 * 　そこで考察すると、同じ2頂点を結ぶ辺は、2本あれば往復して得しかしないので、2x本はないものとして考えられる。
 * 　また、オイラー路の判定に必要なのは連結かどうかと各頂点の次数の偶奇なので、ここからも2本以上減らすメリットはないと言える。
 * 　そこで、各辺について1本減らしてみて試す、というのを全探索する解法が通用することになる。
 * 　これは辺が最大で4*4=16本(無向辺であり、自己ループは減らす必要がないので実際は6本)しかないので、
 * 　辺集合をビット全探索できる。
 * ・ビット全探索の中では、辺を減らしたグラフの構築、UFによるグラフの連結、連結成分毎の総和の集計、
 * 　連結成分がオイラー路になっているかの判定、グラフの状態戻し、を順番に進めていく。
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
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
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
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

struct UnionFind {

    int n, groupcnt;
    vector<int> par, rank, size;
    vector<bool> tree;

    UnionFind(int n) : n(n) {
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        tree.resize(n, 1);
        rep(i, 0, n) par[i] = i;
        groupcnt = n;
    }

    UnionFind() {}

    void resize(int _n) {
        n = _n;
        par.resize(n);
        rank.resize(n);
        size.resize(n, 1);
        rep(i, 0, n) par[i] = i;
        groupcnt = n;
    }

    // 根の検索(グループ番号)
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            par[x] = find(par[x]);
            return par[x];
        }
    }

    // 併合
    void merge(int a, int b) {
        int x = find(a);
        int y = find(b);

        if (x == y) {
            tree[x] = false;
            return;
        }
        if (!tree[x] or !tree[y]) {
            tree[x] = tree[y] = false;
        }

        groupcnt--;
        if (rank[x] < rank[y]) {
            par[x] = y;
            size[y] += size[x];
        } else {
            par[y] = x;
            size[x] += size[y];
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
        }
    }

    // 同じ集合に属するか判定
    bool is_same(int a, int b) {
        return find(a) == find(b);
    }

    // あるノードの属する集合のノード数
    int get_size(int x) {
        return size[find(x)];
    }

    // 集合の数
    int get_size() {
        return groupcnt;
    }

    // 木かどうかの判定
    bool is_tree(int x) {
        return tree[find(x)];
    }

    // 全ての根を取得
    set<int> get_roots() {
        set<int> res;
        rep(i, 0, n) {
            res.insert(find(i));
        }
        return res;
    }
};

pll itoedge(ll i, ll N) {
    return divmod(i, N);
}

ll edgetoi (ll u, ll v, ll N) {
    return u*N+v;
}

void solve() {
    ll N = 4, M;
    cin >> M;
    auto cnt = list2d(N, N, 0LL);
    auto sm = list2d(N, N, 0LL);
    auto mn = list2d(N, N, INF);
    rep(i, M) {
        ll c1, v, c2;
        cin >> c1 >> v >> c2;
        if (c1 > c2) swap(c1, c2);
        c1--; c2--;
        cnt[c1][c2]++;
        cnt[c2][c1]++;
        sm[c1][c2] += v;
        chmin(mn[c1][c2], v);
    }

    ll NN = N*N;
    ll ans = 0;
    // 1本減らす辺の集合を全探索する
    rep(bit, 1<<NN) {
        bool ok = 1;
        // 辺を減らしたグラフの構築
        rep(i, NN) {
            if (bit>>i & 1) {
                auto [u, v] = itoedge(i, N);
                if (u >= v) continue;
                // ない辺を消そうとしたらNG
                if (!cnt[u][v]) ok = 0;
                cnt[u][v]--;
                cnt[v][u]--;
                sm[u][v] -= mn[u][v];
            }
        }

        if (ok) {
            // 今使える辺でグラフを連結させる
            UnionFind uf(N);
            rep(i, N) {
                rep(j, i, N) {
                    if (cnt[i][j] > 0) {
                        uf.merge(i, j);
                    }
                }
            }
            // 連結成分毎に総和を集める
            vector<ll> groupsm(N);
            rep(i, N) {
                rep(j, i, N) {
                    if (cnt[i][j] > 0) {
                        groupsm[uf.find(i)] += sm[i][j];
                    }
                }
            }

            // 各連結成分でオイラー路の条件を満たしているか判定する
            vector<ll> oddcnt(N);
            rep(i, N) {
                ll edgecnt = 0;
                rep(j, N) {
                    // 自己ループは無視
                    if (i == j) continue;
                    edgecnt += cnt[i][j];
                }
                if (edgecnt%2 == 1) {
                    oddcnt[uf.find(i)]++;
                }
            }
            rep(i, N) {
                // 次数が奇数になる頂点が0か2ならOK
                if (oddcnt[uf.find(i)] == 0 or oddcnt[uf.find(i)] == 2) {
                    chmax(ans, groupsm[uf.find(i)]);
                }
            }
        }

        // 状態を元に戻す
        rep(i, NN) {
            if (bit>>i & 1) {
                auto [u, v] = itoedge(i, N);
                if (u >= v) continue;
                cnt[u][v]++;
                cnt[v][u]++;
                sm[u][v] += mn[u][v];
            }
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
