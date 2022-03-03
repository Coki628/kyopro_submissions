#include "../macros.hpp"
#include "listnd.hpp"

// ダブリング
template<typename T, typename F>
struct Doubling {

    int N;
    vector<vector<T>> dat;
    const int MXLOG;
    const F f;

    // 通常はこっち
    Doubling(int MXLOG, const vector<T> &A, T init, const F &f) : MXLOG(MXLOG), f(f) {
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

    // ダブリング配列をライブラリ外で事前構築するコンストラクタ
    Doubling(const vector<vector<T>> &A, const F &f) : MXLOG(A.size()), dat(A), f(f) {}

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

    vector<T> get(const vector<T> &st, ll K) {
        vector<T> res = st;
        rep(k, MXLOG-1, -1, -1) {
            if (K>>k & 1) {
                res = f(res, dat[k], k);
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
Doubling<T, F> get_doubling(int MXLOG, const vector<T> &A, T init, const F &f) {
    return {MXLOG, A, init, f};
}

template<typename T, typename F>
Doubling<T, F> get_doubling(const vector<vector<T>> &A, const F &f) {
    return {A, f};
}
