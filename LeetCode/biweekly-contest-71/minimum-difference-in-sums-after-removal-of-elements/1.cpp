/*
・自力AC！まあ既出なんだけど。。
・BIT2本で個数と総和
・abc062_dだし、道場のset_e_3_2で最近やったからよく覚えてた。能書きはそっち見て。
・ほぼそのまま貼って、座圧パート外して、最大化を最小化にするだけ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"

#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "template.hpp"

class Solution {
public:
    long long minimumDifference(vector<int>& A) {
        ll N = A.size()/3;
        ll M = max(A)+1;
        BIT<ll> bitlcnt(M), bitlsm(M), bitrcnt(M), bitrsm(M);
        rep(i, N) {
            bitlcnt.add(A[i], 1);
            bitlsm.add(A[i], A[i]);
        }
        rep(i, N, N*3) {
            bitrcnt.add(A[i], 1);
            bitrsm.add(A[i], A[i]);
        }

        auto calc = [&]() -> ll {
            // 左側小さい方からN個
            ll j = bitlcnt.bisearch_fore(0, M-1, N);
            assert(j != -1);
            ll lcnt = bitlcnt.query(0, j+1);
            ll lexeed = lcnt-N;
            ll lsm = bitlsm.query(0, j+1)-j*lexeed;
            // 右側大きい方からN個
            ll i = bitrcnt.bisearch_back(0, M-1, N);
            assert(i != -1);
            ll rcnt = bitrcnt.query(i, M);
            ll rexeed = rcnt-N;
            ll rsm = bitrsm.query(i, M)-i*rexeed;
            return lsm-rsm;
        };
        ll ans = calc();
        rep(i, N, N*2) {
            bitrcnt.add(A[i], -1);
            bitrsm.add(A[i], -A[i]);
            bitlcnt.add(A[i], 1);
            bitlsm.add(A[i], A[i]);
            chmin(ans, calc());
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        return 0;
    }
#endif
