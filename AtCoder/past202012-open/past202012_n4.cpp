/**
 * ・クエリ系、ダブリングLCA、二分探索
 * ・C++AC2.28秒(制約4秒)。セグ木にぶたんよりは軽いと思ったんだけど、こっちのが遅かった。
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

// 条件を満たす最小値を見つける二分探索
template<typename F>
ll bisearch_min(ll mn, ll mx, const F &func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 下を探しに行く
            ok = mid;
        } else {
            // 上を探しに行く
            ng = mid;
        }
    }
    return ok;
}


// 条件を満たす最大値を見つける二分探索
template<typename F>
ll bisearch_max(ll mn, ll mx, const F &func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}

// DFS(木、スタック、重みあり) 
void dfs(ll N, vector<vector<tuple<ll, ll, ll>>> &nodes, ll src, vector<ll> &depths, vvl &nxt, vvl &L, vvl &R) {
    
    vector<tuple<ll, ll, ll, ll, ll>> stack;
    stack.pb({src, -1, 0, -1, -1});
    while (!stack.empty()) {
        auto [u, prev, depth, prevl, prevr] = stack.back(); stack.pop_back();
        depths[u] = depth;
        nxt[0][u] = prev;
        L[0][u] = prevl;
        R[0][u] = prevr;
        for (auto [v, l, r] : nodes[u]) {
            if (v != prev) {
                stack.pb({v, u, depth+1, l, r});
            }
        }
    }
}

const ll MX = 18;

pll get_mnmx(ll a, ll b, vector<ll> &depths, vvl &nxt, vvl &L, vvl &R) {
    if (depths[a] > depths[b]) {
        swap(a, b);
    }
    ll gap = depths[b] - depths[a];
    ll mx = 0;
    ll mn = INF;
    rep(i, 0, MX+1) {
        if (gap>>i & 1) {
            mx = max(mx, L[i][b]);
            mn = min(mn, R[i][b]);
            b = nxt[i][b];
        }
    }
    if (a == b) {
        return {mn, mx};
    } else {
        rrep(i, MX, -1) {
            ll a2 = nxt[i][a];
            ll b2 = nxt[i][b];
            if (a2 != b2) {
                mx = max({mx, L[i][a], L[i][b]});
                mn = min({mn, R[i][a], R[i][b]});
                a = a2;
                b = b2;
            }
        }
        if (a != b) {
            mx = max({mx, L[0][a], L[0][b]});
            mn = min({mn, R[0][a], R[0][b]});
        }
        return {mn, mx};

    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, Q;
    cin >> N >> Q;
    vector<vector<tuple<ll, ll, ll>>> nodes(N);
    rep(i, 0, N-1) {
        ll l, r;
        cin >> l >> r;
        nodes[i].pb({i+1, l, r});
        nodes[i+1].pb({i, l, r});
    }

    auto nxt = list2d(MX+1, N, -1LL);
    auto L = list2d(MX+1, N, -1LL);
    auto R = list2d(MX+1, N, -1LL);
    vector<ll> depths(N, -1);
    dfs(N, nodes, 0, depths, nxt, L, R);

    rep(k, 1, MX+1) {
        rep(v, 0, N) {
            if (nxt[k-1][v] == -1) {
                continue;
            }
            nxt[k][v] = nxt[k-1][nxt[k-1][v]];
            L[k][v] = max(L[k-1][v], L[k-1][nxt[k-1][v]]);
            R[k][v] = min(R[k-1][v], R[k-1][nxt[k-1][v]]);
        }
    }

    rep(_, 0, Q) {
        ll val, x, l, r, res;
        cin >> val >> x;
        x--;

        // Lの最大がval以下でRの最小がval以上ならその区間は通れる
        l = bisearch_min(-1, x, [&](ll m) {
            auto [mn, mx] = get_mnmx(x, m, depths, nxt, L, R);
            return mx <= val and mn >= val;
        });
        r = bisearch_max(x, N, [&](ll m) {
            auto [mn, mx] = get_mnmx(x, m, depths, nxt, L, R);
            return mx <= val and mn >= val;
        });
        res = r-l+1;
        print(res);
    }
    return 0;
}
