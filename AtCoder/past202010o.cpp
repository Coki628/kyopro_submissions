/*
・PAST未ACのupsolve
・時間かかったけど自力AC！嬉しい。
・DP高速化、平方分割
・なかなか方針が定まらなかったけど、手前の宝箱から開けたかどうかの状態を
　区切るDPみたいに確定させていくとすると、何とか筋道が見えてきた。
　鍵屋の区間は右端を軸にして、その鍵屋を使う時は右端までの遷移をしてくるようにする。
　区間が被る問題は、左端から右端までの遷移を全部見ていけば解消できる。
　これでN^2のDPは作れたので、区間遷移の高速化について検討していく。
・max(dp[l]+acc.query(l, r)) みたいな遷移を何回もやるので、これをまとめる。
　平方分割で√毎に上記の最大値を取っておいて、長い区間を見る時は、左右の端は愚直に、
　√の区間を全部含む範囲についてはそっちのバケットから最大値を取るようにする。
　√の区切りのいい所までDPが進んだら、そこまでの分のバケットをまた前計算する、
　といった具合で進めていく。
・結果的にはこれで問題なかったのだが、色々バグらせてて一筋縄ではいかなかった。
　・直前からの無条件遷移
　・バケットで持ってる範囲より右は別途累積和から持ってくる
　・狭い区間の扱い
　この辺のことはソース内コメントにも入れておく。
　あと添字が普通のNまでのindexとDまでのやつで行き来するのでかなり気を遣うが、
　そこを気を付けてたからかほぼバグらせずに仕上げることができてた。
・20万のNに対してO(N√N)だけどかなり速くて、AC0.39秒。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for(ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for(ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for(ll i = a, _bb = b; (c > 0 && a <= i && i < _bb) or (c < 0 && a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr ld EPS = 1e-10;
constexpr ld PI = M_PI;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(deque<T> A) { rep(i, 0, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> &A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(int x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
int bit_length(ll x) { return x != 0 ? floor(log2(x))+1 : 0; }
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if(res == "") res += '0'; return res; }

ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

ld degrees(ld radians) { return radians * 180.0 / PI; }
ld radians(ld degrees) { return degrees * PI / 180.0; }

template<typename T> int bisect_left(vector<T> &A, T val, int lo=0) { return lower_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val, int lo=0) { return upper_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }

template<typename T> map<T, ll> Counter(vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
map<char, ll> Counter(string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }

template<typename T> struct Accumulate {
    vector<T> acc; int N;
    Accumulate() {}
    Accumulate(int N) : N(N) { acc.resize(N); }
    Accumulate(vector<T> &A) { N = A.size(); acc = A; build(); }
    void set(int i, T a) { acc[i] = a; }
    void build() { rep(i, N-1) acc[i+1] += acc[i]; acc.insert(acc.begin(), 0); }
    T query(int l, int r) { assert(0 <= l and l <= N and 0 <= r and r <= N); return acc[r]-acc[l]; }
    T get(int i) { return query(i, i+1); }
    T operator[](int i) { return query(i, i+1); }
};

template<int mod> struct ModInt {
    int x;
    ModInt() : x(0) {}
    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; }
    ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; }
    ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; }
    ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; }
    ModInt operator-() const { return ModInt(-x); }
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    bool operator==(const ModInt &p) const { return x == p.x; }
    bool operator!=(const ModInt &p) const { return x != p.x; }
    bool operator<(const ModInt &p) const { return x < p.x; }
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    vector<vector<pll>> adj(N+1);
    vector<tuple<ll, ll, ll>> LRC;
    rep(i, M) {
        ll l, r, c;
        cin >> l >> r >> c;
        l--;
        adj[r].pb({l, c});
        LRC.pb({l, r, c});
    }

    // ll ans = 0;
    // rep(bit, 1<<M) {
    //     vector<bool> covered(N);
    //     ll cur = 0;
    //     vector<ll> B;
    //     rep(i, M) {
    //         if (bit>>i & 1) {
    //             B.pb(i);
    //             auto [l, r, c] = LRC[i];
    //             rep(j, l, r) {
    //                 covered[j] = 1;
    //             }
    //             cur -= c;
    //         }
    //     }
    //     rep(i, N) {
    //         if (covered[i]) {
    //             cur += A[i];
    //         }
    //     }
    //     if (cur > ans) {
    //         ans = cur;
    //     }
    // }

    ll D = ceil(sqrt(N));
    vector<ll> bucket(D);
    Accumulate<ll> acc(A);
    vector<ll> dp(N+1);
    dp[0] = 0;
    rep(r, 1, N+1) {
        // D区切りまで進んだら、バケットに最大値をまとめておく
        if (r%D == 0) {
            ll rd = r/D;
            ll ld = r/D-1;
            ll l = ld*D;
            rep(m, l, r) {
                chmax(bucket[ld], dp[m]+acc.query(m, r));
            }
        }
        // 直前からの無条件遷移(最初これも抜けてた)
        chmax(dp[r], dp[r-1]);
        for (auto [l, c] : adj[r]) {
            // rep(m, l, r) {
            //     chmax(dp[r], dp[m]+acc.query(m, r)-c);
            // }
            ll ld = l/D+1;
            ll rd = r/D;
            // 狭い区間で ld*D > r が発生するのでrとmin取る
            rep(m, l, min(ld*D, r)) {
                chmax(dp[r], dp[m]+acc.query(m, r)-c);
            }
            rep(md, ld, rd) {
                // バケットで持ってる範囲より右は別途累積和から持ってくる
                ll m = (md+1)*D;
                chmax(dp[r], bucket[md]+acc.query(m, r)-c);
            }
            // 左端と同様にここも rd*D < l を考慮する
            rep(m, max(rd*D, l), r) {
                chmax(dp[r], dp[m]+acc.query(m, r)-c);
            }
        }
    }
    ll ans = dp[N];
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
