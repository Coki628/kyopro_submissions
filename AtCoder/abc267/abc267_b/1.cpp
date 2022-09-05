/*
・Bだけど実装方針とか結構悩む感じのやつ。
　列の配列作ってその中に立ってるピンの情報入れた。
　どのピンが何列目にあるかは筋肉場合分け…。
　間が空いてるかの判定は制約小さいし3重ループ回した。
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

void solve() {
    bool has1 = false;
    vector<ll> cols(7);
    rep(i, 10) {
        char c;
        cin >> c;
        ll a = toint(c);
        if (i == 0) {
            has1 = a;
        }
        if (i == 6) {
            cols[0] |= a;
        } elif (i == 3) {
            cols[1] |= a;
        } elif (i == 1 or i == 7) {
            cols[2] |= a;
        } elif (i == 0 or i == 4) {
            cols[3] |= a;
        } elif (i == 8 or i == 2) {
            cols[4] |= a;
        } elif (i == 5) {
            cols[5] |= a;
        } elif (i == 9) {
            cols[6] |= a;
        }
    }

    if (not has1) {
        rep(l, 7) {
            rep(r, 7) {
                rep(m, l+1, r) {
                    if (cols[l] and not cols[m] and cols[r]) {
                        Yes();
                        return;
                    }
                }
            }
        }
    }
    No();
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
