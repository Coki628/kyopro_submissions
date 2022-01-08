/*
・終了後自力AC！間に合わず…。
・全箇所について、スタンプ押せるかチェックをBIT2Dでやって、
　OKだったら2Dいもすにそのスタンプ範囲を記録、
　1つでもいもすが0の場所があったらNG。
　あとコーナーケースでスタンプがでかすぎる場合と1箇所も押さなくていい場合。
　りとこは落ちたテストケースがその場で見える仕様みたいで優しい。
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

#include "../../../_lib/cpp/_src/segment/BIT2D.hpp"

class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int hlen, int wlen) {
        ll H = grid.size();
        ll W = grid[0].size();
        BIT2D<int> bit2d(H, W);
        ll cnt = 0;
        rep(i, H) {
            rep(j, W) {
                if (grid[i][j]) {
                    bit2d.add(i, j, 1);
                    cnt++;
                }
            }
        }

        if (cnt == H*W) {
            return true;
        }
        if (hlen > H or wlen > W) {
            return false;
        }

        auto imos = list2d(H+1, W+1, 0LL);
        rep(i, H-hlen+1) {
            rep(j, W-wlen+1) {
                if (bit2d.query(i, j, i+hlen, j+wlen) == 0) {
                    imos[i][j]++;
                    imos[i+hlen][j]--;
                    imos[i][j+wlen]--;
                    imos[i+hlen][j+wlen]++;
                }
            }
        }
        rep(i, H+1) {
            rep(j, W) {
                imos[i][j+1] += imos[i][j];
            }
        }
        rep(j, W+1) {
            rep(i, H) {
                imos[i+1][j] += imos[i][j];
            }
        }

        bool ok = true;
        rep(i, H) {
            rep(j, W) {
                if (grid[i][j] == 0 and imos[i][j] == 0) {
                    ok = false;
                    break;
                }
            }
            if (not ok) break;
        }
        return ok;
    }
};

#ifdef __LOCAL
    int main() {
        vvi input = {{1,1,1,0},{0,0,0,1},{1,1,1,0},{1,1,0,0},{0,0,0,0},{0,1,0,1},{0,1,0,1},{1,1,1,0},{1,0,1,1},{0,0,0,1}};
        Solution sol;
        auto res = sol.possibleToStamp(input, 13, 6);
        print(res);
        return 0;
    }
#endif
