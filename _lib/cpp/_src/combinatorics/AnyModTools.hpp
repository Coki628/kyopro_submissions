#include "../base.hpp"
#include "../numbers/extgcd.hpp"

// 参考：https://betrue12.hateblo.jp/entry/2020/02/23/173513
// 任意Mod数え上げ演算ツール
struct AnyModTools {

    const int64_t MOD;
    // 素数冪を (p, c) で表現したもの
    vector<pair<int64_t, int>> primes;
    // 素数冪 p^c の実際の値
    vector<int64_t> ppow;
    // 階乗を (x, y) 形式で表現したもの
    vector<vector<pair<int64_t, int>>> fact;

    AnyModTools(int64_t MOD, int MX) : MOD(MOD) {
        create_composite_mod_table(++MX, MOD);
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
    int64_t inv_mod(int64_t a, int64_t mod) {
        int64_t x, y;
        extgcd(a, mod, x, y);
        return (MOD + x%mod) % mod;
    }

    // 素因数分解をして素数冪ごとにfactを前計算：O(√M+N*(Mの素因数の種類数))
    void create_composite_mod_table(int N, int64_t MOD) {
        primes = factorize(MOD);
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

    pair<int64_t, int64_t> crt(int64_t b1, int64_t m1, int64_t b2, int64_t m2){
        int64_t p, q;
        int64_t d = extgcd(m1, m2, p, q);
        if((b2-b1) % d != 0) return {-1, -1};
        int64_t m = m1 * (m2/d);
        int64_t tmp = (b2 - b1) / d * p % (m2/d);
        int64_t r = ((b1 + m1 * tmp) % m + m) % m;
        return make_pair(r, m);
    }

    // 二項係数nCrの計算：O(modの素因数の種類数*中国剰余定理)
    int64_t nCr(int n, int k) {
        if (n < k or k < 0) return 0;
        pair<int64_t, int64_t> res = {0, 1};
        for (int pi=0; pi<primes.size(); pi++) {
            res = crt(res.first, res.second, comb_mod(n, k, pi), ppow[pi]);
        }
        return res.first;
    }
};
