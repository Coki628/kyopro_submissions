/**
 * 参考：https://twitter.com/kumakumaaaaa__/status/1372594767222083585
 * 　　　https://twitter.com/laycrs/status/1372591337598455810
 * ・自力ならず。いやあ難しかった。
 * ・LCMの式変形、前計算、素因数の個数、約数列挙
 * ・数学考察強めなやつ。苦手。でもこういうの解けるようになりたい。
 * ・まず始めに、式変形する必要があるけど、lcm(a, b)はgcd(a, b)の倍数なのが確定なので、
 * 　lcm(a, b) = k*gcd(a, b) という形にして、式からlcmを消す。ここがまずできなかった。
 * ・次に、ここから式変形していくと、c*k-d = x/gcd といった形が取れる。
 * 　これの何が嬉しいかと言うと、変数gcdが定数xの分母になることで、
 * 　出てくる値が全て整数であることから、gcdはxの約数しか取り得ないことが分かる。
 * 　こうなるとgcdの候補になる値は√x個まで絞り込めるので、だいぶ答えに近づく。
 * ・上記gcdを決めて全探索する。このgcdが定まると、式に変数はkだけになるので、
 * 　kも一意に定まる。このkは、lcmがk*gcdであることを意味するので、
 * 　lcmがどのくらいgcdより大きいのかが分かる。もっと直感的にに言うと、
 * 　gcdから「はみ出してる」部分がどのくらいあるのかが分かることになる。
 * 　gcdはa,bの共通部分なので、ここはa,b両方の要素が持っている必要がある。
 * 　はみ出した部分はどちらかだけが持っている部分なので、
 * 　これをa,bに振り分ける通り数が分かれば、それが答えになる。
 * ・ここではみ出した素因数を自由に振り分けられるのかと言うと、少し違う。
 * 　これ理解するのに時間かかった。色々図とか書いて理解。
 * 　例えば、素因数2が2つはみ出していたとして、これをa,bに1つずつ分けようとする。
 * 　ここで何が起こるかと言うと、両方共通の因数になってしまうので、
 * 　決めてあるgcdの値が変わってしまう。これではダメ。
 * 　同じ素因数は全部片方に寄せないといけない。
 * 　つまり通り数を増やせるのは、はみ出した素因数の個数ではなく種類数。
 * 　どちらに振るかなので2冪を足しこんでいけばいい。
 * 　これを全部のgcdについてやっていけば答えになる。
 * ・考察終わり。超大変じゃん。あー疲れた。
 * ・で、実装上はxの約数列挙とkの素因数数えるのを両方その場でやろうとすると間に合わないので、
 * 　素因数の方は前計算しておく。篩をちょっといじると全列挙できる。
 * 　この時、k = (x/gcd)+d/c になるんだけど、
 * 　xとdがでかくてcが1とかだと最大値の1000万も普通に超えてくる。2000万まで用意すること。
 * ・とりあえずこれで普通に投げたらなんとか通ってAC1.996秒。危なすぎー。
 * 　計算量がテストケース1万と√xが√1000万で3000ちょっと、これで3000万くらいだからきついんだな。
 * 　実際はここでpowしてるからさらにlogが乗ってるようなもんだし、前計算で2000万の篩もある。
 * ・約数列挙のソートをコメントアウトしたらAC1.45秒。
 * 　約数ってそんな大きくならないだろうし、このlogは対して影響ないと思ってたけど、
 * 　計算量きつい時は意外と影響するんだな…。
 * 　多分、1万個のテストケース全部で約数のかなり多いやつ連投してるやつがあるんだと思う。
 * 　それが約数1000以上とかあったら、さすがにlogも無視できない物量になりそうだし。
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
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define elif else if
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr ld EPS = 1e-10;

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
    // operator int() const { return x; }
};
using mint = ModInt<MOD>;

vector<ll> divisors(ll n) {

    vector<ll> res;
    for (ll i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.pb(i);
            if (n/i != i) res.pb(n/i);
        }
    }
    // sort(ALL(res));
    return res;
}

// table[i] := iが持つ素因数の種類数
vector<ll> eratosthenes_sieve(ll n) {

    vector<ll> table(n+1);
    rep(i, 2, n+1) {
        if (table[i] == 0) {
            for (ll j=i; j<=n; j+=i) {
                table[j]++;
            }
        }
    }
    return table;
}

vector<ll> table;

void prep() {
    table = eratosthenes_sieve(20000000);
}

void solve() {
    ll c, d, x;
    cin >> c >> d >> x;

    ll ans = 0;
    for (ll g : divisors(x)) {
        if ((x/g+d)%c) continue;
        ll k = (x/g+d)/c;
        ans += pow(2, table[k]);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
