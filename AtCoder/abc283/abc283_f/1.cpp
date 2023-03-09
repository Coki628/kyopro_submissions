/*
・やっとupsolveした。
・45度回転、座圧、WM、range_freq、二分探索
・(i,P[i])=(x,y)として座標平面に帰着するとabc233_hと同じ感じにできる。
　でも20万にlog3つさすがにTLつらくてこれはTLE。。
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

#include "datastructure/WaveletMatrix.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<int> P(N);
    cin >> P;
    P--;

    vector<int> U, V;
    vector<pii> cptmp;
    rep(i, N) {
        int u = i - P[i];
        int v = i + P[i];
        U.eb(u);
        V.eb(v);
        cptmp.eb(u, v);
    }

    cptmp.eb(MOD, MOD);
    V.eb(MOD);
    Compress<pii> cpu(cptmp);
    Compress<int> cpv(V);
    int W = cpu.size();
    int H = cpv.size();
    // vの情報を含めて一意にしたu座標をキー、v座標を値としてWMを構成する
    vector<int> wmtmp(W, MOD);
    rep(i, N) {
        wmtmp[cpu[{U[i], V[i]}]] = cpv[V[i]];
    }
    WaveletMatrix<int> wm(wmtmp);

    vector<int> ans(N);
    rep(i, N) {
        int u = i - P[i];
        int v = i + P[i];
        ans[i] = bisearch_min(-1, 400007, [&](int m) {
            // (u,v)を中心とした1辺が2mの正方形領域の中にある点の個数
            int lu = u - m;
            int ru = u + m + 1;
            int lv = v - m;
            int rv = v + m + 1;
            int cnt = wm.range_freq(cpu[{lu, -MOD}], cpu[{ru, -MOD}], cpv[lv], cpv[rv]);
            // 2個以上ある最小値なら自身以外への最短距離が取れる
            return cnt >= 2;
        });
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
