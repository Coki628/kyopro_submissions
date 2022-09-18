/*
・きっちり自力AC！
・尺取り法、ビット毎に見る
・リバースして、右端を軸にして左端を引っ張る尺取りみたいにした。ビット毎に個数集計しながら。
・でもこれ多分区間orはセグ木とかに乗せればもっと楽にやれたっぽいね…。
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
    vector<int> smallestSubarrays(vector<int>& A) {
        ll N = A.size();
        reverse(ALL(A));
        ll L = 30;
        vector<int> C(L), ans(N);
        ll l = 0;
        rep(r, N) {
            rep(i, L) {
                if (A[r]>>i & 1) {
                    C[i]++;
                }
            }
            while (l < r) {
                bool ok = true;
                rep(i, L) {
                    if (A[l]>>i & 1) {
                        // 最後の1個ならここは外せない
                        if (C[i] == 1) {
                            ok = false;
                            break;
                        }
                    }
                }
                if (ok) {
                    rep(i, L) {
                        if (A[l]>>i & 1) {
                            C[i]--;
                        }
                    }
                    l++;
                } else {
                    break;
                }
            }
            ans[r] = r - l + 1;
        }
        reverse(ALL(ans));
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
