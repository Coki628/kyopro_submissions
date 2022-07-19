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
    ll N, x, y, z;
    cin >> N >> x >> y >> z;
    auto A = LIST(N);
    auto B = LIST(N);
    vector<pii> AI, BI, ABI;
    rep(i, N) {
        AI.eb(-A[i], i);
        BI.eb(-B[i], i);
        ABI.eb(-A[i]-B[i], i);
    }

    sort(ALL(AI));
    sort(ALL(BI));
    sort(ALL(ABI));
    vector<bool> done(N);
    vector<ll> ans;
    ll cnt = 0;
    sort(ALL(AI));
    for (auto [a, i] : AI) {
        if (cnt < x) {
            ans.eb(i+1);
            done[i] = true;
            cnt++;
        }
        if (cnt == x) break;
    }
    cnt = 0;
    for (auto [b, i] : BI) {
        if (cnt < y and not done[i]) {
            ans.eb(i+1);
            done[i] = true;
            cnt++;
        }
        if (cnt == y) break;
    }
    cnt = 0;
    for (auto [ab, i] : ABI) {
        if (cnt < z and not done[i]) {
            ans.eb(i+1);
            done[i] = true;
            cnt++;
        }
        if (cnt == z) break;
    }
    sort(ALL(ans));
    print(ans, '\n');
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
