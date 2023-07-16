/*
・これは自力TLE。悪あがきの枝刈りも通じず。
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
    ll N, T, M;
    cin >> N >> T >> M;
    auto NG = listnd(N, N, 0);
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        NG[a][b] = 1;
        NG[b][a] = 1;
    }

    vvl teams(T);
    ll ans = 0;
    auto rec = [&](auto &&f, ll i) -> void {
        ll empcnt = 0;
        rep(j, T) {
            if (teams[j].empty()) {
                empcnt++;
            }
        }
        ll rest = N - i;
        if (empcnt > rest) {
            return;
        } else if (i == N) {
            ans++;
            return;
        }
        rep(j, T) {
            bool ok = true;
            for (ll k : teams[j]) {
                if (NG[i][k]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                teams[j].pb(i);
                f(f, i + 1);
                teams[j].pop_back();
            }
        }
    };
    rec(rec, 0);
    ans /= factorial<ll>(T);
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
