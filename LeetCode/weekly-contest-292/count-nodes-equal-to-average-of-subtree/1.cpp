/*
・きっちり自力AC！
・木、DFS
・りとこはこういうポインタ持つ系たまに出るよね。
・基本的には木DPみたいに進める。
　でも値valが一意じゃなかったのでキーにできず、戻り値に状態持たせた。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#ifdef __LOCAL
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
    int averageOfSubtree(TreeNode* root) {
        int ans = 0;
        auto dfs = [&](auto&& f, TreeNode* u) -> pll {
            ll sz = 1;
            ll sm = u->val;
            if (u->left != NULL) {
                auto res = f(f, u->left);
                sz += res.first;
                sm += res.second;
            }
            if (u->right != NULL) {
                auto res = f(f, u->right);
                sz += res.first;
                sm += res.second;
            }
            if (sm / sz == u->val) {
                ans++;
            }
            return {sz, sm};
        };
        dfs(dfs, root);
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
