#include "../base.hpp"
#include "../numbers/inv_mod.hpp"

// 参考：https://betrue12.hateblo.jp/entry/2020/02/23/173513
// 任意Mod数え上げ演算ツール
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

    vector<pair<int64_t, int>> factorize(int64_t n) {
        vector<pair<int64_t, int>> ret;
        for(int64_t i=2; i*i<=n; i++) {
            int cnt = 0;
            while(n % i == 0) {
                n /= i;
                cnt++;
            }
            if(cnt) ret.emplace_back(i, cnt);
        }
        if(n > 1) ret.emplace_back(n, 1);
        return ret;
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
