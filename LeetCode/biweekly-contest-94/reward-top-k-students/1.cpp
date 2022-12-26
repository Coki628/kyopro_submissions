/*
・きっちり自力AC！
・数えてソート。(-score, id)で持つと楽。
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
    vector<int> topStudents(vector<string> &A, vector<string> &B,
                            vector<string> &S, vector<int> &ids, int K) {
        ll N = A.size();
        ll M = B.size();
        ll L = S.size();
        assert(S.size() == ids.size());

        set<string> pos(ALL(A)), neg(ALL(B));
        vector<pll> vec;
        rep(i, L) {
            ll cnt = 0;
            for (string s : split(S[i], ' ')) {
                if (pos.count(s)) {
                    cnt += 3;
                }
                if (neg.count(s)) {
                    cnt--;
                }
            }
            vec.eb(-cnt, ids[i]);
        }
        sort(ALL(vec));
        vector<int> ans(K);
        rep(i, K) {
            ans[i] = vec[i].second;
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
