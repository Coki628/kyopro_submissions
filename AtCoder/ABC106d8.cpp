/**
 * ・E8さん精選100+50問埋め：累積和
 * ・全然違う話だけど、別解で通せた！
 * ・Mo's algorithm、bitset高速化
 * ・想定解の2次元累積和にl,rをプロットするやつは覚えてたけど、その考察は思いつきにくくて
 * 　類題が出ても気付けるか自信がなかったので、別解で通せないかやってみた。
 * ・ある区間のl,r両方が現在の区間に含まれる必要があるので、
 * 　bit1[i] := 左端が現在含まれているか
 * 　bit2[i] := 右端が現在含まれているか
 * 　bit3[i] := 両端が現在含まれているか
 * 　を管理しながら区間をMoで伸縮させていく。
 * ・あと、クエリは半開区間で与えるんだけど、右端が入る時の処理とかあるので、
 * 　伸縮時の更新は閉区間でやる感じになるので、添字バグ注意。
 * 　それと左端のbitは最初から全埋めしておくのを忘れずに。
 * ・最初BITでやってたらさすがにlog乗るのきつくて3秒でもTLE。
 * 　bitsetでも同じ感じにできると気付いてやってみると、こっちは無事AC！1.23秒。
 * ・両端が現在含まれているか、はbit1&bit2ってやっても分かるのでそっちでやってみた。
 * 　ちょっと遅くなったけど問題なくAC1.33秒。
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
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for(ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for(ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for(ll i = a, _bb = b; (a <= i && i < _bb) or (a >= i && i > _bb); i += c)
#define pb push_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define elif else if
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

vector<ll> LIST(ll N) { vector<ll> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
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
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename T> unordered_map<T, ll> Counter(vector<T> &A) { unordered_map<T, ll> res; for (T a : A) res[a]++; return res; }
unordered_map<char, ll> Counter(string &S) { unordered_map<char, ll> res; for (char c : S) res[c]++; return res; }

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
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
};
using mint = ModInt<MOD>;

struct Mo {
    int n;
    vector< pair< int, int > > lr;

    explicit Mo(int n) : n(n) {}

    // クエリを半開区間[l,r)で順番に追加
    void add(int l, int r) {
        lr.emplace_back(l, r);
    }

    template< typename AL, typename AR, typename EL, typename ER, typename O >
    void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
        int q = (int) lr.size();
        int bs = n / min< int >(n, sqrt(q));
        vector< int > ord(q);
        iota(begin(ord), end(ord), 0);
        sort(begin(ord), end(ord), [&](int a, int b) {
            int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
            if(ablock != bblock) return ablock < bblock;
            return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
        });
        int l = 0, r = 0;
        for(auto idx : ord) {
            while(l > lr[idx].first) add_left(--l);
            while(r < lr[idx].second) add_right(r++);
            while(l < lr[idx].first) erase_left(l++);
            while(r > lr[idx].second) erase_right(--r);
            out(idx);
        }
    }

    // add:   区間が伸びる時の処理(引数はmoのindex)
    // erase: 区間が縮む時の処理(引数はmoのindex)
    // out:   クエリに回答する処理(引数はクエリのindex)
    // 伸縮時に左右で処理に違いがなければadd,eraseは1つずつでOK
    template< typename A, typename E, typename O >
    void build(const A &add, const E &erase, const O &out) {
        build(add, add, erase, erase, out);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M, Q;
    cin >> N >> M >> Q;
    vvl adjl(N+1), adjr(N+1);
    rep(i, M) {
        ll l, r;
        cin >> l >> r;
        l--; r--;
        adjl[l].pb(i);
        adjr[r].pb(i);
    }
    Mo mo(N+1);
    rep(i, Q) {
        ll p, q;
        cin >> p >> q;
        p--;
        mo.add(p, q);
    }

    bitset<200007> bit1, bit2;
    rep(i, M) bit1.set(i);
    auto add_left = [&](ll i) {
        for (ll j : adjl[i]) {
            bit1.set(j);
        }
    };
    auto add_right = [&](ll i) {
        for (ll j : adjr[i]) {
            bit2.set(j);
        }
    };
    auto erase_left = [&](ll i) {
        for (ll j : adjl[i]) {
            bit1.reset(j);
        }
    };
    auto erase_right = [&](ll i) {
        for (ll j : adjr[i]) {
            bit2.reset(j);
        }
    };
    vector<ll> ans(Q);
    auto out = [&](ll i) {
        ans[i] = (bit1&bit2).count();
    };
    mo.build(add_left, add_right, erase_left, erase_right, out);
    for (ll a : ans) print(a);
    return 0;
}
