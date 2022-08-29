/**
 * 参考：https://atcoder.jp/contests/past202012-open/editorial
 * ・グラフ、平方分割
 * ・最近これをyukico1331で習った時に、この問題に使えるんじゃあ、って思ってやってみた。
 * 　実際その方針でよかったんだけど、さすがに20万のN√NにさらにBITのlogまで乗ってTLE。。
 * 　加算の処理を線形にできなかったんだけど、prevみたいなの持てばいいだけだったね。。
 * ・実装としては、添字がグラフの頂点番号と√したやつので混在するからややこしめ。
 * 　終わってから気付いたけど、HLDにセグ木乗せる時みたいに、
 * 　グラフの番号をu,v,w、√の方をi,j,kみたいに住み分ければもうちょいやりやすかったかもな。。
 * ・解説を参考に、BIT外してprv配列に変えたら無事AC。
 * 　ついでに添字も整理。やっぱ番号が混在する時はグラフはu,vとかで統一した方が見やすいね。
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

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;
    vvl nodes(N);
    rep(i, 0, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].pb(v);
        nodes[v].pb(u);
    }

    ll D = ceil(sqrt(M));
    vector<ll> nodetod(N, -1);
    vector<vector<bool>> nodetocnt;
    ll i = 0;
    rep(u, 0, N) {
        ll sz = nodes[u].size();
        if (sz >= D) {
            nodetod[u] = i;
            i++;
            vector<bool> tmp(N);
            rep(v, 0, sz) {
                tmp[nodes[u][v]] = 1;
            }
            nodetocnt.pb(tmp);
        }
    }
    ll L = i;

    ll Q;
    cin >> Q;
    vector<ll> unread(N);
    vector<ll> cnt(L);
    auto prv = list2d(L, N, 0);
    rep(_, 0, Q) {
        ll t, x;
        cin >> t >> x;
        x--;
        if (t == 1) {
            if (nodetod[x] != -1) {
                ll i = nodetod[x];
                cnt[i]++;
            } else {
                for (ll v : nodes[x]) {
                    unread[v]++;
                }
            }
        } else {
            rep(i, 0, L) {
                if (nodetocnt[i][x]) {
                    unread[x] += cnt[i]-prv[i][x];
                    prv[i][x] = cnt[i];
                }
            }
            print(unread[x]);
            unread[x] = 0;
        }
    }
    return 0;
}
