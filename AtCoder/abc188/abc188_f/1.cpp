/**
 * ・自力ならず。。
 * ・整数ダイクストラ
 * ・AGC044aとほぼ同じ方針で解ける。ちょっと弱体化した感じ。あっちは解けたのにどうして。。。
 * ・似てるのは思い出したから、ちらっとコード見に行ったのにな。もっとちゃんとよく確認しに行くんだった。
 * ・BFSでやってたのをダイクストラにして、+-1のところは、+-1して/2するのを、コスト2で追加する。
 * 　そして毎回の操作前に、そこから全部+-だけで行った場合の到達コストをチェックする。
 * ・全部AGC044aから適切に取ってくれば通った。これは通したかったな。。。
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

    ll x, y;
    cin >> x >> y;

    if (x > y) {
        print(x-y);
        return 0;
    }

    priority_queue<pll, vector<pll>, greater<pll>> que;
    unordered_map<ll, ll> dist;
    dist[y] = 0;
    que.push({0, y});
    while (!que.empty()) {
        auto [cost, cur] = que.top(); que.pop();
        // 全部+-だけで行った場合の到達コストをチェック
        if (!dist.count(x) or dist[x] > cost+abs(x-cur)) {
            dist[x] = cost+abs(x-cur);
        }
        if (cur >= x+2) {
            if (cur % 2 == 0) {
                // 割る2する場合の遷移
                ll nxt = cur/2;
                if (!dist.count(nxt) or dist[nxt] > cost+1) {
                    dist[nxt] = cost+1;
                    que.push({cost+1, nxt});
                }
            } else {
                // -1して割る2、+1して割る2する場合の遷移
                ll nxt = (cur-1)/2;
                if (!dist.count(nxt) or dist[nxt] > cost+2) {
                    dist[nxt] = cost+2;
                    que.push({cost+2, nxt});
                }
                nxt = (cur+1)/2;
                if (!dist.count(nxt) or dist[nxt] > cost+2) {
                    dist[nxt] = cost+2;
                    que.push({cost+2, nxt});
                }
            }
        }
    }
    ll ans = dist[x];
    print(ans);
    return 0;
}
