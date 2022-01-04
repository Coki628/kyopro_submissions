/*
・自力AC！
・両端に何を使うかだけが問題。基本的には左端最小、右端最大の2つを使えばいいが、
　1つで両側をカバーできるやつがあると、コスト計算が変わるのでややこしくなる。
　両端に別のを使う時と同じのを使う時を完全に分けて管理したら通った。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;

    ll mn = INF, mx = -INF;
    ll mn2 = INF, mx2 = -INF;
    ll costl = 0, costr = 0, cost2 = 0;
    rep(i, N) {
        ll l, r, c;
        cin >> l >> r >> c;

        if (l < mn) {
            mn = l;
            costl = c;
        } elif (l == mn and c < costl) {
            costl = c;
        }
        if (r > mx) {
            mx = r;
            costr = c;
        } elif (r == mx and c < costr) {
            costr = c;
        }
        if (l < mn2 and r >= mx2 or l <= mn2 and r > mx2) {
            mn2 = l;
            mx2 = r;
            cost2 = c;
        } elif (l == mn2 and r == mx2 and c < cost2) {
            cost2 = c;
        }

        if (mn == mn2 and mx == mx2) {
            print(min(costl+costr, cost2));
        } else {
            print(costl+costr);
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
