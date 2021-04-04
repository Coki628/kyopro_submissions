/*
・ライブラリ：数え上げ
*/

#include "_tpl.cpp"


// Mod数え上げnCr
struct ModTools {

    int MAX;
    const int MOD;
    vector<mint> fact, inv;

    ModTools(int MOD) : MOD(MOD) {};

    ModTools(int MOD, int mx) : MOD(MOD) {
        build(mx);
    }

    void build(int mx) {
        // nCrならn、nHrならn+rまで作る
        MAX = ++mx;
        fact.resize(MAX);
        inv.resize(MAX);
        fact[0] = fact[1] = 1;
        rep(i, 2, MAX) {
            fact[i] = fact[i-1] * i;
        }
        inv[MAX-1] = fact[MAX-1].inverse();
        rep(i, MAX-2, -1, -1) {
            inv[i] = inv[i+1] * (i+1);
        }
    }

    mint nCr(int n, int r) {
        if (n < r) return 0;
        r = min(r, n-r);
        mint num = fact[n];
        mint den = inv[r] * inv[n-r];
        return num * den;
    }

    mint nHr(int n, int r) {
        return nCr(r+n-1, r);
    }
};


// 順列列挙
template<typename T>
vector<vector<T>> permutations(vector<T> &A, int N=-1) {

    if (N == -1) N = A.size();
    int M = A.size();
    vector<vector<T>> comb;
    rep(bit, 0, 1<<M) {
        if (popcount(bit) != N) continue;
        vector<T> res;
        rep(i, 0, M) {
            if (bit>>i & 1) {
                res.pb(A[i]);
            }
        }
        comb.pb(res);
    }

    vector<vector<T>> res;
    for (auto &perm : comb) {
        sort(ALL(perm));
        do {
            res.pb(perm);
        } while (next_permutation(ALL(perm)));
    }
    return res;
}


// 階乗(modなし)
template<typename T>
T factorial(T x) {
    T res = 1;
    for (T i=1; i<=x; i++) res *= i;
    return res;
}
