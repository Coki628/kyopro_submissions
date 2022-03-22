#pragma once
#include "../macros.hpp"

// Mod数え上げ演算ツール
template<typename Mint>
struct ModTools {

    int MAX;
    vector<Mint> _fact, _factinv, inv;

    // nCrならn、nHrならn+rまで作る
    ModTools(int mx) : MAX(++mx) {
        _fact.resize(MAX);
        _factinv.resize(MAX);
        inv.resize(MAX);
        _fact[0] = _fact[1] = 1;
        rep(i, 2, MAX) {
            _fact[i] = _fact[i-1]*(Mint)i;
        }
        _factinv[MAX-1] = (Mint)1/_fact[MAX-1];
        rep(i, MAX-2, -1, -1) {
            _factinv[i] = _factinv[i+1]*(Mint)(i+1);
        }
        rep(i, MAX-1, 0, -1) {
            inv[i] = _factinv[i]*_fact[i-1];
        }
    }

    // 準備O(N)、操作O(1)でlogが乗らないmod除算
    Mint div(Mint a, int b) {
        return a*inv[b];
    }

    Mint fact(int x) {
        assert(x < MAX);
        return _fact[x];
    }

    Mint factinv(int x) {
        assert(x < MAX);
        return _factinv[x];
    }

    Mint nCr(int n, int r) {
        if (n < r or r < 0) return 0;
        r = min(r, n-r);
        Mint num = _fact[n];
        Mint den = _factinv[r] * _factinv[n-r];
        return num * den;
    }

    Mint nHr(int n, int r) {
        assert(r+n-1 < MAX);
        return nCr(r+n-1, r);
    }

    Mint nPr(int n, int r) {
        if (n < r or r < 0) return 0;
        return _fact[n] * _factinv[n-r];
    }

    // 二重階乗
    // 参考：https://ja.wikipedia.org/wiki/%E4%BA%8C%E9%87%8D%E9%9A%8E%E4%B9%97
    Mint double_factorial(int n) {
        if (n%2 == 0) {
            int k = n/2;
            return Mint(2).pow(k)*fact(k);
        } else {
            int k = (n+1)/2;
            return fact(2*k)/Mint(2).pow(k)/fact(k);
        }
    }
};
