/*
参考：https://betrue12.hateblo.jp/entry/2019/08/19/201430
・ABC高難度埋め
・難しい桁DP、2変数を扱う桁DP
・解説はアルメリアさんのものが分かりやすかったので感謝。
・まあ考察も実装も大変。まず考察、題意の条件を満たすには、
　・最大ビットが同じ位置
　・最大ビット未満については、各ビットについて、y >= x となる場所は全部OK。
　これを満たすような遷移を進めていけばいいことになる。
・ここまでについては、高い数学的考察力があれば考えて導出できるかもしれないけど、
　適当に小さい数で実験して察するってのが現実的だろう。
　自分はここまで詰めれなかったけど、実験コードを2進数表記にしたらしっかり見えたので、
　ビットが絡む以上、2進数表記の結果まで実験でチェックすべきだったね。
・さてここから実装。smallerフラグっぽいのが、上限だけでなく下限にもあるってのは
　まあ複雑にはなるけど同じような場合分けをそこでもやればいいとして、
　ビットを見る対象の元の値が今回は2つあるので、
　自分的にはここがこれは桁DP無理だろうって思ってしまった点だった。
・結論としてはこれは可能で、普通の桁DPでビットをx=0,1にするの2通りの遷移をしていたところを、
　ビットを(y,x)=(0,0),(0,1),(1,0),(1,1)にするの4通りみたいな遷移で考えればいい。
　言われると確かにそれでうまくいきそうだけど、これは自分では思いつかないなぁ。
・そして今回は各ビットについて y >= x でないといけないので、
　先ほどの4通りから(y,x)=(0,1)を除いた3通りが実際の遷移になる。
・後は上限、下限の条件と、最大ビットは両方1という条件を踏まえて、
　丁寧に場合分けしてDP遷移を組んでいくことになる。(詳細はソース内コメント)
　終わってみれば結構スッキリしたコードになったけど、これ全部自分で考えるの大変だ。。
・あと提出してみたら1WAで、原因はbit_length関数が小数誤差でバグってた。。
　つい最近のABC前半で似たような論点のやつ見てたから気付けたけど。。
　doubleじゃなくてldで処理するようにしたらAC。
　まあ本当は整数除算で2で割った回数みたいにした方が良さそうだけどね。。
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

template<typename T> T sum(const vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(const vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(const vector<T> &A) { return *min_element(ALL(A)); }

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
int bit_length(ll x) { return x != 0 ? floor(log2((ld)x))+1 : 0; }
string bin(ll x) { string res; while (x) { if (x & 1) res += '1'; else res += '0'; x >>= 1; } reverse(ALL(res)); if(res == "") res += '0'; return res; }

ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

ld degrees(ld radians) { return radians * 180.0 / PI; }
ld radians(ld degrees) { return degrees * PI / 180.0; }

template<typename T> int bisect_left(const vector<T> &A, T val, int lo=0) { return lower_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> int bisect_right(const vector<T> &A, T val, int lo=0) { return upper_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }

template<typename T> map<T, ll> Counter(const vector<T> &A) { map<T, ll> res; for (T a : A) res[a]++; return res; }
map<char, ll> Counter(string &S) { map<char, ll> res; for (char c : S) res[c]++; return res; }
template<typename T1, typename T2> pair<vector<T1>, vector<T2>> zip(vector<pair<T1, T2>> &A) { ll N = A.size(); pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)}; rep(i, N) { res.first[i] = A[i].first; res.second[i] = A[i].second; } return res; }

template<typename T> struct Accumulate {
    vector<T> acc; int N;
    Accumulate() {}
    Accumulate(int N) : N(N) { acc.resize(N); }
    Accumulate(const vector<T> &A) { N = A.size(); acc = A; build(); }
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
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

string zfill(string str, int len) {
    string zeros;
    int n = str.size();
    rep(i, len-n) zeros += '0';
    return zeros+str;
}

void solve() {
    ll L, R;
    cin >> L >> R;

    // rep(j, L, R+1) {
    //     rep(i, L, j+1) {
    //         if (j%i == (j^i)) {
    //             print(mkp(bin(j), bin(i)));
    //         }
    //     }
    // }

    ll N = bit_length(R);
    string S = zfill(bin(L), N);
    string T = bin(R);
    auto dp = list4d<mint>(N+1, 2, 2, 2, 0);
    dp[0][0][0][0] = 1;
    rep(i, N) {
        rep(a, 2) {
            rep(b, 2) {
                rep(c, 2) {
                    for (auto& nxt : {"00", "10", "11"}) {
                        // Lが1でgreater確定していないなら、どちらも1にしかできない
                        if (S[i] == '1' and a == 0 and nxt != "11") continue;
                        // Rが0でsmaller確定していないなら、どちらも0にしかできない
                        if (T[i] == '0' and b == 0 and nxt != "00") continue;
                        // 1桁目なら両方立てないといけない
                        if (c == 0 and nxt == "10") continue;
                        // 遷移先
                        ll aa = (S[i] == '0' and nxt == "11") ? 1 : a;
                        ll bb = (T[i] == '1' and nxt == "00") ? 1 : b;
                        ll cc = (nxt == "11") ? 1 : c;
                        dp[i+1][aa][bb][cc] += dp[i][a][b][c];
                    }
                }
            }
        }
    }
    mint ans = 0;
    rep(a, 2) {
        rep(b, 2) {
            ans += dp[N][a][b][1];
        }
    }
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
