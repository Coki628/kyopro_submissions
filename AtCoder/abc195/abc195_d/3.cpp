/*
・ぱっと見想定解分からないけどフローできそうだったのでやった。
・最小費用流、重み付き二部マッチング
・最大化で下駄履かせる時のやり方がゴタゴタしてしまって手際よくできなかったのはよくない。
　過去の類題を参考にしようとしたらこの問題が出てきた…。
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

#include "acl/mincostflow.hpp"

void solve() {
    ll N, M, Q;
    cin >> N >> M >> Q;
    vector<ll> W(N), V(N);
    rep(i, N) {
        cin >> W[i] >> V[i];
    }
    vector<ll> X(M);
    cin >> X;

    rep(_, Q) {
        ll l, r;
        cin >> l >> r;
        l--;

        atcoder::mcf_graph<ll, ll> mcf(M + N + 2);
        ll s = M + N;
        ll t = M + N + 1;
        ll mx = max(V);
        rep(j, N) {
            mcf.add_edge(M + j, t, 1, 0);
        }
        rep(i, M) {
            if (l <= i and i < r) continue;
            mcf.add_edge(s, i, 1, 0);
            rep(j, N) {
                if (W[j] <= X[i]) {
                    mcf.add_edge(i, M + j, 1, mx - V[j]);
                }
            }
        }
        auto [f, c] = mcf.flow(s, t);
        ll res = f * mx - c;
        print(res);
    }
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
