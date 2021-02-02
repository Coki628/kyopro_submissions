/**
 * ・蟻本演習4-7-4
 * ・文字列検索、ローリングハッシュ
 * ・自力AC！これは嬉しい。
 * ・調べる部分文字列について、jag2017autumn_hとほぼ同じ考え方が適用できる。
 * 　単語長の総和が20万なので、単語長の種類数は√20万くらいに抑えられる。
 * 　存在する単語長についてだけメイン文字列の部分文字列をチェックすれば、N√20万で全部見れる。
 * ・チェック内容としては、そのハッシュに対応する単語のIDを持っておいて、
 * 　各単語について一致を見つけたところで左端のchminと右端のchmaxをやればいい。
 * 　注意点として、ここで出した最大文字列長が、左端文字列より短くなってしまったらNGで0。
 * ・で、ここまでで出したら2件TLE。よくよく再考すると、同じ文字列ばっかり出てくると、
 * 　chmin,chmaxの処理を無駄にやりまくっている気がした。
 * 　そこで、左端は左から見ていって最初に当たったところで確定だし、
 * 　右端は右から見ていって最初に当たったところで確定であることを使うことにした。
 * 　つまり左端チェックは左から進めて既にいい値が入っていたらそこはbreak、
 * 　右端チェックは右から進めてその逆をやる。これで無事AC0.74秒。(制約4秒)
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

    uint64_t get_hash(string &s, int l, int r) {
        auto table = build(s);
        return query(table, l, r);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    string S;
    cin >> S;
    ll N = S.size();
    RollingHash rh;
    auto s_table = rh.build(S);
    ll M;
    cin >> M;
    map<ll, unordered_map<int64_t, vector<ll>>> hashl, hashr;
    vector<ll> szl(M);
    rep(i, 0, M) {
        string x, y;
        cin >> x >> y;
        auto x_hash = rh.get_hash(x, 0, x.size());
        auto y_hash = rh.get_hash(y, 0, y.size());
        hashl[x.size()][x_hash].pb(i);
        hashr[y.size()][y_hash].pb(i);
        szl[i] = x.size();
    }

    vector<pll> ans(M, {INF, -INF});
    rep(i, 0, N) {
        for (auto& [j, mp] : hashl) {
            if (i+j > N) break;
            auto s_hash = rh.query(s_table, i, i+j);
            if (mp.count(s_hash)) {
                for (ll k : mp[s_hash]) {
                    if (ans[k].first < i) break;
                    chmin(ans[k].first, i);
                }
            }
        }
    }
    rrep(i, N-1, -1) {
        for (auto& [j, mp] : hashr) {
            if (i+j > N) break;
            auto s_hash = rh.query(s_table, i, i+j);
            if (mp.count(s_hash)) {
                for (ll k : mp[s_hash]) {
                    if (ans[k].second > i+j) break;
                    chmax(ans[k].second, i+j);
                }
            }
        }
    }

    rep(i, 0, M) {
        auto [l, r] = ans[i];
        ll len = r-l;
        if (len >= szl[i]) {
            print(len);
        } else {
            print(0);
        }
    }
    return 0;
}
