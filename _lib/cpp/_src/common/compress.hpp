#include "../macros.hpp"

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
