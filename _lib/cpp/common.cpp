/*
・ライブラリ：汎用
*/

#include "_tpl.cpp"


ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }

ll floor(ll a, ll b) { if (a < 0) return (a-b+1) / b; else return a / b; }
ll ceil(ll a, ll b) { if (a >= 0) return (a+b-1) / b; else return a / b; }
ll modulo(ll a, ll b) { return ((a % b) + b) % b; }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(const vector<T> &A) { return accumulate(ALL(A), (T)0); }
template<typename T> T max(const vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(const vector<T> &A) { return *min_element(ALL(A)); }

ll pow(int x, int n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(int x, ll n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(ll x, int n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(ll x, ll n) { ll res = 1; rep(_, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
int bit_length(ll x) { return x != 0 ? floor(log2((ld)x))+1 : 0; }

template<typename T> int bisect_left(const vector<T> &A, T val, int lo=0) { return lower_bound(A.begin()+lo, A.end(), val) - A.begin(); }
template<typename T> int bisect_right(const vector<T> &A, T val, int lo=0) { return upper_bound(A.begin()+lo, A.end(), val) - A.begin(); }


template<typename T>
map<T, ll> Counter(const vector<T> &A) {
    map<T, ll> res;
    for (T a : A) {
        res[a]++;
    }
    return res;
}
template<typename T>
vector<ll> Counter(const vector<T> &A, T mx) {

    vector<ll> res(mx+1);
    for (T a : A) {
        res[a]++;
    }
    return res;
}
map<char, ll> Counter(const string &S) {
    map<char, ll> res;
    for (char c : S) {
        res[c]++;
    }
    return res;
}


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


template<typename T1, typename T2>
pair<vector<T1>, vector<T2>> zip(const vector<pair<T1, T2>> &A) {
    int N = A.size();
    pair<vector<T1>, vector<T2>> res = {vector<T1>(N), vector<T2>(N)};
    rep(i, N) {
        res.first[i] = A[i].first;
        res.second[i] = A[i].second;
    }
    return res;
}
template<typename T1, typename T2, typename T3>
tuple<vector<T1>, vector<T2>, vector<T3>> zip(const vector<tuple<T1, T2, T3>> &A) {
    int N = A.size();
    tuple<vector<T1>, vector<T2>, vector<T3>> res = {vector<T1>(N), vector<T2>(N), vector<T3>(N)};
    rep(i, N) {
        get<0>(res)[i] = get<0>(A[i]);
        get<1>(res)[i] = get<1>(A[i]);
        get<2>(res)[i] = get<2>(A[i]);
    }
    return res;
}


// 座標圧縮(二分探索ベース)
template<typename T>
struct Compress {

    int N;
    vector<T> dat;

    Compress(vector<T> A) {
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        N = A.size();
        dat = A;
    }

    int zip(T x) {
        return bisect_left(dat, x);
    }

    T unzip(int x) {
        return dat[x];
    }

    int operator[](T x) {
        return zip(x);
    }

    int size() {
        return dat.size();
    }

    vector<T> zip(const vector<T> &A) {
        int M = A.size();
        vector<T> res(M);
        rep(i, M) res[i] = zip(A[i]);
        return res;
    }
};


// ランレングス圧縮
template<typename T>
vector<pair<T, int>> RLE(const vector<T> &A) {
    if (A.empty()) return {};
    int N = A.size();
    vector<pair<T, int>> res;
    T cur = A[0];
    int cnt = 1;
    rep(i, 1, N) {
        if (A[i] == A[i-1]) {
            cnt++;
        } else {
            res.pb({cur, cnt});
            cnt = 1;
            cur = A[i];
        }
    }
    res.pb({cur, cnt});
    return res;
}
// ランレングス圧縮(文字列)
vector<pair<char, int>> RLE(const string &S) {
    if (S.empty()) return {};
    int N = S.size();
    vector<pair<char, int>> res;
    char cur = S[0];
    int cnt = 1;
    rep(i, 1, N) {
        if (S[i] == S[i-1]) {
            cnt++;
        } else {
            res.pb({cur, cnt});
            cnt = 1;
            cur = S[i];
        }
    }
    res.pb({cur, cnt});
    return res;
}










////////// end template included here //////////










vector<string> split(const string &S, char separator) {
    int N = S.size();
    vector<string> res;
    string cur;
    rep(i, N) {
        if (S[i] == separator) {
            res.eb(cur);
            cur = "";
        } else {
            cur += S[i];
        }
    }
    if (cur.size()) res.eb(cur);
    return res;
}


string to_string(const string &S) { return S; }
template<typename T>
string join(const vector<T> &A, char separator=0) {
    int N = A.size();
    string res;
    rep(i, N) {
        res += tostr(A[i]);
        if (separator != 0 and i != N-1) res += separator;
    }
    return res;
}


template<typename T, typename F>
vector<T> mapping(const vector<string> &A, const F &f) {
    int N = A.size();
    vector<T> res(N);
    rep(i, N) res[i] = f(A[i]);
    return res;
}


template<typename T>
vector<T> sorted(vector<T> A, bool reverse=false) {
    sort(ALL(A));
    if (reverse) std::reverse(ALL(A));
    return A;
}


int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }


// 条件を満たす最小値を見つける二分探索(実数)
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


// 条件を満たす最大値を見つける二分探索(実数)
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


// [l,r)の範囲で乱数生成
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
ll randrange(ll l, ll r) {
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}


// 参考：https://rsk0315.hatenablog.com/entry/2021/02/23/163040
// 乗算のオーバーフロー検知
bool mul_overflow(ll x, ll y) {
    ll z;
    return __builtin_mul_overflow(x, y, &z);
}


// 三分探索(実数)
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


// 三分探索(整数)
template<typename F>
pll trisearch_min(ll lo, ll hi, const F &func, ll offset=1) {
    
    ll m1 = lo, l = lo;
    ll m2 = hi, r = hi;
    while (lo+2 < hi) {
        m1 = (lo*2+hi) / 3;
        m2 = (lo+hi*2) / 3;
        ll res1 = func(m1);
        ll res2 = func(m2);
        if (res1 <= res2) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    ll mn = INF;
    pll res;
    rep(i, max(m1-offset, l), min(m2+offset, r)) {
        ll val = func(i);
        if (val < mn) {
            mn = val;
            res = {i, val};
        }
    }
    return res;
}


// 三分探索(整数)
template<typename F>
pll trisearch_max(ll lo, ll hi, const F &func, ll offset=1) {
    
    ll m1 = lo, l = lo;
    ll m2 = hi, r = hi;
    while (lo+2 < hi) {
        m1 = (lo*2+hi) / 3;
        m2 = (lo+hi*2) / 3;
        ll res1 = func(m1);
        ll res2 = func(m2);
        if (res1 >= res2) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    ll mx = -INF;
    pll res;
    rep(i, max(m1-offset, l), min(m2+offset, r)) {
        ll val = func(i);
        if (val > mx) {
            mx = val;
            res = {i, val};
        }
    }
    return res;
}


// 座標圧縮(mapベース)(旧)
template<typename T>
pair<map<T, int>, vector<T>> compress(vector<T> unzipped) {
    map<T, int> zipped;
    sort(unzipped.begin(), unzipped.end());
    unzipped.erase(unique(unzipped.begin(), unzipped.end()), unzipped.end());
    rep(i, 0, unzipped.size()) {
        zipped[unzipped[i]] = i;
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


// インタラクティブ用
ll ask(ll i) {
    ll res;
    cout << "? " << i+1 << endl;
    cin >> res;
    res--;
    return res;
}

void answer(ll i) {
    cout << "! " << i+1 << endl;
}
