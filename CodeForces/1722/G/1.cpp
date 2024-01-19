/*
・自力AC！
・ギャグ、乱択、XORの性質
・最後の1個以外適当に突っ込んで、最後の1個で帳尻合わせて0にする。
　たまに失敗して値が被ったりしそうだから、
　乱択使ってうまくいくまでやる。
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

#include "common/randrange.hpp"

void solve() {
    ll N;
    cin >> N;

    while (1) {
        vector<ll> ans;
        set<ll> se;
        ll cur = 0;
        rep(i, N - 1) {
            ll a = -1;
            while (1) {
                a = randrange(0, 1LL << 31);
                if (not se.count(a)) break;
            }
            ans.eb(a);
            se.insert(a);
            cur ^= a;
        }
        ll need = cur;
        if (se.count(need)) continue;
        ans.eb(need);
        print(ans);
        break;
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
