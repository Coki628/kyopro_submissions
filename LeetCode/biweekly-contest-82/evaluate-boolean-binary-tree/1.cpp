/*
・自力AC！
・再帰探索
・りとこでよく出るポインタ芸。
　関数が戻り値boolなのに何も返さないパターンがあり得るからコンパイルエラーしてた。
　エラー内容からそれが分かりにくい…。さすがC++。。assert(0)入れたら動いた。
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

#ifdef __LOCAL
    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
#endif

class Solution {
public:
    bool evaluateTree(TreeNode* root) {
        auto rec = [&](auto&& f, TreeNode* cur) -> bool {
            if (cur->val <= 1) {
                return cur->val;
            }
            if (cur->val == 2) {
                return f(f, cur->left) | f(f, cur->right);
            }
            if (cur->val == 3) {
                return f(f, cur->left) & f(f, cur->right);
            }
            assert(0);
        };
        return rec(rec, root);
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
