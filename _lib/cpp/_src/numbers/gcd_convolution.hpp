#include "../base.hpp"

// 添字GCD畳み込み(計算量：O(NloglogN))
template<typename T>
vector<T> gcd_convolution(vector<T> F, vector<T> G) {
    int N = max(F.size(), G.size());

    // 高速ゼータ変換
    auto fast_zeta = [&](vector<T> &a) {
        int n = a.size();
        vector<bool> sieve(n, false);
        for (int p = 2; p < n; ++p) {
            if (sieve[p]) continue;
            for (int k=(n-1)/p; k>=0; k--) sieve[k*p]=true, a[k]+=a[k*p];
        }
    };
    // 高速メビウス変換
    auto fast_mobius = [&](vector<T> &a) {
        int n = a.size();
        vector<bool> sieve(n, false);
        for (int p = 2; p < n; ++p) {
            if (sieve[p]) continue;
            else {
                for (int k=0; k*p<n; k++) sieve[k*p]=true, a[k]-=a[k*p];
            }
        }
    };

    fast_zeta(F);
    fast_zeta(G);

    vector<T> H(N);
    rep(i, min(F.size(), G.size())) {
        H[i] = F[i]*G[i];
    }

    fast_mobius(H);

    return H;
}
