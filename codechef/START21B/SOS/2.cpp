/*
参考：https://discuss.codechef.com/t/sos-editorial/97499
・公式解の方針。かしけー。
・木DP、森
・R-Gとなる辺を跨いだペアはNG判定にはならない。(これは思った。)
　この事実を使って、この辺を切断した連結成分毎の森で考えるとする。(まじかってなる。)
　すると、この連結成分内で青が2つ以上あったらそのペア間には
　赤緑どちらかは必ず足りず、NGとなる。ここは気付きにくいと思う。でも確かにそう。
　ここまで考察が進むと、後は連結成分毎にDFSするなりして青の数数えるだけ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/HeavyLightDecomposition.hpp"
#include "../../../_lib/cpp/_src/common/randrange.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        if (S[u] == 'R' and S[v] == 'G' or S[u] == 'G' and S[v] == 'R') {
            continue;
        }
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<bool> visited(N);
    vector<ll> C(N);
    rep(i, N) {
        auto dfs = [&](auto&& f, ll u, ll prv) -> void {
            visited[u] = true;
            C[u] = S[u] == 'B';
            for (ll v : nodes[u]) {
                if (v == prv) continue;
                f(f, v, u);
                C[u] += C[v];
            }
        };
        if (not visited[i]) {
            dfs(dfs, i, -1);
        }
    }
    if (max(C) < 2) {
        Yes();
    } else {
        No();
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
