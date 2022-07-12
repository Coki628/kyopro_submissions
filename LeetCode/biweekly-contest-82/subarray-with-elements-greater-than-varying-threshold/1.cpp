/*
参考：https://twitter.com/iiljj/status/1545801734584664064
・自力ならず。。
・二分探索、UFで区間マージ
・各iに対して、条件を満たす最小のkを前計算する所まではできたけど、
　その先が詰めれなかった。l固定でrをにぶたんしようとしたけどダメ。
　やってみると分かるんだけど、なんか両方増えるみたいな感じになってうまくいかない。
　多分、片方が増えて片方が減るみたいな状況だといけるんだけど。。
　こういうの考察段階でうまく判別していかないとなぁ…。
・siさんのツイートより、kでソートして小さい方から追加して、区間をマージしてく感じだった。
　確かにこれだとkを最小限に抑えながら区間長を伸ばしていけそう。
　実装はUF使った。なんか他にもやり方ありそうだけど、みんなどうやってるんだろか。
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
    int validSubarraySize(vector<int>& A, int threshold) {
        ll N = A.size();
        vector<ll> B(N);
        rep(i, N) {
            B[i] = bisearch_min(0, INF, [&](ll k) {
                return A[i] > threshold / k;
            });
        }
        
        UnionFind uf(N);
        vector<ll> L(N), R(N);
        rep(i, N) {
            L[i] = i;
            R[i] = i + 1;
        }
        auto merge = [&](ll i, ll j) {
            ll ri = uf.find(i);
            ll rj = uf.find(j);
            ll r = uf.merge(i, j);
            L[r] = min(L[ri], L[rj]);
            R[r] = max(R[ri], R[rj]);
        };
        vector<pll> BI;
        rep(i, N) {
            BI.eb(B[i], i);
        }
        sort(ALL(BI));
        vector<bool> added(N);
        for (auto [k, i] : BI) {
            if (i > 0 and added[i-1]) {
                merge(i-1, i);
            }
            if (i < N-1 and added[i+1]) {
                merge(i, i+1);
            }
            ll r = uf.find(i);
            ll len = R[r] - L[r];
            if (len >= k) {
                return len;
            }
            added[i] = true;
        }
        return -1;
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
