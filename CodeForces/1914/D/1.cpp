/*
・きっちり自力AC！
・3つ組、賢く全探索
・添字の重複を許さずに最善を探す訳だが、どんなに被っても3つなので、
　良い方から3つだけ残してそこだけ全探索する。
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
    vector<ll> A(N), B(N), C(N);
    cin >> A >> B >> C;

    vector<pll> AI, BI, CI;
    rep(i, N) {
        AI.eb(A[i], i);
        BI.eb(B[i], i);
        CI.eb(C[i], i);
    }
    sort(AI.rbegin(), AI.rend());
    sort(BI.rbegin(), BI.rend());
    sort(CI.rbegin(), CI.rend());
    ll ans = -INF;
    rep(i, 3) {
        auto [a, ai] = AI[i];
        rep(j, 3) {
            auto [b, bi] = BI[j];
            if (ai == bi) continue;
            rep(k, 3) {
                auto [c, ci] = CI[k];
                if (ai == ci or bi == ci) continue;
                chmax(ans, a + b + c);
            }
        }
    }
    print(ans);
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
