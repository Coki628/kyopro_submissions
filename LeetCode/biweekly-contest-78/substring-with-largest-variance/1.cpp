/*
参考：https://ark4rk.hatenablog.com/entry/2018/01/08/002508
・自力ならず。。
・最大部分配列問題、分割統治法
・前提として、文字種の全ペアを(最小出現数, 最大出現数)として全探索する。
　そもそもこれが出なかったからね…。で、そしたら各ペアは、-1,+1に変換した列で、
　最大部分配列問題ってのをやることになる。ようは連続部分列の値の最大化。
　調べてたら分割統治法が紹介されていたので、とりあえずやってみる。
・なんかTLでsiさんがlog付きでTLEになるって言ってたのはこれのことか…。
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
    int largestVariance(string S) {
        ll N = S.size();
        vector<ll> A(N);
        rep(i, N) {
            A[i] = S[i] - 'a';
        }
        ll M = 26;
        vector<int> B(N);
        int ans = 0;
        rep(c1, M) {
            rep(c2, M) {
                if (c1 == c2) continue;
                rep(i, N) {
                    if (A[i] == c1) {
                        B[i] = -1;
                    } elif (A[i] == c2) {
                        B[i] = 1;
                    } else {
                        B[i] = 0;
                    }
                }
                auto rec = [&](auto&& f, ll l, ll r) -> array<array<array<int, 2>, 2>, 2> {
                    // res[i][j][k] := 現在の最大値が、左端を使っているかi=0/1,右端を使っているかj=0/1,c1が出現済かk=0/1
                    array<array<array<int, 2>, 2>, 2> res;
                    rep(i, 2) rep(j, 2) rep(k, 2) res[i][j][k] = -MOD;
                    ll len = r - l;
                    if (len == 1) {
                        res[1][1][B[l] == -1] = B[l];
                        return res;
                    }
                    ll m = (l+r) / 2;
                    auto L = f(f, l, m);
                    auto R = f(f, m, r);
                    rep(i1, 2) {
                        rep(j1, 2) {
                            rep(k1, 2) {
                                rep(i2, 2) {
                                    rep(j2, 2) {
                                        rep(k2, 2) {
                                            // 左の右側と右の左側が残ってるなら合わせられる
                                            if (j1 == 1 and i2 == 1) {
                                                chmax(res[i1][j2][k1|k2], L[i1][j1][k1] + R[i2][j2][k2]);
                                            } else {
                                                // そうでなければ、どちらかの最大値を採用
                                                chmax(res[i1][0][k1], L[i1][j1][k1]);
                                                chmax(res[0][j2][k2], R[i2][j2][k2]);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    return res;
                };
                auto res = rec(rec, 0, N);
                rep(i, 2) {
                    rep(j, 2) {
                        chmax(ans, res[i][j][1]);
                    }
                }
            }
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.largestVariance("aababbb");
        print(res);
        return 0;
    }
#endif
