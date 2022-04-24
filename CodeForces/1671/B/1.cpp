/*
・なんとか自力AC。終了1分間前くらいにブザービート…。
・差分取って、間に向けて寄せるなら差分3が1つで他が1、
　要素に向けて寄せるなら差分2が2つで他が1。
　後者の2が2つが離れててもOKなのが見えてなくてやばかった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    if (N == 1) {
        YES();
        return;
    }

    vector<ll> B(N-1);
    rep(i, N-1) {
        B[i] = A[i+1] - A[i];
    }
    vector<ll> C(5);
    rep(i, N-1) {
        C[min(B[i], 4LL)]++;
    }
    if (C[4] > 0) {
        NO();
        return;
    }
    if (C[3] == 1 and C[2] == 0) {
        YES();
        return;
    }
    if (C[3] == 0 and C[2] <= 2) {
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
