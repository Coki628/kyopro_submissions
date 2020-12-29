/**
 * 参考：https://fairy-lettuce.hatenadiary.com/entry/2020/12/29/025529
 * ・むずい。ロリハ確認ついでに頑張って解いた。
 * ・文字列操作、ローリングハッシュ、辞書順最小、鳩の巣原理
 * ・まず重要な考察として、逆を考えることがある。
 * 　今回、全ての部分文字列で共通部分が1つでもないといけないが、
 * 　これは、どの部分文字列とも一致しないものを反転させると達成できる。
 * 　どれかと一致する部分文字列の場合、反転させたらその部分文字列との共通部分がなくなってしまうので、
 * 　結果的にどの部分文字列とも一致しないのが良しとなる。(でもこれ、気付かないなー。。。)
 * ・とりあえず出現する部分文字列を列挙したい。これは陽にやると、今回の制約N<=100万から、
 * 　例えば長さ50万の文字列切り出しを約50万回とかやらなきゃいけなくなって死ぬ。
 * 　これはロリハで取ったハッシュをsetに入れておくような形にすればいける。
 * ・で、一致しないものの中で辞書順最小を探すことになるが、これは反転させるので辞書順最大から探す。
 * 　まともに全部探すと2^K種類あって探しきれないように思えるが、出現した部分文字列が
 * 　仮に全部一意だったとしてもN-K+1個しかないはずなので、最大でもここまでには見つかる。
 * 　それでも1回毎にチェックする文字列のハッシュを取らないといけないので、
 * 　全部やったら間に合わないように思えるが、連続した部分文字列を切り取ってきているので、
 * 　辞書順で後ろの方だけが綺麗に揃うってことがまずないんだと思う。(多分)
 * ・割と早い段階で当たりを引くのだろうと信じて投げると、無事ACする。。1.19秒。
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

struct RollingHash {
    static const uint64_t mod = (1ull << 61ull) - 1;
    using uint128_t = __uint128_t;
    vector< uint64_t > power;
    const uint64_t base;

    static inline uint64_t add(uint64_t a, uint64_t b) {
        if((a += b) >= mod) a -= mod;
        return a;
    }

    static inline uint64_t mul(uint64_t a, uint64_t b) {
        uint128_t c = (uint128_t) a * b;
        return add(c >> 61, c & mod);
    }

    // 2^61-1以下の乱数を返す。これをbaseとするとHackされにくい
    static inline uint64_t generate_base() {
        mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution< uint64_t > rand(1, RollingHash::mod - 1);
        return rand(mt);
    }

    inline void expand(size_t sz) {
        if(power.size() < sz + 1) {
            int pre_sz = (int) power.size();
            power.resize(sz + 1);
            for(int i = pre_sz - 1; i < sz; i++) {
                power[i + 1] = mul(power[i], base);
            }
        }
    }

    // 基数baseのローリングハッシュを構築する
    explicit RollingHash(uint64_t base = generate_base()) : base(base), power{1} {}

    // 文字列sのハッシュテーブルを返す：O(n)
    vector< uint64_t > build(const string &s) const {
        int sz = s.size();
        vector< uint64_t > hashed(sz + 1);
        for(int i = 0; i < sz; i++) {
            hashed[i + 1] = add(mul(hashed[i], base), s[i]);
        }
        return hashed;
    }

    template< typename T >
    vector< uint64_t > build(const vector< T > &s) const {
        int sz = s.size();
        vector< uint64_t > hashed(sz + 1);
        for(int i = 0; i < sz; i++) {
            hashed[i + 1] = add(mul(hashed[i], base), s[i]);
        }
        return hashed;
    }

    // sの区間[l,r)のハッシュ値を返す：O(1)
    uint64_t query(const vector< uint64_t > &s, int l, int r) {
        expand(r - l);
        return add(s[r], mod - mul(s[l], power[r - l]));
    }

    // ハッシュ値h1と長さh2lenのハッシュ値h2を結合する
    uint64_t combine(uint64_t h1, uint64_t h2, size_t h2len) {
        expand(h2len);
        return add(mul(h1, power[h2len]), h2);
    }

    // ハッシュテーブルaの区間[l1,r1)と、ハッシュテーブルbの区間[l2,r2)の文字列の最長共通接頭辞の長さを返す：O(logn)
    int lcp(const vector< uint64_t > &a, int l1, int r1, const vector< uint64_t > &b, int l2, int r2) {
        int len = min(r1 - l1, r2 - l2);
        int low = 0, high = len + 1;
        while(high - low > 1) {
            int mid = (low + high) / 2;
            if(query(a, l1, l1 + mid) == query(b, l2, l2 + mid)) low = mid;
            else high = mid;
        }
        return low;
    }
};

void solve() {
    ll N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    // 部分文字列のハッシュを全てsetに詰める
    RollingHash rh;
    auto hash_s = rh.build(S);
    set<ll> se;
    rep(i, 0, N-K+1) {
        ll h = rh.query(hash_s, i, i+K);
        se.insert(h);
    }

    // 辞書順最大の111111..から見ていく
    string T(K, '1');
    rep(i, 0, N-K+2) {
        auto hash_t = rh.build(T);
        ll h = rh.query(hash_t, 0, K);
        // 元の文字列にないものが見つかったら反転して出力
        if (!se.count(h)) {
            YES();
            rep(j, 0, K) T[j] = '1' - (T[j]-'0');
            print(T);
            return;
        }
        // 辞書順で1つずつ進めていく
        rep(k, 0, min(20LL, K)) {
            ll j = K - k - 1;
            if ((i+1) % pow(2, k) == 0) {
                T[j] = '1' - (T[j]-'0');
            }
        }
    }
    NO();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) solve();

    return 0;
}
