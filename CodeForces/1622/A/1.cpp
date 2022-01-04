/*
・きっちり自力AC！
・場合分け。必要なものが全てサンプルに含まれていたので優しい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_dist/base.hpp"

#include "../../../_lib/cpp/_dist/macros.hpp"

#include "../../../_lib/cpp/_dist/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    auto li = LIST(3);
    sort(ALL(li));
    
    if (li[0]+li[1] == li[2]) {
        YES();
        return;
    }
    if (li[0] == li[1] and li[2]%2 == 0) {
        YES();
        return;
    }
    if (li[2] == li[1] and li[0]%2 == 0) {
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
