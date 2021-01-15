/**
 * 参考：https://yukicoder.me/problems/no/1340/editorial
 * ・行列累乗、グラフ
 * ・edpc_rみたいに、グラフの隣接行列を行列累乗に乗せるやつ。
 * ・基本的にそっちとやり方は同じだけど、普通のグラフの隣接行列とは行列逆向きにする。
 * 　これは行列の遷移の向きを考えると確かにそう。貰う側の頂点が1次元側に来ないとおかしいもんね。
 * ・あと、1000000007キラーっぽいケースが追加されてたみたいなので、1000000009でやったら通った。
 * 　本当は複数MODでやってどちらか満たしてたらOK、みたいにすると確実みたいだね。
 * ・ACだけど1.87秒もかかってる。計算量N^3logTは100万*60くらいはあるけど、
 * 　それにしてもC++でこれは明らかに遅いので、何かボトルネックがありそう。。
 * ・分かった。MODをクラスに入れちゃうと遅い。グローバルでconstexprで持ったまま使えば速い。
 * 　AC1.87秒→0.36秒。あと、1000000009もキラーケース入ったみたいで998244353にした。
 * 　MODグローバルのがいいみたいな話は聞いたことあったけど、こんなに変わるんだな。。
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
constexpr ll MOD = 998244353;

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

// 行列累乗
template<typename T>
struct MatPow {

    MatPow() {}

    vector<vector<T>> mat_dot(vector<vector<T>> &A, vector<vector<T>> &B) {
        int n1 = A.size();
        int n2 = A[0].size();
        int m2 = B[0].size();
        auto res = list2d(n1, m2, (T)0);
        rep(i, 0, n1) {
            rep(j, 0, m2) {
                rep(k, 0, n2) {
                    res[i][j] = (res[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
                }
            }
        }
        return res;
    }
    
    vector<vector<T>> mat_pow(vector<vector<T>> mat, ll k) {
        int n = mat.size();
        auto res = list2d(n, n, (T)0);
        rep(i, 0, n) {
            res[i][i] = 1;
        }
        while (k > 0) {
            if (k & 1) {
                res = mat_dot(res, mat);
            }
            mat = mat_dot(mat, mat);
            k >>= 1;
        }
        return res;
    }

    vector<T> solve(vector<vector<T>> mat, vector<T> &_init, ll K) {
        int n = mat.size();
        auto init = list2d(n, 1, (T)0);
        rep(i, 0, n) init[i][0] = _init[i];
        auto res = mat_pow(mat, K);
        res = mat_dot(res, init);
        vector<T> ret(n, 0);
        rep(i, 0, n) {
            ret[i] = res[i][0];
        }
        return ret;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M, T;
    cin >> N >> M >> T;
    auto G = list2d(N, N, 0LL);
    rep(i, 0, M) {
        ll u, v;
        cin >> u >> v;
        // いつもの隣接行列と逆向き
        G[v][u] = 1;
    }

    // init[i] := 出発前に頂点iにいる通り数
    vector<ll> init(N);
    init[0] = 1;
    MatPow<ll> mp;
    // res[i] := T回移動後に頂点iにいる通り数
    auto res = mp.solve(G, init, T);
    ll ans = 0;
    rep(i, 0, N) {
        if (res[i]) ans++;
    }
    print(ans);
    return 0;
}
