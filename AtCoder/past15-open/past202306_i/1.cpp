/*
・きっちり自力AC！
・GCDの最大化、約数列挙
・C[g] := GCDがgを取れるような値の個数
　的な配列を考えて、各値から自身の約数に向けて配っていく、とした。
　これでK以上の所を見ればいい。
　公式は倍数で見て、調和級数のループでやってた。
　自分も最初そっちでやろうとしたんだけど、
　なんか約数でのが考えやすいな、ってこっちにしたんだ。
　倍数でできるのであれば、調和級数は速いのでより良い。
　そっちの場合、後からK個あるか見る時に、
　自身の倍数に向かって貰いに行く、みたいな感じだった。
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

#include "numbers/Eratosthenes.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    ll M = 1000000;
    Eratosthenes era(M + 1);
    vector<ll> C(M + 1);
    for (auto a : A) {
        for (auto d : era.divisors(a)) {
            C[d]++;
        }
    }
    ll ans = 1;
    rep(i, 2, M + 1) {
        if (C[i] >= K) {
            chmax(ans, i);
        }
    }
    print(ans);
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
