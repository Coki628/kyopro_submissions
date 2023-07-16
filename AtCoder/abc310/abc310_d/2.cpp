/*
・自力ならず。
・再帰全探索、バックトラック
・TLEコード書く前にほぼこのコード書いたんだけど、
　答え合わなくて方針変えたんだよな。
　原因は参照渡ししてるとこが(多分)再帰との兼ね合いで壊れるみたい。
　普通に添字で参照する形に直したら通った…。
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

    vvl teams;
    ll ans = 0;
    auto rec = [&](auto&& f, ll i) -> void {
        if (i == N) {
            if (teams.size() == T) {
                ans++;
            }
            return;
        }
        // この参照渡しだとなんかバグる
        // for (auto& team : teams) {
        rep(t, teams.size()) {
            bool ok = true;
            for (ll j : teams[t]) {
                if (NG[i][j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                teams[t].pb(i);
                f(f, i + 1);
                teams[t].pop_back();
            }
        }
        if (teams.size() < T) {
            teams.pb({i});
            f(f, i + 1);
            teams.pop_back();
        }
    };
    rec(rec, 0);
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
