/*
・なんとか自力AC！
・木DP
・さっきの愚直2乗DPをよく観察すると、遷移元dp[v][?]の?には、
　D[v]回以下使ったか、D[v]-1回以下使った場合しか使われないことが分かる。
　D[u]を決める時、なんとかこの2つだけを効率的に決められないか考える。
　ぱっと思いつくのは、ソートして貪欲。とりあえず無制限に取れるdp[v][D[v]]をベースにして、
　これを最大でD[u]個かD[u]-1個、dp[v][D[v]-1]+wの方に置き換える。
　これなら2次元目の添字は2つだけだし、部分木の頂点数程度のソートだけで計算量も収まる。
　いけてそうな気もするけど、全然自信なし。でも結果的にこれで通った。
　注意点としては、dp[v][D[v]-1]+wのが損する場合もあるので
　この場合は取らないようにすることと、D[u]=0な頂点ではD[u]-1個取ることが不可能なので、
　こういった場所は-INFのままにしておく。
・結果として自力ACはしてるんだけど、とても1時間以内とかでは間に合ってないので、
　Dで詰まってなかったとしても、本番中ACはまず無理だっただろうという感じ…。
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
    auto D = LIST(N);
    vvpll nodes(N);
    rep(i, N-1) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        nodes[u].eb(v, w);
        nodes[v].eb(u, w);
    }

    auto dp = list2d(N, 2, -INF);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        vector<ll> diff;
        ll i = 0, sm = 0;
        for (auto [v, w] : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            diff.eb((dp[v][1]+w) - dp[v][0]);
            sm += dp[v][0];
            i++;
        }
        ll m = i;
        sort(diff.rbegin(), diff.rend());
        dp[u][0] = sm;
        rep(i, min(D[u], m)) {
            if (diff[i] <= 0) break;
            dp[u][0] += diff[i];
        }
        if (D[u] > 0) {
            dp[u][1] = sm;
            rep(i, min(D[u]-1, m)) {
                if (diff[i] <= 0) break;
                dp[u][1] += diff[i];
            }
        }
    };
    dfs(dfs, 0, -1);
    ll ans = dp[0][0];
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
