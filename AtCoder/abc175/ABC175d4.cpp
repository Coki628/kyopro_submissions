/**
 * ・ライブラリ整備：ダブリングのverify
 */

// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
typedef pair<ll, ld> pld;
typedef pair<pii, int> ppiii;
typedef pair<pii, ll> ppiil;
typedef pair<pll, ll> pplll;
typedef pair<pli, int> pplii;
typedef vector<vector<ll>> vvl;
typedef vector<vector<int>> vvi;
typedef vector<vector<pll>> vvpll;
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for(ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for(ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for(ll i = a, _bb = b; (a <= i && i < _bb) or (a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define mkp make_pair
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

template<typename T> inline bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> inline bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

ll sum(vector<ll> A) { ll res = 0; for (ll a: A) res += a; return res; }
ll max(vector<ll> A) { ll res = -INF; for (ll a: A) chmax(res, a); return res; }
ll min(vector<ll> A) { ll res = INF; for (ll a: A) chmin(res, a); return res; }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
// 数字なら'0'、アルファベットなら'a'みたいに使い分ける
// int toint(char c) { return c - '0'; }
// char tochar(int i) { return '0' + i; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T, typename F>
struct Doubling {

    int N;
    vector<vector<T>> dat;
    const int MXLOG;
    const F f;

    Doubling(int MXLOG, const vector<T> &A, T init, const F f) : MXLOG(MXLOG), f(f) {
        N = A.size();
        dat = list2d(MXLOG, N, init);
        rep(i, N) {
            dat[0][i] = A[i];
        }
        rep(k, 1, MXLOG) {
            rep(i, N) {
                dat[k][i] = f(dat[k-1][i], dat[k-1][dat[k-1][i]]);
            }
        }
    }

    // stから始めてK個先を返す
    T get(T st, ll K) {
        T res = st;
        rep(k, MXLOG-1, -1, -1) {
            if (K>>k & 1) {
                res = f(res, dat[k][res]);
            }
        }
        return res;
    }

    // stから始めて1個先を返す
    T next(T st) {
        return f(st, dat[0][st]);
    }
};

template<typename T, typename F>
Doubling<T, F> get_doubling(int MXLOG, const vector<T> &A, T init, const F f) {
    return {MXLOG, A, init, f};
}

struct Node {
    ll nxt, sm;
    operator ll() const { return nxt; }
};

auto f = [](const Node &prev, const Node &power) {
    Node res;
    res.nxt = power.nxt;
    res.sm = prev.sm + power.sm;
    return res;
};

ll N, K;
vector<ll> P, C, A;
const ll MAX = 32;
// ll nxt[MAX][5007], score[MAX][5007];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N >> K;
    P.resize(N);
    C.resize(N);
    rep(i, 0, N) {
        cin >> P[i];
        P[i]--;
    }
    rep(i, 0, N) cin >> C[i];

    vector<Node> A(N);
    rep(i, N) {
        A[i].nxt = P[i];
        A[i].sm = C[P[i]];
    }
    auto db = get_doubling(MAX, A, {-1, -1}, f);
    // rep(i, 0, N) {
    //     nxt[0][i] = P[i];
    //     score[0][i] = C[P[i]];
    // }
    // rep(k, 1, MAX) {
    //     rep(i, 0, N) {
    //         nxt[k][i] = nxt[k-1][nxt[k-1][i]];
    //         score[k][i] = score[k-1][i] + score[k-1][nxt[k-1][i]];
    //     }
    // }

    ll ans = -INF;
    // ll cur, sm, dist;
    rep(i, 0, N) {
        // 1からmin(K, N)まで見る
        Node cur = {i, 0};
        rep(j, 1, min(K, N)+1) {
            cur = db.next(cur);
            chmax(ans, cur.sm);
        }
        // cur = i;
        // sm = 0;
        // rep(j, 1, min(K, N)+1) {
        //     sm += score[0][cur];
        //     cur = nxt[0][cur];
        //     chmax(ans, sm);
        // }
        if (K > N) {
            // K-Nまで飛ぶ
            cur = db.get({i, 0}, K-N);
            // dist = K - N;
            // cur = i;
            // sm = 0;
            // rrep(k, MAX-1, -1) {
            //     if (dist >> k & 1) {
            //         sm += score[k][cur];
            //         cur = nxt[k][cur];
            //     }
            // }
            // K-NからKまで見る
            rep(j, N) {
                cur = db.next(cur);
                chmax(ans, cur.sm);
            }
            // rep(j, 0, N) {
            //     sm += score[0][cur];
            //     cur = nxt[0][cur];
            //     chmax(ans, sm);
            // }
        }
    }
    print(ans);
    return 0;
}
