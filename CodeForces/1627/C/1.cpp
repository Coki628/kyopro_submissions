/*
・自力ならず。悔しい。
・木、パスグラフ
・ようはパスグラフの時だけOKで、2,奇素数,2,奇素数みたいにするんだけど、
　これ長らく同じ数何回も使っちゃダメだと思って迷走してた。
　よく見たらそんなことどこにも書いてないね…。
・で、それが分かればまあだいたい解けたようなもんなんだけど、
　パスグラフの辺を交互に塗り分けるのが地味に実装方針手間取った。
　普通に頂点の二分グラフ塗り分けみたいにやろうとすると、
　根から2方向に出てた時ダメになる。なので、葉の場所を予め探して、
　葉の1つを根としてそこから探索したら通った。
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
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    map<pll, ll> edges;
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        edges[{u, v}] = i;
        edges[{v, u}] = i;
    }

    if (N == 2) {
        print(2);
        return;
    }
    if (N == 3) {
        print(mkp(2, 5));
        return;
    }
    rep(i, N) {
        if (nodes[i].size() >= 3) {
            print(-1);
            return;
        }
    }

    vector<ll> ans(N-1, -1);
    auto dfs = [&](auto&& f, ll u, ll prv, ll p) -> void {
        for (ll v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u, 1-p);
            if (p) {
                ans[edges[{u, v}]] = 2;
            } else {
                ans[edges[{u, v}]] = 5;
            }
        }
    };
    rep(i, N) {
        if (nodes[i].size() == 1) {
            dfs(dfs, i, -1, 0);
            break;
        }
    }
    print(ans);
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
