/**
 * ・pypy通らなかったのでこっちで。
 * ・配る遷移と貰う遷移を両方やるDP、セグ木上の二分探索
 * ・30万にlogで、C++AC0.59秒。やっぱSparse Tableが遅いのかなー。
 * ・セグ木でも通るか試してみた。C++AC1.65秒。まあ遅くはなるけど通るね。
 * ・TODO: SojiさんのACLのセグ木使ってるやつめっちゃ速かったから、時間ある時にチェックする。
 * →https://codeforces.com/contest/1407/submission/92273033
 * ・functionやめてtemplate引数にしてみたけど、速くならなかった。。
 * ・セグ木の演算もFunctionやめてラムダにした。速くなった！AC1.14秒。
 * ・セグ木にぶたんをちゃんと速いのにした。爆速。AC0.11秒。
 * 　log1つのはずだし、それはそうか。。
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

template<typename Monoid, typename F>
struct SegmentTree {
    
    int sz;
    vector<Monoid> seg;
    
    const F f;
    const Monoid M1;
    
    SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    void clear() {
        seg.clear();
    }
    
    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
    }
    
    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    void build(vector<Monoid> &A) {
        int n = A.size();
        resize(n);
        rep(i, 0, n) set(i, A[i]);
        build();
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }
 
    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = f(L, seg[a++]);
            if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }

    Monoid all() {
        return seg[1];
    }

    void print(int n) {
        rep(i, 0, n) {
            cout << query(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }

    template<typename C>
    int find_subtree(int a, const C &check, Monoid &M, bool type) {
        while(a < sz) {
            Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
            if(check(nxt)) a = 2 * a + type;
            else M = nxt, a = 2 * a + 1 - type;
        }
        return a - sz;
    }

    template<typename C>
    int find_first(int a, const C &check) {
        Monoid L = M1;
        if(a <= 0) {
            if(check(f(L, seg[1]))) return find_subtree(1, check, L, false);
            return -1;
        }
        int b = sz;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) {
                Monoid nxt = f(L, seg[a]);
                if(check(nxt)) return find_subtree(a, check, L, false);
                L = nxt;
                ++a;
            }
        }
        return -1;
    }

    template<typename C>
    int find_last(int b, const C &check) {
        Monoid R = M1;
        if(b >= sz) {
            if(check(f(seg[1], R))) return find_subtree(1, check, R, true);
            return -1;
        }
        int a = sz;
        for(b += sz; a < b; a >>= 1, b >>= 1) {
            if(b & 1) {
                Monoid nxt = f(seg[--b], R);
                if(check(nxt)) return find_subtree(b, check, R, true);
                R = nxt;
            }
        }
        return -1;
    }
};

template<typename Monoid, typename F>
SegmentTree<Monoid, F> get_segment_tree(int N, const F& f, const Monoid& M1) {
    return {N, f, M1};
}

template<typename Monoid, typename F>
SegmentTree<Monoid, F> get_segment_tree(const F& f, const Monoid& M1) {
    return {f, M1};
}

ll N;
vector<ll> A, dp;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    dp.assign(N, INF);
    auto stmn = get_segment_tree([](ll a, ll b) { return min(a, b); }, INF);
    auto stmx = get_segment_tree([](ll a, ll b) { return max(a, b); }, -INF);
    stmn.resize(N);
    stmx.resize(N);
    rep(i, 0, N) {
        cin >> A[i];
        stmn.set(i, A[i]);
        stmx.set(i, A[i]);
    }
    stmn.build();
    stmx.build();

    ll prev, nxt;
    dp[0] = 0;
    rep(cur, 0, N) {
        if (cur != 0) {
            prev = stmn.find_last(cur, [&](ll x) { return x <= A[cur]; });
            if (prev != -1) {
                chmin(dp[cur], dp[prev] + 1);
            }
            prev = stmx.find_last(cur, [&](ll x) { return x >= A[cur]; });
            if (prev != -1) {
                chmin(dp[cur], dp[prev] + 1);
            }
        }
        if (cur != N-1) {
            nxt = stmn.find_first(cur+1, [&](ll x) { return x <= A[cur]; });
            if (nxt != -1) {
                chmin(dp[nxt], dp[cur] + 1);
            }
            nxt = stmx.find_first(cur+1, [&](ll x) { return x >= A[cur]; });
            if (nxt != -1) {
                chmin(dp[nxt], dp[cur] + 1);
            }
        }
    }
    ll ans = dp[N-1];
    print(ans);
    return 0;
}
