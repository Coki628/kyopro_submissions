/*
・Wavelet Matrix
・2次元平面上である長方形領域に含まれる点の数はWMで高速に求まる。
　x座標が重複する時、こういうのWMには乗らないのかと思ってたけど、
　座圧の情報にy側も含めれば一意になるので対応できる。
・でも今回は該当する全座標列挙しないといけなくて、
　セグ木にぶたんみたいな要領で位置は取れるんだけど、
　TL1秒だしさすがにきつくてTLE。。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/WaveletMatrix.hpp"

void solve() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    vector<pii> cptmp;
    rep(i, N) {
        cin >> X[i] >> Y[i];
        cptmp.eb(X[i], Y[i]);
    }
    cptmp.eb(MOD, MOD);
    Y.eb(MOD);
    Compress<pii> cpx(cptmp);
    Compress<int> cpy(Y);
    int W = cpx.size();
    int H = cpy.size();

    // yの情報を含めて一意にしたx座標をキー、y座標を値としてWMを構成する
    vector<int> wmtmp(W), wmtoi(W);
    rep(i, N) {
        wmtmp[cpx[{X[i], Y[i]}]] = cpy[Y[i]];
        wmtoi[cpx[{X[i], Y[i]}]] = i;
    }
    WaveletMatrix<int, 20> wm(wmtmp);

    int Q;
    cin >> Q;
    vector<tuple<int, int, int, int>> qs;
    rep(i, Q) {
        int sx, tx, sy, ty;
        cin >> sx >> tx >> sy >> ty;
        // 半開区間に
        tx++; ty++;
        qs.eb(cpx[{sx, -MOD}], cpy[sy], cpx[{tx, -MOD}], cpy[ty]);
    }

    rep(i, Q) {
        int sx, sy, tx, ty;
        tie(sx, sy, tx, ty) = qs[i];
        int lx = sx;
        int rx = tx+1;
        vector<int> res;
        while (1) {
            int mx = bisearch_min(lx, rx, [&](int x) {
                return wm.range_freq(lx, x, sy, ty) >= 1;
            });
            if (mx == rx) break;
            res.eb(wmtoi[mx-1]);
            lx = mx;
        }
        if (res.size()) {
            sort(ALL(res));
            for (auto a : res) print(a);
        }
        print();
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
