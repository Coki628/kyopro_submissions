/*
・きっちり自力AC！
・2乗効くので愚直に。地味にi,jの前後入れ替え忘れたりで1WA。。
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
    int captureForts(vector<int> &A) {
        int N = A.size();
        int ans = 0;
        rep(i, N) {
            rep(j, N) {
                if (i == j) continue;
                if (A[i] == 1 and A[j] == -1 or A[i] == -1 and A[j] == 1) {
                    bool ok = true;
                    rep(k, min(i, j) + 1, max(i, j)) {
                        if (A[k] != 0) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        chmax(ans, (int)abs(i - j) - 1);
                    }
                }
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
