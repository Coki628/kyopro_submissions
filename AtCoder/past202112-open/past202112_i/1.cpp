/*
・きっちり自力AC！
・座圧してダイクストラやる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/dijkstra.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> tmp = {0, N-1}, A(M), B(M), C(M);
    rep(i, M) {
        cin >> A[i] >> B[i] >> C[i];
        A[i]--; B[i]--;
        tmp.eb(A[i]), tmp.eb(B[i]);
    }

    Compress<ll> cp(tmp);
    ll L = cp.size();
    A = cp.zip(A);
    B = cp.zip(B);
    vvpll nodes(L);
    rep(i, M) {
        nodes[A[i]].eb(B[i], C[i]);
        nodes[B[i]].eb(A[i], C[i]);
    }
    rep(i, L-1) {
        ll len = cp.unzip(i+1)-cp.unzip(i);
        nodes[i].eb(i+1, len);
        nodes[i+1].eb(i, len);
    }
    auto res = dijkstra(nodes, 0, L-1);
    print(res[L-1]);
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
