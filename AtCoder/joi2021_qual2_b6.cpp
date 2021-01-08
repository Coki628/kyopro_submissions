/**
 * 参考：https://www.ioi-jp.org/joi/2020/2021-yo2/2021-yo2-t2-review.pdf
 * 　　　https://atcoder.jp/contests/joi2021yo2/submissions/18984869
 * ・クエリ毎に色々な文字列が来るが、それらはいずれかのソート済状態を終点とする。
 * 　逆操作で同じ終点に向かう全ての状態を一度に網羅すれば、状態数よりも多く探索しなくて済む。
 * 　状態は最大でも3^13=160万くらいなので間に合う。
 * ・でもこれでもTLE。。結局、mapとstringのキーがボトルネックで、
 * 　ABCを3進数エンコードしてやらないと間に合わないみたい。。
 * ・mapのキーを文字列からエンコードしてintにした。これでAC、2.26秒。(制約2.5秒)
 * ・キーintにするならそもそもmapじゃなくていいよね、ってことで生配列にした。AC0.74秒。やっぱ全然速い。
 * ・3進数変換パートを、自分のやつ移植してきた。こっちのが遅いけどね。。
 * 　あと、inlineにしたらやたら速くなることがあった。変えても変わらないとこもある。分からん。。
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

ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

// N進数文字列Sを10進数に
ll ntod(string S, ll n) {
    ll res = 0, k = 1;
    reverse(ALL(S));
    for (char &c : S) {
        res += k*toint(c);
        k *= n;
    }
    return res;
}

// 10進数をN進数文字列に(負数対応版)
string dton(ll num, ll n) {
    string res;
    while (abs(num) > 0) {
        ll m = num % abs(n);
        num -= m;
        res += tochar(m);
        num /= n;
    }
    reverse(ALL(res));
    if (res != "") {
        return res;
    } else {
        return "0";
    }
}

int dist[2000007];
int N;

int to_int(string s) {
    // 'A' to '0'
    rep(i, 0, s.size()) s[i] -= 17;
    return ntod(s, 3);
}

string to_str(int a) {
    auto res = dton(a, 3);
    // 0埋め
    if (res.size() < N) res = string(N-res.size(), '0')+res;
    // '0' to 'A'
    rep(i, 0, res.size()) res[i] += 17;
    return res;
}

void bfs(string &S) {

    queue<int> que;
    dist[to_int(S)] = 0;
    que.push(to_int(S));
    while(!que.empty()) {
        int s = que.front(); que.pop();
        string t = to_str(s);
        rep(i, 2, N+1) {
            reverse(t.begin(), t.begin()+i);
            if (dist[to_int(t)] == -1) {
                dist[to_int(t)] = dist[s]+1;
                que.push(to_int(t));
            }
            reverse(t.begin(), t.begin()+i);
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int Q;
    cin >> N >> Q;

    memset(dist, -1, sizeof(dist));
    rep(i, 0, Q) {
        string S;
        cin >> S;

        if (dist[to_int(S)] == -1) {
            string T = S;
            sort(ALL(T));
            bfs(T);
        }
        print(dist[to_int(S)]);
    }
    return 0;
}
