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
constexpr ll INF = LONG_LONG_MAX;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

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
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }

inline ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
inline ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

inline ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
inline ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }


template<typename T>
unordered_map<T, ll> Counter(vector<T> &A) {
    unordered_map<T, ll> res;
    for (T a : A) {
        res[a]++;
    }
    return res;
}


unordered_map<char, ll> Counter(string &S) {
    unordered_map<char, ll> res;
    for (char c : S) {
        res[c]++;
    }
    return res;
}


template<typename T>
vector<T> accumulate(vector<T> &A) {
    int N = A.size();
    if (!N) return {};
    vector<T> res(N);
    res[0] = A[0];
    rep(i, 1, N) res[i] = res[i-1] + A[i];
    return res;
}


template<typename T, typename F>
vector<T> accumulate(vector<T> &A, const F &func) {
    int N = A.size();
    if (!N) return {};
    vector<T> res(N);
    res[0] = A[0];
    rep(i, 1, N) res[i] = func(res[i-1], A[i]);
    return res;
}
// accumulate<ll>(A, [](ll a, ll b) { return min(a, b); });


// 条件を満たす最小値を見つける二分探索
template<typename F>
ll bisearch_min(ll mn, ll mx, const F &func) {

    ll ok = mx;
    ll ng = mn;
    while (ng+1 < ok) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 下を探しに行く
            ok = mid;
        } else {
            // 上を探しに行く
            ng = mid;
        }
    }
    return ok;
}


// 条件を満たす最大値を見つける二分探索
template<typename F>
ll bisearch_max(ll mn, ll mx, const F &func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}


// 条件を満たす最小値を見つける二分探索(小数用)
template<typename F>
ld bisearch_min(ld mn, ld mx, const F &func, ll times) {

    ld ok = mx;
    ld ng = mn;
    rep(_, 0, times) {
        ld mid = (ok+ng) / 2;
        if (func(mid)) {
            // 下を探しに行く
            ok = mid;
        } else {
            // 上を探しに行く
            ng = mid;
        }
    }
    return ok;
}


// 条件を満たす最大値を見つける二分探索(小数用) 
template<typename F>
ld bisearch_max(ld mn, ld mx, const F &func, ll times) {

    ld ok = mn;
    ld ng = mx;
    rep(_, 0, times) {
        ld mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}


// 三分探索(小数)
template<typename F>
pair<ld, ld> trisearch_min(ld lo, ld hi, const F &func, ll times) {

    ld m1 = lo;
    ld m2 = hi;
    rep(_, 0, times) {
        m1 = (lo*2+hi) / 3;
        m2 = (lo+hi*2) / 3;
        ld res1 = func(m1);
        ld res2 = func(m2);
        if (res1 <= res2) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    ld i = min(m1, m2);
    ld val = func(i);
    return {i, val};
}


// 座標圧縮
typedef unordered_map<ll, int> mli;
typedef unordered_map<int, ll> mil;
pair<mli, mil> compress(vector<ll> A) {
    mli zipped;
    mil unzipped;
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    rep(i, 0, A.size()) {
        zipped[A[i]] = i;
        unzipped[i] = A[i];
    }
    return {zipped, unzipped};
}


// なんかこれ速いhashmapらしい
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct custom_hash {
    // https://codeforces.com/blog/entry/62393
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
// gp_hash_table<ll,ll,custom_hash> mp;


// 行列累乗
template<typename T>
struct MatPow {

    MatPow() {}

    vector<vector<T>> mat_dot(vector<vector<T>> &A, vector<vector<T>> &B) {
        int n1 = A.size();
        int n2 = A[0].size();
        int m2 = B[0].size();
        auto res = list2d(n1, m2, (T)0);
        rep(i, 0, n1) {
            rep(j, 0, m2) {
                rep(k, 0, n2) {
                    res[i][j] = (res[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
                }
            }
        }
        return res;
    }
    
    vector<vector<T>> mat_pow(vector<vector<T>> mat, ll k) {
        int n = mat.size();
        auto res = list2d(n, n, (T)0);
        rep(i, 0, n) {
            res[i][i] = 1;
        }
        while (k > 0) {
            if (k & 1) {
                res = mat_dot(res, mat);
            }
            mat = mat_dot(mat, mat);
            k >>= 1;
        }
        return res;
    }

    vector<T> solve(vector<vector<T>> mat, vector<T> &_init, ll K) {
        int n = mat.size();
        auto init = list2d(n, 1, (T)0);
        rep(i, 0, n) init[i][0] = _init[i];
        auto res = mat_pow(mat, K);
        res = mat_dot(res, init);
        vector<T> ret(n, 0);
        rep(i, 0, n) ret[i] = res[i][0];
        return ret;
    }
};


// ダブリング
vvl doubling(int MXLOG, vector<ll> &A) {

    int N = A.size();
    auto nxt = list2d(MXLOG, N, -1LL);
    rep(i, 0, N) {
        nxt[0][i] = A[i];
    }
    rep(k, 1, MXLOG) {
        rep(i, 0, N) {
            if (nxt[k-1][i] != -1) {
                nxt[k][i] = nxt[k-1][nxt[k-1][i]];
            }
        }
    }
    return nxt;
}


// [l,r)の範囲で乱数生成
ll randrange(ll l, ll r) {
    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}


// 最小増加部分列
template<typename T>
vector<T> LIS(vector<T> &A, bool equal=false) {

    auto compare = (not equal) ? [](T a, T b) { return a > b; } : [](T a, T b) { return a >= b; };
    auto bisect = (not equal) ? bisect_left<T> : bisect_right<T>;
    vector<T> res;
    res.pb(A[0]);
    ll n = A.size();
    rep(i, 1, n) {
        if (compare(A[i], res.back())) {
            res.pb(A[i]);
        } else {
            res[bisect(res, A[i])] = A[i];
        }
    }
    return res;
}
