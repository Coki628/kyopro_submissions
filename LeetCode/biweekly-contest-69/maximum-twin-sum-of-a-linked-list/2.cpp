/*
・Linked List
・後学のためにC++でも通しておいた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#ifdef __LOCAL
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
#endif

class Solution {
public:
    int pairSum(ListNode* head) {
        vector<ll> V;
        while (head != NULL) {
            V.eb(head->val);
            head = head->next;
        }
        ll N = V.size();
        ll ans = 0;
        rep(i, N/2) {
            chmax(ans, V[i]+V[N-i-1]);
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        return 0;
    }
#endif
