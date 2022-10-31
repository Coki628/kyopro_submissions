/*
・なんとか自力AC！
・数列Aをmod Kすると、値の同じ所が対象の(同時にdestroyできる)場所になる。
　これで後ろからmapに詰めていけば、自分より右側で値が同じ個数は数えられるので、
　これがその位置を選んだ時にdestroyできる個数なので答えが求まる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
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
    int destroyTargets(vector<int>& A, int K) {
        ll N = A.size();
        sort(ALL(A));
        vector<ll> B(N);
        rep(i, N) {
            B[i] = A[i] % K;
        }
        map<ll, ll> mp;
        vector<ll> C(N);
        rep(i, N-1, -1, -1) {
            mp[B[i]]++;
            C[i] = mp[B[i]];
        }
        ll ans = -1;
        ll mx = 0;
        rep(i, N) {
            if (chmax(mx, C[i])) {
                ans = A[i];
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        // Solution sol;
        // auto res = sol.funcName();
        // print(res);
        return 0;
    }
#endif
