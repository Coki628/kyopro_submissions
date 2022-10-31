/*
・きっちり自力AC。りとこQ1にしては重め。
・mapで、作られる数列をキー、元文字列のリストを値に持って、値の配列が長さ1の所が答えってやった。
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
    string oddString(vector<string>& words) {
        ll N = words.size();
        map<vector<ll>, vector<string>> mp;
        rep(i, N) {
            ll m = words[i].size();
            vector<ll> vec(m);
            rep(j, m-1) {
                vec[j] = words[i][j+1] - words[i][j];
            }
            mp[vec].eb(words[i]);
        }

        for (auto [k, v] : mp) {
            if (v.size() == 1) {
                return v[0];
            }
        }
        assert(0);
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
