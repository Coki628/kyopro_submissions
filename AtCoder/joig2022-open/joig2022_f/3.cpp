/*
参考：https://www.ioi-jp.org/joig/2021/2022-ho/2022-joig-ho-t6-review.pdf
・自力ならず。。悔しい。
・頂点拡張ダイクストラ
・所持金の減り方と対応するコストの増え方を見抜けなかったのが敗因。
　割る2した回数を状態に持つのは考えたけど、結局コストの増え方が分からなくて無理だった。
　結局必要だったのは「最初は任意の移動がコスト1、割る2の辺を通る度に、
　このコストが(次回から)2倍される」という規則性に気付くことだった。
　所持金に割る2食らうので、手持ち金の価値が2倍になるとも取れると思うと、
　確かにこれは予想しうることなのかもしれない。がしかし思いつくかなこれ…。
　もっとガチャガチャいじってエスパーするとかが現実的な解決策だったか。。
・で、これが分かると、普通に状態増やしてダイクストラやれば全部分かる。
　クエリなのはあんま本質じゃなかったね…。
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
    ll N, M, Q, L;
    cin >> N >> M >> Q >> L;
    vvpll nodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }

    ll K = 30;
    auto res = list2d(N, 30, INF);
    vector<ll> ans(N, INF);
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> que;
    res[0][0] = 1;
    ans[0] = 1;
    que.push({1, 0, 0});
    while (que.size()) {
        auto [dist, u, k] = que.top(); que.pop();
        if (res[u][k] < dist) continue;
        for (auto [v, c] : nodes[u]) {
            ll nxk = c == 2 ? k + 1 : k;
            if (nxk >= K) continue;
            ll nxdist = dist + pow(2, k);
            if (nxdist > L) continue;
            if (chmin(res[v][nxk], nxdist)) {
                chmin(ans[v], nxdist);
                que.push({nxdist, v, nxk});
            }
        }
    }

    rep(i, Q) {
        ll t;
        cin >> t;
        t--;
        if (ans[t] > L) {
            print("Large");
        } else {
            print(ans[t]);
        }
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
