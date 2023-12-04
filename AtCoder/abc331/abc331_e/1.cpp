/*
・きっちり自力AC！
・セグ木に乗せて、その時不要な部分だけ一時的に-INFにする、みたいにやればいい。
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
    ll N, M, L;
    cin >> N >> M >> L;
    vector<ll> A(N), B(M);
    cin >> A >> B;
    vvl adj(N);
    rep(i, L) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].eb(b);
    }

    auto seg = get_segment_tree(B, [](ll a, ll b) { return max(a, b); }, -INF);
    ll ans = -INF;
    rep(i, N) {
        for (auto j : adj[i]) {
            seg.update(j, -INF);
        }
        chmax(ans, A[i] + seg.all());
        for (auto j : adj[i]) {
            seg.update(j, B[j]);
        }
    }
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
