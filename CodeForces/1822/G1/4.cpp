/*
・参考：https://twitter.com/butsurizuki/status/1650543745321013248
・3つ組、真ん中固定、式変形、√まで全探索
・約数列挙を使わない方針。
　真ん中のAjを固定する。これならAi*b^2=Akより、
　b>1000はAkが10^6を超えてしまうので不可とみなせて、1000以下でbを全探索できる。
・こっちのが全然速いかと思ったら、意外とAi固定約数列挙のが速かった。これはAC1.95秒(制約4秒)。
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
    vector<ll> A(N);
    cin >> A;

    ll ans = 0;
    auto C = Counter(A);
    for (auto [k, v] : C) {
        ans += v * (v - 1) * (v - 2);
    }
    // Ajを固定
    // Ai*b^2 = Aj*b = Ak となる3つ組を探す
    // -> Ai*b = Aj = Ak/b
    for (auto [aj, cnt] : C) {
        // b>1000はAkが10^6を超えてしまうので不可
        rep(b, 2, 1001) {
            if (aj % b == 0 and C.count(aj / b) and C.count(aj * b)) {
                ll ai = aj / b;
                ll ak = aj * b;
                // Ai * Aj * Ak
                ans += C[ai] * cnt * C[ak];
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
