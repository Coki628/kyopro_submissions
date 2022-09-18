/*
・きっちり自力AC！
・multisetでぶん殴った。
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
    int matchPlayersAndTrainers(vector<int>& A, vector<int>& B) {
        ll N = A.size();
        ll M = B.size();
        multiset<ll> se;
        rep(i, M) {
            se.insert(B[i]);
        }
        sort(ALL(A));
        ll ans = 0;
        rep(i, N) {
            auto itr = se.lower_bound(A[i]);
            if (itr == se.end()) break;
            ans++;
            se.erase(itr);
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
