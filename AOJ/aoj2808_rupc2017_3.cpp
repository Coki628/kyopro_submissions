/**
 * 参考：https://drive.google.com/drive/folders/0ByodiIJxyvTYZTQ1TmZNS2s1Y2M
 * ・蟻本演習4-7-3
 * ・文字列検索、ローリングハッシュ
 * ・いやー、ロリハ使うって分かってても自力解けなかった。考察力さん。。
 * ・とりあえず、あまり多い文字数にしなくて答えが出そうなのは分かった。
 * 　なのでaから順に見ていって、全単語に含まれなかったところで答え。この方針自体は合ってる。
 * 　でも毎回のチェックで全単語のループ回して全部分と一致チェックしてた。これじゃ無理。
 * ・全単語の部分文字列は前計算しておける。
 * 　合計40万文字もあるやつを、全てのl,rでN^2無理ー、ってこれは自分の中で却下してたんだけど、
 * 　よくよく考えると、答えになる文字数が多くないってことは、その文字数くらいまでの長さの
 * 　部分文字列だけ取っておけばいい。40万は26^4より小さく、これなら4文字でいい。
 * 　4文字以内の部分文字列であれば、40万に乗るのは定数程度と見ていいので大丈夫。
 * 　これで全部setに詰めておけるので、答え候補の文字列との照合は各回logくらいで済む。
 * ・あと地味に、a~z,aa,ab,ac..az,ba,bb..zz,aaa..みたいなのをやるのに悩んだ。
 * 　26進数からエンコードするとzの次がbaになってしまうので、aの1つ手前から使うことにして、
 * 　そいつが混ざってたら空文字に置き換え、ってやって、まあうまくいった。
 * 　C++のreplace関数がゴミっぽかったのでpythonぽいやつを拾ってきた。。
 * ・ていうか、切り出す文字列長が最大4ならもはやロリハいらなくない？
 * 　となり、stringのまま切り出してsetに詰めてみたところ、これでも問題なくAC。。
 * 　速度もちょい遅くなったけど0.19秒→0.36秒で、まあ問題にはならない。
 * ・全列挙も直した。ちょっと人様の参考にしたけど、
 * 　そうだよね、こういう全列挙は再帰でやれば楽だよね。。
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    set<string> se;
    rep(_, 0, N) {
        string s;
        cin >> s;
        rep(d, 1, 5) {
            if (s.size() < d) break;
            rep(i, 0, s.size()-d+1) {
                se.insert(s.substr(i, d));
            }
        }
    }

    rep(n, 1, 5) {
        vector<string> v;
        auto rec = [&](auto&& f, string cur, ll i) {
            if (i == n) {
                v.pb(cur);
                return;
            }
            for (char c : ascii_lowercase) {
                f(f, cur+c, i+1);
            }
        };
        rec(rec, "", 0);
        for (auto s : v) {
            if (!se.count(s)) {
                print(s);
                return 0;
            }
        }
    }
    return 0;
}
