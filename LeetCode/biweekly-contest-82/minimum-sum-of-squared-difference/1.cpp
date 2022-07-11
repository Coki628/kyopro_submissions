/*
・自力AC！
・二分探索、優先度付きキュー
・A,Bの差分の列にして、k1k2も一緒にしていい。
　一括でどこまで減らせるかにぶたんした後、
　残りをプリキューに詰めて使い切ったけど、何かうまくやればもっと簡単にできそう…。
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
    long long minSumSquareDiff(vector<int>& A, vector<int>& B, int k1, int k2) {
        ll N = A.size();
        ll K = k1 + k2;
        vector<ll> D(N);
        rep(i, N) {
            D[i] = abs(A[i]-B[i]);
        }
        sort(D.rbegin(), D.rend());

        ll res = bisearch_min(-1, MOD, [&](ll m) {
            ll cnt = 0;
            rep(i, N) {
                ll use = max(D[i]-m, 0LL);
                cnt += use;
            }
            return cnt <= K;
        });
        rep(i, N) {
            ll use = max(D[i]-res, 0LL);
            D[i] -= use;
            K -= use;
        }
        if (sum(D) == 0) {
            return 0;
        }
        priority_queue<ll, vector<ll>> que;
        rep(i, N) {
            que.push(D[i]);
        }
        rep(_, K) {
            auto cur = que.top(); que.pop();
            if (cur > 0) cur--;
            que.push(cur);
        }
        ll ans = 0;
        rep(_, N) {
            auto cur = que.top(); que.pop();
            ans += pow(cur, 2);
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
