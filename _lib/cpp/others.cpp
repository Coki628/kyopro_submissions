/*
・ライブラリ：その他
*/

#include "_tpl.cpp"


// 最小増加部分列
template<typename T>
vector<T> LIS(const vector<T> &A, bool equal=false) {

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


// ダブリング
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

    // stから始めてgに到達するまでの回数を返す
    ll times(T st, ll g) {
        T cur = st;
        ll res = 0;
        rep(k, MXLOG-1, -1, -1) {
            if (dat[k][cur] < g) {
                res += 1LL<<k;
                cur = dat[k][cur];
            }
        }
        res++;
        return res;
    }
};

template<typename T, typename F>
Doubling<T, F> get_doubling(int MXLOG, const vector<T> &A, T init, const F f) {
    return {MXLOG, A, init, f};
}


// ダブリング(旧)
vvl doubling(int MXLOG, const vector<ll> &A) {

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
