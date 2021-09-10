/*
参考：https://twitter.com/e869120/status/1393753066331992065/photo/1
　　　https://twitter.com/e869120/status/1393753066331992065/photo/3
・E8さん典型90問埋め
・幾何、凸包、新履修：ピックの定理
・最近こどふぉでも類題出たし、重い腰上げて幾何問の履修。
・凸包はPython時代に書いたやつ写経してきた。
・ピックの定理は新しく履修だね。多角形の面積と辺上の格子点数が分かると、
　内部の点数も分かるというもの。で、凸包が作ってあれば、外周を辿ることはできるので、
　線分の外積の和/2で面積が求まって、2点間のマンハッタン距離xyみたいなやつのgcd取ると
　線上にある格子点数もわかる。格子点ってようは2値が整数で重なる場所なので、
　gcdで求まるのなるほどー、って感じ。
・最初素直に組んだらWAが出て、誤差ゲーが始まったのかと思ったら意外とそうでもなくて、
　結局同じWAが出てる人の提出見たんだけど、ソート条件にxしか使ってないのが原因だった。
　確かにyの並び無視してたら、x座標が全部同じみたいな時に訪問順ぐちゃぐちゃになって壊れそう。
　2番目の条件としてyも並べるようにしたら無事AC。
・確かに今回誤差はあんま出なそうなんだよね。計算だいたい掛け算だし、
　少数出るの多分面積とピックの定理でそれぞれ/2してるとこだけだと思うんだよね。
　まあそれなら式変形して整数でやれって話ではあるんだけどね。。
　(だいたいみんなそうしてそうだった。)
・ちょっと整理した。あと幾何ライブラリを整数でも使えるように調整した。
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

template<typename T>
struct Point {
    T x, y;
    Point () {}
    Point(T x, T y) : x(x), y(y) {}
    Point operator+(const Point &p) { return {x+p.x, y+p.y}; }
    Point operator-(const Point &p) { return {x-p.x, y-p.y}; }
    Point operator*(const Point &p) { return {x*p.x, y*p.y}; }
    Point operator/(const Point &p) { return {x/p.x, y/p.y}; }
    Point operator*(T k) { return {x*k, y*k}; }
    Point operator/(T k) { return {x/k, y/k}; }
    T norm(const Point &p) { return p.x*p.x + p.y*p.y; }
    T abs(const Point &p) { return hypot(x-p.x, y-p.y); }
    T manhattan(const Point &p) { return std::abs(x-p.x) + std::abs(y-p.y); }
};
template<typename T> struct Segment { Point<T> p1, p2; };
#define Line Segment
template<typename T>
struct Circle {
    Point<T> c;
    ld r;
    Circle(Point<T> c, ld r=0.0) : c(c), r(r) {}
};
// 内積
template<typename T> T dot(const Point<T> a, const Point<T> b) { return a.x*b.x + a.y*b.y; }
// 外積
template<typename T> T cross(const Point<T> a, const Point<T> b) { return a.x*b.y - a.y*b.x; }

// 線分p0,p1から線分p0,p2への回転方向
template<typename T>
ll ccw(Point<T> p0, Point<T> p1, Point<T> p2) {
    Point<T> a = p1-p0;
    Point<T> b = p2-p0;
    // 反時計回り
    if (cross(a, b) > EPS) return 1;
    // 時計回り
    if (cross(a, b) < -EPS) return -1;
    // 直線上(p2 => p0 => p1)
    if (dot(a, b) < -EPS) return 2;
    // 直線上(p0 => p1 => p2)
    if (a.norm(a) < b.norm(b)) return -2;
    // 直線上(p0 => p2 => p1)
    return 0;
}

// ピックの定理(多角形の座標から、内部にある格子点の数を出す)
tuple<ll, ll, ll> pick_theorem(vector<Point<ll>> P) {
    ll N = P.size();
    ll S = 0;
    ll b = 0;
    rep(i, N) {
        S += cross(P[i], P[(i+1)%N]);
        auto a = P[i]-P[(i+1)%N];
        b += gcd(abs(a.x), abs(a.y));
    }
    ll i = (abs(S)-b+2)/2;
    // 内部にある格子点の数, 辺上の格子点の数, 面積
    return {i, b, abs(S)};
}

// アンドリューのアルゴリズム(Monotone Chain)：凸包に使った座標と距離を返す
template<typename T>
vector<pair<Point<T>, ld>> monotone_chain(vector<Point<T>> li) {
    int N = li.size();
    assert(N >= 2);

    sort(ALL(li), [](Point<T> a, Point<T> b) {
        // ソート条件にyも使う
        if (a.x == b.x) return a.y < b.y;
        else return a.x < b.x; 
    });

    // 上半分
    // 使う座標と距離を保持
    vector<pair<Point<T>, ld>> stack;
    stack.pb({li[0], 0});
    stack.pb({li[1], li[0].abs(li[1])});
    rep(i, 2, N) {
        // 1つ前->次 と 1つ前->2つ前 のベクトルで外積をチェックして向きを判定する
        while (stack.size() >= 2 and ccw(stack[stack.size()-2].first, stack[stack.size()-1].first, li[i]) == 1) {
            // 次が反時計回り側にある時は1つ前を外す
            stack.pop_back();
        }
        // 次が時計回り側にあればOKなので進める
        stack.pb({li[i], stack.back().first.abs(li[i])});
    }
    vector<pair<Point<T>, ld>> res;
    rep(i, 1, stack.size()) {
        res.pb(stack[i]);
    }

    // 下半分(やることは同じ)
    stack.clear();
    stack.pb({li[li.size()-1], 0});
    stack.pb({li[li.size()-2], li[li.size()-1].abs(li[li.size()-2])});
    rrep(i, N-3, -1) {
        while (stack.size() >= 2 and ccw(stack[stack.size()-2].first, stack[stack.size()-1].first, li[i]) == 1) {
            stack.pop_back();
        }
        stack.pb({li[i], stack.back().first.abs(li[i])});
    }
    rep(i, 1, stack.size()) {
        res.pb(stack[i]);
    }
    return res;
}

void solve() {
    ll N;
    cin >> N;
    vector<Point<ll>> li;
    rep(i, N) {
        ld x, y;
        cin >> x >> y;
        li.pb({x, y});
    }

    auto res = monotone_chain(li);
    auto [li2, _] = zip(res); 
    auto [i, b, S] = pick_theorem(li2);

    ll ans = b+i-N;
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
