/*
・終了後ほぼ自力AC！
・決め打ちにぶたんin決め打ちにぶたん
・決め打ちにぶたん内で決め打ちにぶたんした。
　log*logが30*15=450くらいなので、この内側で10万が回っても
　何とかなりそうな気がするんだけどなんともならなかった。
　ソートのlogも乗ってるからかも。。
・公式解見てもだいたいこの方針だったので、
　最深部にソートのlogが乗らないように調整したら無事AC。0.92秒。(TL3秒)
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), B(N);
    rep(i, 1, N) {
        cin >> A[i];
    }
    cin >> B;

    auto sortedA = sorted(A);
    auto sortedB = sorted(B);
    auto func = [&](ll x) {
        auto cura = sortedA;
        auto curb = sortedB;
        reverse(ALL(curb));
        rep(_, x) {
            cura.pop_back();
            curb.pop_back();
        }
        reverse(ALL(curb));
        rep(i, cura.size()) {
            if (cura[i] >= curb[i]) {
                return false;
            }
        }
        return true;
    };
    ll m = 1, ans = 0;
    while (m <= M) {
        A[0] = m;
        sortedA = sorted(A);
        ll curval = bisearch_min(-1, N, func);
        ll nxm = bisearch_min(m, M + 1, [&](ll mm) {
            A[0] = mm;
            sortedA = sorted(A);
            ll nxval = bisearch_min(-1, N, func);
            return nxval > curval;
        });
        ans += (nxm - m) * curval;
        m = nxm;
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
