/*
参考：https://ark4rk.hatenablog.com/entry/2018/01/08/002508
・最大部分配列問題、分割統治法
・(連続)部分列の和の最大値をO(NlogN)でやるというもの。
　詳しいやり方書いてなかったけど、多分こんな感じだろう。(証明AC)
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

void solve() {
    while (1) {
        ll N;
        cin >> N;
        if (N == 0) break;
        auto A = LIST(N);

        auto rec = [&](auto&& f, ll l, ll r) -> array<array<ll, 2>, 2> {
            // res[i][j] := 現在の最大値が、左端を使っているかi=0/1,右端を使っているかj=0/1
            array<array<ll, 2>, 2> res;
            rep(i, 2) rep(j, 2) res[i][j] = -INF;
            ll len = r - l;
            if (len == 1) {
                res[1][1] = A[l];
                return res;
            }
            ll m = (l+r) / 2;
            auto L = f(f, l, m);
            auto R = f(f, m, r);
            rep(i1, 2) {
                rep(j1, 2) {
                    rep(i2, 2) {
                        rep(j2, 2) {
                            // 左の右側と右の左側が残ってるなら合わせられる
                            if (j1 == 1 and i2 == 1) {
                                chmax(res[i1][j2], L[i1][j1] + R[i2][j2]);
                            } else {
                                // そうでなければ、どちらかの最大値を採用
                                chmax(res[i1][0], L[i1][j1]);
                                chmax(res[0][j2], R[i2][j2]);
                            }
                        }
                    }
                }
            }
            return res;
        };
        auto res = rec(rec, 0, N);
        ll ans = -INF;
        rep(i, 2) {
            rep(j, 2) {
                chmax(ans, res[i][j]);
            }
        }
        print(ans);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
