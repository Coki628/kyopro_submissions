/*
・なんとか自力AC！
・WM、range_freq、二分探索
・WMのrange_freqでにぶたんして個数が2以上になる最小位置
　ってやったらTLE…このlog2個は重いか。がしかし他に良い案が出ないので、
　非本質枝刈りで最悪ケースだけ対応したら通っちゃった…
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

#include "datastructure/WaveletMatrix.hpp"

class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& A) {
        ll N = A.size();
        Compress<int> cp(A);
        rep(i, N) {
            A[i] = cp[A[i]];
        }
        int MX = max(A);
        WaveletMatrix<int> wm(A);
        vector<int> ans(N, -1);
        rep(i, N) {
            if (wm.range_freq(i+1, N, A[i]+1, MX+1) < 2) {
                continue;
            }
            if (i+2 < N and A[i+1] > A[i] and A[i+2] > A[i]) {
                ans[i] = cp.unzip(A[i+2]);
                continue;
            }
            ll j = bisearch_min(i, N, [&](ll x) {
                return wm.range_freq(i+1, x+1, A[i]+1, MX+1) >= 2;
            });
            if (j < N) {
                ans[i] = cp.unzip(A[j]);
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
