#pragma once
#include "../macros.hpp"

// Mod数え上げ演算ツール
template<typename Mint>
struct ModTools {

    int MAX;
    vector<Mint> fact, factinv, inv;

    ModTools() {};

    ModTools(int mx) {
        build(mx);
    }

    void build(int mx) {
        // nCrならn、nHrならn+rまで作る
        MAX = ++mx;
        fact.resize(MAX);
        factinv.resize(MAX);
        inv.resize(MAX);
        fact[0] = fact[1] = 1;
        rep(i, 2, MAX) {
            fact[i] = fact[i-1]*(Mint)i;
        }
        factinv[MAX-1] = (Mint)1/fact[MAX-1];
        rep(i, MAX-2, -1, -1) {
            factinv[i] = factinv[i+1]*(Mint)(i+1);
        }
        rep(i, MAX-1, 0, -1) {
            inv[i] = factinv[i]*fact[i-1];
        }
    }

    // 準備O(N)、操作O(1)でlogが乗らないmod除算
    Mint div(Mint a, int b) {
        return a*inv[b];
    }

    Mint factorial(int x) {
        return fact[x];
    }

    Mint inverse(int x) {
        return factinv[x];
    }

    Mint nCr(int n, int r) {
        if (n < r or r < 0) return 0;
        r = min(r, n-r);
        Mint num = fact[n];
        Mint den = factinv[r] * factinv[n-r];
        return num * den;
    }

    Mint nHr(int n, int r) {
        assert(r+n-1 < MAX);
        return nCr(r+n-1, r);
    }

    Mint nPr(int n, int r) {
        if (n < r or r < 0) return 0;
        return fact[n] * factinv[n-r];
    }
};
