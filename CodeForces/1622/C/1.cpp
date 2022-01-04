/*
・これは実験用。凸っぽいと思ったけどその確認に。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_dist/base.hpp"

#include "../../../_lib/cpp/_dist/macros.hpp"

#include "../../../_lib/cpp/_dist/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    auto check = [&](vector<ll> cur, ll x) {
        ll cnt = 0;
        ll sm = sum(cur);
        if (sm <= K) {
            debug(x);
            debug(cnt);
            return;
        }
        rep(_, x) {
            cur[0]--;
            sm--;
            cnt++;
            if (sm <= K) {
                debug(x);
                debug(cnt);
                return;
            }
        }
        rep(i, N-1, 0, -1) {
            sm -= abs(cur[0]-cur[i]);
            cnt++;
            if (sm <= K) {
                debug(x);
                debug(cnt);
                return;
            }
        }
        cnt = INF;
        debug(x);
        debug(cnt);
    };
    sort(ALL(A));
    rep(x, 10) {
        check(A, x);
    }
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
