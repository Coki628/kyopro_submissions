/**
 * 参考：https://atcoder.jp/contests/abc189/editorial
 * 　　　https://fairy-lettuce.hatenadiary.com/entry/2021/01/24/115737
 * ・自力ならず。
 * ・期待値DP、1次式の応用
 * ・一応、本番中ちゃんと考えて、期待値DPとして正しい流れを考察してた。
 * 　後ろから見て、目の数だけ先から遷移させてきて、足してその数で割る、に今回の1を足す。
 * 　この流れ自体は合ってた。ただ今回は「ふりだしに戻る」があるので、
 * 　急に遷移の途中にdp[0]を使おうにもまだそこは確定してないから無理、、で詰まって終了。
 * ・この先のことは、れたすさんが記事書いて詳しく説明してくれてた。
 * ・こういう時、ふりだし地点の期待値をxとして f(0) = ax + b って1次式にするといいらしい。
 * 　このa,bを分けた状態でDPしていくことができて、最後にdp[0]までやりきったら
 * 　その時のa,bが分かるので、x = ax + b みたいのを式変形して x = b/(1-a) とすれば
 * 　最終的な答えが分かる、というもの。
 * ・a,bの具体的な遷移については、aがふりだし担当、bが普通のところ担当みたいになる。
 * 　NGマスでは dp[i] = x としたいので、ax + b を 1*x + 0 とするために a = 1, b = 0 とする。
 * 　OKマスでは普通に期待値DPっぽい遷移をする。bは前に進むので+1する。
 * ・でもむずいよなー。自分でこの遷移とか式変形を導けるかと言われると。。
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

template<typename T>
struct BIT {

    int sz;
    vector<T> tree;

    BIT(int n) {
        // 0-indexed
        n++;
        sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        tree.resize(sz);
    }

    // [0, i]を合計する
    T sum(int i) {
        T s = 0;
        i++;
        while (i > 0) {
            s += tree[i-1];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, T x) {
        i++;
        while (i <= sz) {
            tree[i-1] += x;
            i += i & -i;
        }
    }

    // 区間和の取得 [l, r)
    T query(int l, int r) {
        return sum(r-1) - sum(l-1);
    }

    T get(int i) {
        return query(i, i+1);
    }

    void update(int i, T x) {
        add(i, x - get(i));
    }

    T operator[](int i) {
        return get(i);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, M, K;
    cin >> N >> M >> K;
    vector<bool> ng(N+1);
    rep(i, 0, K) {
        ll a;
        cin >> a;
        ng[a] = 1;
    }

    vector<ll> acc(N+2);
    acc[0] = ng[0];
    rep(i, 0, N+1) {
        acc[i+1] += acc[i]+ng[i];
    }
    rep(l, 0, N+1) {
        ll r = l+M;
        if (r > N+1) break;
        ll sm = acc[r]-acc[l];
        if (sm == M) {
            print(-1);
            return 0;
        }
    }

    BIT<ld> dpa(N+1), dpb(N+1);
    rrep(i, N-1, -1) {
        if (ng[i]) {
            dpa.add(i, 1);
            dpb.add(i, 0);
        } else {
            ll j = min(i+M, N);
            dpa.add(i, dpa.query(i+1, j+1)/M);
            dpb.add(i, dpb.query(i+1, j+1)/M+1);
        }
    }
    ld ans = dpb[0] / (1-dpa[0]);
    print(ans);
}
