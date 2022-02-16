/*
・dojo set_d_2_3
・自力AC！まあでもこれは虐殺が印象的過ぎて、考察過程よく覚えてたから。。
・期待値の線形性
・まず題意より、同じ頂点が2回以上使われることはない。
　そして自分に到達可能な頂点が1度でも使われると自分は消えてしまう。
　これを前提に話を進める。
・期待値の線形性があるので、全体の操作回数の期待値は、
　個々の頂点が使われる期待値(今回は最大が1だし確率とイコール)を全頂点分足し合わせるといい。
　で、これは「1/その頂点に辿り着ける頂点数」とできる。
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

#include "../../../_lib/cpp/_src/graph/warshall_floyd.hpp"

void solve() {
    ll N;
    cin >> N;
    auto G = list2d(N, N, INF);
    rep(i, N) {
        string s;
        cin >> s;
        rep(j, N) {
            if (s[j] == '1') {
                G[i][j] = 1;
            }
        }
    }

    auto wf = warshall_floyd(G);
    vector<ll> C(N);
    rep(u, N) {
        rep(v, N) {
            if (wf[u][v] < INF) {
                C[v]++;
            }
        }
    }

    ld ans = 0;
    rep(i, N) {
        ans += 1/(ld)C[i];
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
