/*
・なんとか自力AC！
・二分探索、累積和
・各区間の左端から始めるを全探索。
　にぶたんでどこまで届くか見て、全部覆う所は累積和、最後の端数は別計算。
・やることはそうなんだけど、末端の処理とかバグるから嫌になるやつ。
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

class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>> tiles, int K) {
        sort(ALL(tiles));
        ll N = tiles.size();
        vector<ll> L(N), R(N);
        rep(i, N) {
            L[i] = tiles[i][0] - 1;
            R[i] = tiles[i][1];
        }
        vector<ll> len(N), diff(N);
        rep(i, N-1) {
            diff[i] = L[i+1] - R[i];
        }
        rep(i, N) {
            len[i] = R[i] - L[i];
        }
        Accumulate<ll> acc(len);

        int ans = 0;
        rep(i, N) {
            ll j = bisect_left(R, L[i]+K);
            int sm = acc.query(i, j);
            int rest = max(K - (j > i ? diff[j-1]+R[j-1]-L[i] : 0), 0LL);
            chmax(ans, sm+min(rest, (j < N ? (int)len[j] : 0)));
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        // auto res = sol.maximumWhiteTiles({{1,5},{10,11},{12,18},{20,25},{30,32}}, 10);
        auto res = sol.maximumWhiteTiles({{10,11},{1,1}}, 2);
        print(res);
        return 0;
    }
#endif
