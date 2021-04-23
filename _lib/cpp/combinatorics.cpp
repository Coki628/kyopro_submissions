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


// 任意Mod数え上げnCr
struct AnyModTools {

    const int64_t mod;
    // 素数冪を (p, c) で表現したもの
    vector<pair<int64_t, int>> primes;
    // 素数冪 p^c の実際の値
    vector<int64_t> ppow;
    // 階乗を (x, y) 形式で表現したもの
    vector<vector<pair<int64_t, int>>> fact;

    AnyModTools(int64_t mod, int MX) : mod(mod) {
        create_composite_mod_table(++MX, mod);
    }

    void add(int64_t& a, int64_t b, int64_t mod) {
        a = (a+b) % mod;
    }
    void mul(int64_t& a, int64_t b, int64_t mod) {
        a = a*b % mod;
    }

    // 素因数分解をして素数冪ごとにfactを前計算：O(√M+N*(Mの素因数の種類数))
    void create_composite_mod_table(int N, int64_t M) {
        primes = factorize(M);
        int sz = primes.size();
        ppow.resize(sz, 1);
        fact.resize(sz);
        for(int pi=0; pi<sz; pi++){
            int64_t p = primes[pi].first, cnt = primes[pi].second;
            while(cnt--) ppow[pi] *= p;

            auto& f = fact[pi];
            f.resize(N+1);
            f[0] = {1, 0};
            for(int i=1; i<=N; i++){
                f[i] = f[i-1];
                int n = i;
                while(n%p == 0){
                    n /= p;
                    f[i].second++;
                }
                mul(f[i].first, n, ppow[pi]);
            }
        }
    }

    // 素因数毎の二項係数を計算
    int64_t comb_mod(int n, int k, int pi) {
        auto &a = fact[pi][n], &b = fact[pi][k], &c = fact[pi][n-k];
        int64_t p = primes[pi].first, cnt = primes[pi].second;
        int64_t pp = ppow[pi];
        int pw = a.second - b.second - c.second;
        if(pw >= cnt) return 0;

        int64_t v = a.first;
        mul(v, inv_mod(b.first, pp), pp);
        mul(v, inv_mod(c.first, pp), pp);
        while(pw--) mul(v, p, pp);
        return v;
    }

    // 二項係数nCrの計算：O(modの素因数の種類数)
    int64_t nCr(int n, int k) {
        int64_t res = 1;
        rep(i, primes.size()) {
            mul(res, comb_mod(n, k, i), mod);
        }
        return res;
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
