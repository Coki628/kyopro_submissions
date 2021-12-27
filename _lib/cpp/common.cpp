/*
・ライブラリ：汎用
*/

#include "_tpl.cpp"


template<typename T, typename F>
vector<T> mapping(const vector<string> &A, const F &f) {
    int N = A.size();
    vector<T> res(N);
    rep(i, N) res[i] = f(A[i]);
    return res;
}


int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }


// 条件を満たす最小値を見つける二分探索(実数)
template<typename F>
ld bisearch_min(ld mn, ld mx, const F &func, ll times) {

    ld ok = mx;
    ld ng = mn;
    rep(_, times) {
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
    rep(_, times) {
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


// 三分探索(実数)
template<typename F>
pair<ld, ld> trisearch_min(ld lo, ld hi, const F &func, ll times) {

    ld m1 = lo;
    ld m2 = hi;
    rep(_, times) {
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
    rep(i, unzipped.size()) {
        zipped[unzipped[i]] = i;
    }
    return {zipped, unzipped};
}


// 速いhashmap
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
