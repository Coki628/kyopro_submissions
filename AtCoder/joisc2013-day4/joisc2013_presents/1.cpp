/*
・JOI埋め
・自力AC！やったね。まあ、考察時間かかったけど…。
・SCC、円環のDP
・プレゼントを渡す関係がどういうグラフになるかを観察すると、
　サイクル+そこに入ってくる有向辺、みたいな形に(多分)全部なると思う。
　SCCすれば、上記2種類の部分を適切に分解できる。(成分の頂点数が2以上ならサイクル)
　で、こうなるとまずその依存性の末端にあるサイクル部分を確定させたい。
　これは、円環のDPみたいなやつで、最初の頂点と最後の頂点の状態だけ持つと、
　そこだけDP内でやらずに最後に全探索みたいにして、最適を取れる。
　サイクルになってない成分は、よく考えると自分が渡す側の都合の良いように、
　自分がケーキにするかクッキーにするかを選択できるので、常に良い方を選べる。
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

#include "acl/scc.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N), C(N), D(N);
    rep(i, N) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
        A[i]--;
    }

    scc_graph scc(N);
    rep(i, N) {
        scc.add_edge(i, A[i]);
    }
    auto groups = scc.scc();
    auto dp = list3d(N, 2, 2, -INF);
    ll ans = 0;
    for (auto& group : groups) {
        ll m = group.size();
        ll s = group[0];
        ll t = A[s];
        if (m >= 2) {
            auto dfs = [&](auto&& f, ll u, ll p) -> void {
                if (u == s) {
                    dp[u][p][p] = 0;
                    return;
                }
                ll v = A[u];
                f(f, v, p);
                rep(i, 2) {
                    rep(j, 2) {
                        chmax(dp[u][p][i], dp[v][p][j] + B[u]*(i == j ? C[v] : D[v]));
                    }
                }
            };
            dfs(dfs, t, 0);
            dfs(dfs, t, 1);
            ll mx = -INF;
            rep(i, 2) {
                rep(j, 2) {
                    chmax(mx, dp[t][i][j] + B[s]*(i == j ? C[t] : D[t]));
                }
            }
            ans += mx;
        } else {
            ans += B[s]*max(C[t], D[t]);
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
