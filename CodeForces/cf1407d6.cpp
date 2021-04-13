/**
 * ・Sparse TableのFunctionなしラムダ版verify
 */

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
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define mkp make_pair
#define list2d(name, N, M, type, init) vector<vector<type>> name(N, vector<type>(M, init))
const ll INF = LONG_LONG_MAX;
const ll MOD = 1000000007;

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
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
struct SparseTable {

    const F f;
    vector<vector<T>> dat;
    vector<ll> height;

    SparseTable(const F f) : f(f) {}

    SparseTable(vector<T> &A, const F f) : f(f) {
        build(A);
    }

    void build(vector<T> &A) {
        ll N = A.size();

        ll h = 0;
        while ((1<<h) <= N) {
            h++;
        }
        dat.resize(h);
        rep(i, 0, h) dat[i].resize(1<<h);
        height.resize(N+1);

        rep(i, 2, N+1) {
            height[i] = height[i>>1] + 1;
        }
        rep(i, 0, N) {
            dat[0][i] = A[i];
        }
        rep(i, 1, h) {
            rep(j, 0, N) {
                dat[i][j] = f(dat[i-1][j], dat[i-1][min(j+(1<<(i-1)), N-1)]);
            }
        }
    }

    // 区間[l,r)でのmin,maxを取得
    T query(ll l, ll r) {
        assert(l < r);
        ll a = height[r-l];
        return f(dat[a][l], dat[a][r-(1<<a)]);
    }

    // 区間[l,r]で左から最初にxに対して比較の条件を満たすような値が出現する位置
    template<typename G> ll bisearch_fore(ll l, ll r, T x, const G &compare) {
        ll ok = r + 1;
        ll ng = l - 1;
        while (ng+1 < ok) {
            ll mid = (ok+ng) / 2;
            if (compare(query(l, mid+1), x)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != r + 1) {
            return ok;
        } else {
            return -1;
        }
    }

    // 区間[l,r]で右から最初にxに対して比較の条件を満たすような値が出現する位置
    template<typename G> ll bisearch_back(ll l, ll r, T x, const G &compare) {
        ll ok = l - 1;
        ll ng = r + 1;
        while (ok+1 < ng) {
            ll mid = (ok+ng) / 2;
            if (compare(query(mid, r+1), x)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != l - 1) {
            return ok;
        } else {
            return -1;
        }
    }
};

template<typename T, typename F>
SparseTable<T, F> get_sparse_table(vector<T> &A, const F& f) {
    return {A, f};
}

ll N;
vector<ll> A, dp;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    dp.assign(N, INF);
    rep(i, 0, N) cin >> A[i];
    auto stmn = get_sparse_table(A, [](ll a, ll b) { return min(a, b); });
    auto stmx = get_sparse_table(A, [](ll a, ll b) { return max(a, b); });

    ll prev, nxt;
    dp[0] = 0;
    rep(cur, 0, N) {
        if (cur != 0) {
            prev = stmn.bisearch_back(0, cur-1, A[cur], less_equal<ll>());
            if (prev != -1) {
                chmin(dp[cur], dp[prev] + 1);
            }
            prev = stmx.bisearch_back(0, cur-1, A[cur], greater_equal<ll>());
            if (prev != -1) {
                chmin(dp[cur], dp[prev] + 1);
            }
        }
        if (cur != N-1) {
            nxt = stmn.bisearch_fore(cur+1, N-1, A[cur], less_equal<ll>());
            if (nxt != -1) {
                chmin(dp[nxt], dp[cur] + 1);
            }
            nxt = stmx.bisearch_fore(cur+1, N-1, A[cur], greater_equal<ll>());
            if (nxt != -1) {
                chmin(dp[nxt], dp[cur] + 1);
            }
        }
    }
    ll ans = dp[N-1];
    print(ans);
    return 0;
}
