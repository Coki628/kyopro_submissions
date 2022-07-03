/*
参考：https://www.youtube.com/watch?v=nAnN5fBjEqA&list=PLLeJZg4opYKZMA68O5LKWyNEJEulInKAi&index=3
・ABC高難度埋め
・45度回転、WM、座圧、二分探索
・まず、マンハッタン距離を45度回転させる。解説動画の図ですごく納得したんだけど、
　45度回転するとマンハッタン距離の範囲が、ひし形から長方形になるので、
　データ構造でとても管理しやすくなるんだね。今回はある距離以下の点の個数が数えられれば
　にぶたんでK番目が分かるから、これを長方形領域にプロットできていれば、WMのrange_freqが使える。
　そのままだと負数が使えなかったり、X座標が同じ所に2つの点を置けなかったりするから、
　そこは座圧でよしなにする。(領域探索でもこれやったけど、ここがまあまあ面倒)
　これで適切に準備ができていれば、クエリ先読みも不要で直接全部答えられる。
　計算量はにぶたん、range_freq、座圧と3つのlogが乗ってるんだけど、
　それでも2秒切れて、AC1.52秒だった。(制約7秒)
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

#include "segment/WaveletMatrix.hpp"

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

    int Q;
    cin >> Q;
    rep(i, Q) {
        int x, y, k;
        cin >> x >> y >> k;
        int u = x - y;
        int v = x + y;
        int res = bisearch_min(-1, 200007, [&](int m) {
            // (u,v)を中心とした1辺が2mの正方形領域の中にある点の個数
            int lu = u - m;
            int ru = u + m + 1;
            int lv = v - m;
            int rv = v + m + 1;
            int cnt = wm.range_freq(cpu[{lu, -MOD}], cpu[{ru, -MOD}], cpv[lv], cpv[rv]);
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
