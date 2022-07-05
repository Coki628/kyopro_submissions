/*
・dojo set_f_2_1
・自力AC！やったね。
・任意スワップ、Functional Graph、UnionFind
・サイクル毎に見るやつ。許容量の少ない方から決めていけば良さそう。
　逆にそれで無理なら無理そう。という信念の元に突き進むと、通る。
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
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);
    auto P = LIST(N);
    rep(i, N) P[i]--;

    UnionFind uf(N);
    rep(i, N) {
        uf.merge(i, P[i]);
    }
    vvl adj(N);
    rep(i, N) {
        adj[uf.find(i)].eb(i);
    }
    vector<ll> ptoi(N);
    rep(i, N) {
        ptoi[P[i]] = i;
    }

    vector<pll> ans;
    rep(i, N) {
        if (adj[i].size()) {
            sort(ALL(adj[i]), [&](ll a, ll b) { return A[a] < A[b]; });
            for (auto j : adj[i]) {
                if (P[j] == j) continue;
                ll k = ptoi[j];
                if (A[j] <= B[P[j]] or A[k] <= B[P[k]]) {
                    print(-1);
                    return;
                }
                ans.eb(j+1, k+1);
                swap(P[j], P[k]);
                assert(P[j] == j);
                ptoi[P[j]] = j;
                ptoi[P[k]] = k;
            }
        }
    }
    print(ans.size());
    if (ans.size()) print(ans, '\n');
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
