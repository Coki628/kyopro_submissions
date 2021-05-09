/*
参考：https://atcoder.jp/contests/arc117/editorial
　　　https://betrue12.hateblo.jp/entry/2020/02/23/173513
・自力ならず。むずいね。
・パスカルの三角形、二項係数、任意MODのnCr
・まずBWRを012にエンコードして考える。すると-(a+b)mod 3ってやると
　1段上の値を表せる。3つの値を3-(a+b)ってするのを見たことがあったので、
　3-(a+b)mod 3まではやったんだけど、2+2が2じゃなくて-1ってなるから
　ダメだぁーって却下しちゃった。。これmod 3で正負逆すれば2じゃんね。惜しかった。
・でもこの先に行けたかどうかは分からない。てか多分できなかった。
　この後最上段の値を求めるには、AGC043bっぽく、
　パスカルの三角形の考え方を適用すると、二項係数の経路のやつっぽく、
　終点に着く通り数を求める感じで元の値をいくつ掛けるかが求まる。
・ここまで出来てもまだ壁があって、mod 3の二項係数はいつものMOD逆元だと
　求まらない。逆元どころか階乗した時点で3以上になった時全部0になって破綻する。
　公式解説にもやり方が詳しく説明されていたけど、
　もっと汎用的に使えそうな部品をアルメリアさんが記事にしてくれていたので、
　今回はそれを使うことにする。
・今回の場合mod 3なのでわざわざ素因数分解全部しなくても、
　3で割れる回数だけ確認すればよさそうだが、これを使っても十分速い。AC0.08秒。
　結局、素因数の種類数がlogくらいしか(多分)ないからだろう。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
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
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 3;
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
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(deque<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

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

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }

template<typename T> map<T, ll> Counter(vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
map<char, ll> Counter(string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }

template<typename T> struct Accumulate {
    vector<T> acc; int N;
    Accumulate(vector<T> &A) { N = A.size(); acc = A; rep(i, N-1) acc[i+1] += acc[i]; acc.insert(acc.begin(), 0); }
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
    operator int() const { return x; }
};
using mint = ModInt<MOD>;

template<typename T>
vector<pair<T, int>> factorize(T n) {
    vector<pair<T, int>> ret;
    for(T i=2; i*i<=n; i++){
        int cnt = 0;
        while(n % i == 0){
            n /= i;
            cnt++;
        }
        if(cnt) ret.emplace_back(i, cnt);
    }
    if(n > 1) ret.emplace_back(n, 1);
    return ret;
}

template<typename T>
T extgcd(T a, T b, T& x, T& y) {
    T d = a;
    if(b != 0){
        d = extgcd(b, a%b, y, x);
        y -= (a/b) * x;
    }else{
        x = 1; y = 0;
    }
    return d;
}

template<typename T>
T inv_mod(T a, T mod) {
    T x, y;
    extgcd(a, mod, x, y);
    return (mod + x%mod) % mod;
}

struct AnyModTools {

    const int64_t mod;
    // 素数冪を (p, c) で表現したもの
    vector<pair<int64_t, int>> primes;
    // 素数冪 p^c の実際の値
    vector<int64_t> ppow;
    // 階乗を (x, y) 形式で表現したもの
    vector<vector<pair<int64_t, int>>> fact;

    AnyModTools(int64_t mod, int MX) : mod(mod) {
        create_composite_mod_table(++MX, mod);
    }

    void add(int64_t& a, int64_t b, int64_t mod) {
        a = (a+b) % mod;
    }
    void mul(int64_t& a, int64_t b, int64_t mod) {
        a = a*b % mod;
    }

    // 素因数分解をして素数冪ごとにfactを前計算：O(√M+N*(Mの素因数の種類数))
    void create_composite_mod_table(int N, int64_t M) {
        primes = factorize(M);
        int sz = primes.size();
        ppow.resize(sz, 1);
        fact.resize(sz);
        for(int pi=0; pi<sz; pi++){
            int64_t p = primes[pi].first, cnt = primes[pi].second;
            while(cnt--) ppow[pi] *= p;

            auto& f = fact[pi];
            f.resize(N+1);
            f[0] = {1, 0};
            for(int i=1; i<=N; i++){
                f[i] = f[i-1];
                int n = i;
                while(n%p == 0){
                    n /= p;
                    f[i].second++;
                }
                mul(f[i].first, n, ppow[pi]);
            }
        }
    }

    // 素因数毎の二項係数を計算
    int64_t comb_mod(int n, int k, int pi) {
        auto &a = fact[pi][n], &b = fact[pi][k], &c = fact[pi][n-k];
        int64_t p = primes[pi].first, cnt = primes[pi].second;
        int64_t pp = ppow[pi];
        int pw = a.second - b.second - c.second;
        if(pw >= cnt) return 0;

        int64_t v = a.first;
        mul(v, inv_mod(b.first, pp), pp);
        mul(v, inv_mod(c.first, pp), pp);
        while(pw--) mul(v, p, pp);
        return v;
    }

    // 二項係数nCrの計算：O(modの素因数の種類数)
    int64_t nCr(int n, int k) {
        int64_t res = 1;
        rep(i, primes.size()) {
            mul(res, comb_mod(n, k, i), mod);
        }
        return res;
    }
};

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    map<char, mint> mp;
    mp['B'] = 0;
    mp['W'] = 1;
    mp['R'] = 2;
    map<int, char> revmp;
    revmp[0] = 'B';
    revmp[1] = 'W';
    revmp[2] = 'R';
    vector<mint> A(N);
    rep(i, N) A[i] = mp[S[i]];

    AnyModTools mt(MOD, N);
    mint ans = 0;
    rep(i, N) {
        ans += A[i]*(mint)mt.nCr(N-1, i);
    }
    if (N%2 == 0) ans = -ans;
    print(revmp[(int)ans]);
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
