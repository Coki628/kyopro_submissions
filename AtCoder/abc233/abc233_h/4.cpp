/*
・abc283_fで座圧パートのlogが外せたので、こっちでもやってみた。
　やっぱり結構速くなって、AC1.52秒→0.88秒。
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
    int N;
    cin >> N;
    vector<int> U, V;
    vector<pii> cptmp;
    rep(i, N) {
        int x, y;
        cin >> x >> y;
        int u = x - y;
        int v = x + y;
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

    // 下処理で座圧のlogを外す
    vector<int> mpu(400007), mpv(400007);
    int offset = 200000;
    rep(i, -offset, 200007) {
        mpu[i + offset] = cpu[{i, -MOD}];
        mpv[i + offset] = cpv[i];
    }

    int Q;
    cin >> Q;
    rep(i, Q) {
        int x, y, k;
        cin >> x >> y >> k;
        int u = x - y;
        int v = x + y;
        int res = bisearch_min(-1, 200007, [&](int m) {
            // (u,v)を中心とした1辺が2mの正方形領域の中にある点の個数
            int lu = max(u - m + offset, 0);
            int ru = min(u + m + 1 + offset, 400006);
            int lv = max(v - m + offset, 0);
            int rv = min(v + m + 1 + offset, 400006);
            int cnt = wm.range_freq(mpu[lu], mpu[ru], mpv[lv], mpv[rv]);
            return cnt >= k;
        });
        print(res);
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
