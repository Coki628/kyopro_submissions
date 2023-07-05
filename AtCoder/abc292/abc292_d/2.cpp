/*
・ライブラリ整備：UnionFindに追加したマージ時追加処理関数の動作確認
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
    ll N, M;
    cin >> N >> M;
    UnionFind uf(N);
    vector<ll> ecnt(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        uf.merge(u, v, [&](ll r, ll ch) {
            if (r == -1) {
                ecnt[ch]++;
            } else {
                ecnt[r] += ecnt[ch] + 1;
            }
        });
    }

    for (auto r : uf.get_roots()) {
        if (uf.size(r) != ecnt[r]) {
            No();
            return;
        }
    }
    Yes();
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
