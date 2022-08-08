/*
・きっちり自力AC！
・集計して持ち替える。2つに分かれてる意味はよく分からない。
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
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& A, vector<vector<int>>& B) {
        HashMap<int, int> C;
        rep(i, A.size()) {
            C[A[i][0]] += A[i][1];
        }
        rep(i, B.size()) {
            C[B[i][0]] += B[i][1];
        }
        vvi ans;
        for (auto [k, v] : C) {
            ans.pb({k, v});
        }
        sort(ALL(ans));
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
