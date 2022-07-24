/*
・これはTLE。。
・鳩の巣みを感じて愚直に全列挙して前から見てけば当たるだろってやったら普通にTLE。。
　分からんかった…。
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
    int shortestSequence(vector<int>& rolls, int k) {
        ll N = rolls.size();
        rep(i, N) rolls[i]--;
        ll x = 1;
        while (1) {
            vvl V;
            vector<ll> cur;
            auto rec = [&](auto&& f, ll d) -> void {
                if (d == x) {
                    V.eb(cur);
                    return;
                }
                rep(i, k) {
                    cur.eb(i);
                    f(f, d+1);
                    cur.pop_back();
                }
            };
            rec(rec, 0);
            bool okok = true;
            for (auto& cur : V) {
                ll j = 0;
                bool ok = false;
                rep(i, N) {
                    if (cur[j] == rolls[i]) {
                        j++;
                        if (j == x) {
                            ok = true;
                            break;
                        }
                    }
                }
                if (not ok) {
                    okok = false;
                    break;
                }
            }
            if (not okok) {
                return x;
            }
            x++;
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
