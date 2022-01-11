/*
・きっちり自力AC！
・動かさない2つを固定すれば欲しい値は一意なので、正数かどうかとか約数かどうかとかチェック。
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

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;

    ll needa = b-(c-b);
    if (needa > 0 and needa%a == 0) {
        YES();
        return;
    }
    ll needb = (a+c)/2;
    if ((a+c)%2 == 0 and needb > 0 and needb%b == 0) {
        YES();
        return;
    }
    ll needc = b+(b-a);
    if (needc > 0 and needc%c == 0) {
        YES();
        return;
    }
    NO();
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
