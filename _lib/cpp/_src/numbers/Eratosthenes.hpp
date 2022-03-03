#include "../macros.hpp"

// エラトステネスの篩
struct Eratosthenes {

    int n;
    bool loglog;
    vector<bool> prime;
    vector<int> minfactor, cntfactor, cntdivisor, sumdivisor;
    vector<int> mobius;

    Eratosthenes(int n, bool loglog=true) : n(n), loglog(loglog) {
        prime.assign(n+1, true);
        minfactor.assign(n+1, 0);
        cntfactor.assign(n+1, 0);
        mobius.assign(n+1, 1);
        if (not loglog) {
            cntdivisor.assign(n+1, 1);
            sumdivisor.assign(n+1, 1);
        }
        prime[0] = prime[1] = false;
        minfactor[1] = 1;
        rep(i, 2, n+1) {
            if (not loglog) {
                for (int j=i; j<=n; j+=i) {
                    cntdivisor[j]++;
                    sumdivisor[j] += i;
                }
            }
            if (not prime[i]) continue;
            minfactor[i] = i;
            cntfactor[i]++;
            mobius[i] = -1;
            for (int j=i+i; j<=n; j+=i) {
                prime[j] = false;
                minfactor[j] = i;
                cntfactor[i]++;
                // iで2回以上割り切れるものを0に
                if (j/i%i == 0) {
                    mobius[j] = 0;
                } else {
                    mobius[j] = -mobius[j];
                }
            }
        }
    }

    bool is_prime(int x) {
        assert(x <= n);
        return prime[x];
    }

    // 高速素因数分解(osa_k法)
    vector<pii> factorize(int x) {
        assert(x <= n);
        vector<pii> res;
        while (x > 1) {
            int p = minfactor[x];
            int cnt = 0;
            while (minfactor[x] == p) {
                x /= p;
                cnt++;
            }
            res.pb({p, cnt});
        }
        return res;
    }

    // 高速約数列挙(未verify)
    vector<int> divisors(int n) {
        vector<int> res = {1};
        auto fact = factorize(n);
        for (auto [p, cnt] : fact) {
            int m = res.size();
            rep(i, m) {
                int v = 1;
                rep(j, cnt) {
                    v *= p;
                    res.pb(res[i] * v);
                }
            }
        }
        return res;
    }

    // 素因数の種類数(未verify)
    vector<int> get_cntfactor() {
        return cntfactor;
    }

    // 約数の個数(未verify)
    vector<int> get_cntdivisor() {
        assert(not loglog);
        return cntdivisor;
    }

    // 約数の総和(未verify)
    vector<int> get_sumdivisor() {
        assert(not loglog);
        return sumdivisor;
    }

    // メビウス関数
    vector<int> get_mobius() {
        return mobius;
    }
};
