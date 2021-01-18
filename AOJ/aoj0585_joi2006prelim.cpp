/**
 * 参考：蟻本P.324~
 * ・蟻本演習4-6-3
 * ・最近点対問題、分割統治法
 * ・こういう問題見る度に、分割統治すげーってなるけど、自力で書ける自信がない。。
 * 　今回も蟻本のページよく読み込んでから書いた。さすがに写経にはしてないけど。。
 * ・Nが50万のケースでAC2.50秒。(制約8秒)
 * 　ちょっと遅い気がするけど、引数にしてるvector毎回生成が重いのか、
 * 　蟻本とちょっとループと枝刈りが違うから甘いのか、まあこんなもんなのか。
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

    vector<pll> XY;
    rep(i, 0, N) {
        ll x, y;
        cin >> x >> y;
        XY.pb({x, y});
    }
    sort(ALL(XY));

    auto rec = [&](auto&& f, vector<pll> XY) -> ll {
        ll n = XY.size();
        if (n <= 1) return INF;
        ll m = n/2;
        // l := x軸の真ん中
        ll l = XY[m].first;
        // d := 左右の集合内での最小値
        ll d = min(f(f, vector<pll>(XY.begin(), XY.begin()+m)), 
                   f(f, vector<pll>(XY.begin()+m, XY.end())));

        // y軸でソート
        sort(ALL(XY), [](pll a, pll b) { return a.second < b.second; });
        // 左右の集合をまたぐような点対をチェックする
        rep(i, 0, n) {
            auto [x1, y1] = XY[i];
            // xが中心からd以上離れすぎていたらやらない
            if (abs(l-x1) >= d) continue;
            rep(j, i+1, n) {
                auto [x2, y2] = XY[j];
                // y軸の距離がd以上離れたら、XY[i]とのペアはこれ以上やる必要ない
                if (abs(y1-y2) >= d) break;
                chmin(d, (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
            }
        }
        return d;
    };
    ll ans = rec(rec, XY);
    print(ans);
    return 0;
}
