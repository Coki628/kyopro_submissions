/*
・きっちり自力AC！
・優先度付きキュー
・プリキューに突っ込んで大きいのから貪欲にやる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

class Solution {
public:
    int halveArray(vector<int>& A) {
        ll N = A.size();

        priority_queue<ld, vector<ld>> que;
        ld total = 0;
        rep(i, N) {
            que.push(A[i]);
            total += A[i];
        }
        ld sm = total;
        int ans = 0;
        while (que.size() and sm-EPS > total/2) {
            ld cur = que.top(); que.pop();
            sm -= cur;
            cur /= 2;
            sm += cur;
            que.push(cur);
            ans++;
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
