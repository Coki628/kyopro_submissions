/**
 * ・蟻本演習4-6-2
 * ・自力AC！
 * ・重み付きUnionFind
 * ・マージテクの紹介で載ってたけど、実際は「重み付きUFを知っていますか？」だった。
 * 　まあやるだけ系だけれども、久々に使う論点にすぐ気付けたのでよかった。
 * ・C++移植してVerifyがてら無事AC。
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

// 重み付きUnion-Find
template<typename T>
struct WeightedUnionFind {

    int n;
    vector<int> par, rank;
    vector<T> weight;
    
    WeightedUnionFind(int n) : n(n) {
        par.resize(n);
        rank.resize(n);
        // 根への距離を管理
        weight.resize(n);
        rep(i, 0, n) par[i] = i;
    }

    // 検索
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            int y = find(par[x]);
            // 親への重みを追加しながら根まで走査
            weight[x] += weight[par[x]];
            par[x] = y;
            return y;
        }
    }

    // 併合
    void merge(int x, int y, ll w) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;

        // xの木の高さ < yの木の高さ
        if (rank[rx] < rank[ry]) {
            par[rx] = ry;
            weight[rx] = w - weight[x] + weight[y];
        } else {
            par[ry] = rx;
            weight[ry] = - w - weight[y] + weight[x];
            // 木の高さが同じだった場合の処理
            if (rank[rx] == rank[ry]) {
                rank[rx]++;
            }
        }
    }

    // 同じ集合に属するか
    bool is_same(int x, int y) {
        return find(x) == find(y);
    }

    // xからyへのコスト
    T diff(int x, int y) {
        return weight[x] - weight[y];
    }
};


int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    while (1) {
        ll N, M;
        cin >> N >> M;
        if (N == 0) break;
        WeightedUnionFind<ll> uf(N);

        rep(_, 0, M) {
            char op;
            ll a, b, w;
            cin >> op;
            if (op == '!') {
                cin >> a >> b >> w;
                a--; b--;
                uf.merge(a, b, w);
            } else {
                cin >> a >> b;
                a--; b--;
                if (uf.is_same(a, b)) {
                    ll res = uf.diff(a, b);
                    print(res);
                } else {
                    print("UNKNOWN");
                }
            }
        }
    }
    return 0;
}
