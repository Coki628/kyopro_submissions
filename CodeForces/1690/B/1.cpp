/*
・きっちり自力AC。
・ちょっとめんどい。差分取って、B[i]が0の所以外で一意かつA>=Bで、
　B[i]が0の所はその一意になった値以下、ならOKみたいな。
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
    auto B = LIST(N);

    set<ll> se;
    vector<ll> tmp;
    rep(i, N) {
        if (B[i] == 0) {
            tmp.eb(A[i]-B[i]);
        } else {
            se.insert(A[i]-B[i]);
        }
    }
    if (se.size() > 1) {
        NO();
        return;
    } elif (se.size() == 0) {
        YES();
        return;
    }
    ll target = *se.begin();
    if (target < 0) {
        NO();
        return;
    }
    for (auto diff : tmp) {
        if (diff > target) {
            NO();
            return;
        }
    }
    YES();
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
