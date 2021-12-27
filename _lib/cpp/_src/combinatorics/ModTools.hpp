#include "../macros.hpp"
#include "ModInt.hpp"

// Mod数え上げnCr (T=mint)
template<typename T>
struct ModTools {

    int MAX;
    vector<T> fact, factinv;

    ModTools() {};

    ModTools(int mx) {
        build(mx);
    }

    void build(int mx) {
        // nCrならn、nHrならn+rまで作る
        MAX = ++mx;
        fact.resize(MAX);
        factinv.resize(MAX);
        fact[0] = fact[1] = 1;
        rep(i, 2, MAX) {
            fact[i] = fact[i-1] * i;
        }
        factinv[MAX-1] = (T)1 / fact[MAX-1];
        rep(i, MAX-2, -1, -1) {
            factinv[i] = factinv[i+1] * (i+1);
        }
    }

    T factorial(int x) {
        return fact[x];
    }

    T inverse(int x) {
        return factinv[x];
    }

    T nCr(int n, int r) {
        if (n < r or r < 0) return 0;
        r = min(r, n-r);
        T num = fact[n];
        T den = factinv[r] * factinv[n-r];
        return num * den;
    }

    T nHr(int n, int r) {
        return nCr(r+n-1, r);
    }

    T nPr(int n, int r) {
        if (n < r or r < 0) return 0;
        return fact[n] * factinv[n-r];
    }
};
