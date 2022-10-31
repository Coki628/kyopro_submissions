/*
参考：https://twitter.com/iiljj/status/1586387386933514240
・siさんのツイートより。これは思いつくべきだったな。
・平面走査、BITにぶたん
・大きい方からソートしといて、indexでBITに詰めて、自分の2つ先の値の位置を見る。
　同値のindexは拾いたくないので、値毎に隣接リストに詰めておいて、
　同じ値のチェックが全て終わってからそれらのindexをまとめてBITに詰める。
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
    vector<int> secondGreaterElement(vector<int>& A) {
        ll N = A.size();
        Compress<int> cp(A);
        rep(i, N) {
            A[i] = cp[A[i]];
        }
        int M = cp.size();

        vvi adj(M);
        rep(i, N) {
            adj[A[i]].eb(i);
        }
        BIT<int> bit(N);
        vector<int> ans(N, -1);
        rep(i, M-1, -1, -1) {
            for (auto j : adj[i]) {
                ll k = bit.bisearch_fore(j, N-1, 2);
                if (k != -1) {
                    ans[j] = cp.unzip(A[k]);
                }
            }
            for (auto j : adj[i]) {
                bit.add(j, 1);
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
