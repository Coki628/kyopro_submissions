/**
 * 参考：http://www.utpc.jp/2013/slides/E.pdf
 * 　　　https://atcoder.jp/contests/utpc2013/submissions/16477228
 * ・蟻本演習4-5-1
 * ・自力ならず。探索ってヒントあっても全然方針出なかった。。
 * ・再帰探索、枝刈り、バックトラック、構文解析
 * ・条件が(false, false)になってしまっているところはどちらかをtrueにする必要がある。
 * 　これは両方を試していい。それでも計算量は2^10*10万=約1億くらいで済む。
 * ・公式解説の方針から、ここまで進めるもTLEが取れない。。
 * 　やむなく人様のコードと比較してみると、探索した後、その回をbreakしてる。
 * ・全箇所から試さないといけない気になってたけど、今回、true/falseを切り替える順番は
 * 　結果に影響しないはずなので、1つ切り替えを試したら、それ以外の場所は
 * 　そこを切り替えた後の状態からのみ確認すればいい。考えてみればそれはそう。。
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    ll L = S.size();
    string T;
    cin >> T;
    vector<bool> A(N, false);
    rep(i, 0, N) {
        if (T[i] == 'T') A[i] = true;
    }

    // 構文解析パート、再帰やる前に初期状態を確認しておく
    vector<pair<pair<bool, int>, pair<bool, int>>> cnf(M);
    ll i = 0, j = 0;
    bool rev = false;
    while (i < L) {
        i++;
        if (S[i] == '~') {
            rev = true;
            i++;
        } else {
            rev = false;
        }
        string cnt = "";
        while (digits.find(S[i]) != -1) {
            cnt += S[i];
            i++;
        }
        ll v = toint(cnt) - 1;
        cnf[j].first = {rev, v};
        i++;
        if (S[i] == '~') {
            rev = true;
            i++;
        } else {
            rev = false;
        }
        cnt = "";
        while (digits.find(S[i]) != -1) {
            cnt += S[i];
            i++;
        }
        v = toint(cnt) - 1;
        cnf[j].second = {rev, v};
        j++;
        i += 2;
    }

    auto rec = [&](auto&& f, int depth) -> ll {
        if (depth > 10) return INF;

        ll res = INF;
        bool good = true;
        rep(i, 0, M) {
            auto [revu, u] = cnf[i].first;
            auto [revv, v] = cnf[i].second;
            bool a = A[u]-revu;
            bool b = A[v]-revv;
            if (!a and !b) {
                good = false;
                A[u] = 1 - A[u];
                chmin(res, f(f, depth+1));
                A[u] = 1 - A[u];
                A[v] = 1 - A[v];
                chmin(res, f(f, depth+1));
                A[v] = 1 - A[v];
                // ここでこの回の探索を打ち切る必要がある
                break;
            }
        }
        if (good) res = depth;
        return res;
    };
    ll res = rec(rec, 0);
    if (res == INF) {
        print("TOO LARGE");
    } else {
        print(res);
    }
    return 0;
}
