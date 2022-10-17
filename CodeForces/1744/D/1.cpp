/*
・きっちり自力AC！
・素因数で見る
・ようは素因数2の個数だけが大事なので、各位置で素因数2が元々何個あるかと、何個増やせるかを見る。
　増やす必要があるなら、大きい方から貪欲に使えばいい。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<ll> vec;
    ll sm2 = 0;
    rep(i, N) {
        while (A[i]%2 == 0) {
            sm2++;
            A[i] /= 2;
        }
        ll j = i + 1;
        ll cnt2 = 0;
        while (j%2 == 0) {
            cnt2++;
            j /= 2;
        }
        if (cnt2) {
            vec.eb(cnt2);
        }
    }

    if (sm2 >= N) {
        print(0);
        return;
    }

    sort(vec.rbegin(), vec.rend());
    ll ans = 0;
    for (auto cnt2 : vec) {
        ans++;
        sm2 += cnt2;
        if (sm2 >= N) {
            print(ans);
            return;
        }
    }
    print(-1);
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
