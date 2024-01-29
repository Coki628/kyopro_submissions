/*
・きっちり自力AC！
・交差する区間、BIT
・ぐっと睨むと交差する区間の有無の判定になる。
　(円環だけど平気なん？ってなるけど、いくつか手で試すと大丈夫そう、となる。)
　cf1914G2のコメントを参考に思い出しながら実装した。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<pll> RL;
    rep(i, N) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        if (a > b) swap(a, b);
        RL.eb(b, a);
    }

    N *= 2;
    sort(ALL(RL));
    BIT<ll> bit(N);
    for (auto [r, l] : RL) {
        bit.add(l, 1);
    }
    for (auto [r, l] : RL) {
        if (bit.query(l + 1, r)) {
            Yes();
            return;
        }
        bit.add(l, -1);
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
