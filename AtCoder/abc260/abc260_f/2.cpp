/*
参考：https://atcoder.jp/contests/abc260/editorial
・自力ならず。。悔しい。
・鳩の巣原理
・N1,N2は二部グラフになっており、それぞれの側から2頂点取った4頂点が、
　完全二部グラフになってればOK、みたいなのが題意になる。
・N2側の制約が小さいので、そっちの全頂点ペアみたいなループを
　ベースに考えてしまったけど、それではいけなかった。
　N1側から出てる辺に注目すると、これは各頂点から出る辺が多くて3000しかないので、
　この辺(というか行きつくN2側の頂点)の全ペアが回せる。
　これでN2側の頂点ペア(b,c)をキーみたいにすれば、
　N1側で全探索する頂点aと、2回目に同じペアを訪問した時で欲しい4頂点が揃う。
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
    ll N1, N2, M;
    cin >> N1 >> N2 >> M;
    ll N = N1 + N2;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto G = list2d(N2, N2, -1);
    rep(a, N1) {
        for (auto b : nodes[a]) {
            for (auto c : nodes[a]) {
                if (b == c) continue;
                if (G[b-N1][c-N1] == -1) {
                    G[b-N1][c-N1] = a;
                } else {
                    ll d = G[b-N1][c-N1];
                    vector<ll> ans = {a+1, b+1, c+1, d+1};
                    print(ans);
                    return;
                }
            }
        }
    }
    print(-1);
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
