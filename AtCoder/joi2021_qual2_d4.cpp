/**
 * 参考：https://www.ioi-jp.org/joi/2020/2021-yo2/2021-yo2-t4-review.pdf
 * ・公式解に寄せてみた。
 * ・K人でやりきれるか、ではなく、K人に収まるか、で判定する。
 * 　まあ本質的にやってることはほぼ一緒だった。
 * ・状態まとめて進めるとことか、こっちのが簡潔にまとまるかと思ったけど案外変わらなかった。
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

template<typename F>
ll bisearch_min(ll mn, ll mx, const F &func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, K;
    cin >> N >> K;
    vector<ll> A(N), B(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];

    ll res = bisearch_min(0, INF, [&](ll m) -> bool {
        auto B2 = B;
        B2.pb(-1);
        ll i = 0, k = 0;
        pll cur = {0, B2[0]}, prv = {0, B2[0]};
        while (i < N) {
            ll t = m-A[i];
            while (i+1 < N and t > 0) {
                ll use = min(t, B2[i]);
                B2[i] -= use;
                t -= use;
                if (t > 0 and B2[i] == 0) {
                    t -= A[i+1]-A[i];
                    i++;
                }
            }
            if (t > 0) B2[i] -= min(t, B2[i]);
            if (B2[i] == 0) i++;
            cur = {i, B2[i]};
            // この人が始める前と変化がなければ即NG
            if (cur == prv) return 0;
            // 位置iに変化がないなら、ここのB[i]がなくなるまでの操作はまとめられる
            else if (cur.first == prv.first and cur.second != prv.second) {
                // 1人が減らした量
                ll work = prv.second-cur.second;
                // 残りを捌ききるのに必要な人数(余り分1人は無視)
                ll need = B2[i]/work;
                B2[i] %= work;
                k += need;
                if (B2[i] == 0) i++;
            }
            prv = cur;
            k++;
        }
        // この時間でやりきるための人数がK人以内に収まるか
        return k <= K;
    });
    print(res);
    return 0;
}
