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


// 参考：https://outline.hatenadiary.jp/entry/2020/07/02/205628
// きたまさ法
template<typename T>
struct Kitamasa {
    vector<T> a;    // 初期値ベクトル
    vector<T> d;    // 係数ベクトル
    int k;
    
    Kitamasa(vector<T>& a, vector<T>& d) : a(a), d(d), k((int)a.size()) {}
    
    // a_n の係数ベクトルを求める
    vector<T> dfs(int64_t n) {
        if (n == k)  return d;
        
        vector<T> res(k);
        if (n & 1 || n < k * 2) {
            vector<T> x = dfs(n - 1);
            for (int i = 0; i < k; ++i)  res[i] = d[i] * x[k - 1];
            for (int i = 0; i + 1 < k; ++i)  res[i + 1] += x[i];
        }
        else {
            vector<vector<T>> x(k, vector<T>(k));
            x[0] = dfs(n >> 1);
            for (int i = 0; i + 1 < k; ++i) {
                for (int j = 0; j < k; ++j)  x[i + 1][j] = d[j] * x[i][k - 1];
                for (int j = 0; j + 1 < k; ++j)  x[i + 1][j + 1] += x[i][j];
            }
            for (int i = 0; i < k; ++i){
                for (int j = 0; j < k; ++j) {
                    res[j] += x[0][i] * x[i][j];
                }
            }
        }

        return res;
    }

    // a_n を求める
    T calc(int64_t n) {
        if (n < k) return a[n];
        vector<T> x = dfs(n);
        T res = 0;
        for (int i = 0; i < k; ++i)  res += x[i] * a[i];
        return res;
    }
};