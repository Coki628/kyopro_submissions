/*
・領域探索、Mo's algorithm、BIT
・ダメ元で作ってみたら通った！
・WMでやった時の要領でx座標をy込みの一意なIDとしておいて、それをWMではなくBITに乗せる。
　クエリ先読みができるので、y座標側はMoで管理。
　Moの区間が動いた時にBITも合わせて出し入れする。
　クエリ返答時はBITにぶたんで、その時範囲内にある座標点を列挙。
・MoだけでもN*√Qで約7000万くらいになるので、
　ここにBITのlog乗ったらいくらBITでもさすがに無理だろーって思ったんだけど、
　やってみたらAC0.34秒。Moの重さはクエリ量にかなり依存するんかな。
　今回Nは50万で多いけどクエリは2万で少ないから。
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

#include "segment/Mo.hpp"

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

    // yの情報を含めて一意にしたx座標をindexとしてBITを構成する
    vector<int> wmtmp(W), bittoi(W);
    vvi adj(H);
    rep(i, N) {
        int x = cpx[{X[i], Y[i]}];
        bittoi[x] = i;
        adj[cpy[Y[i]]].eb(x);
    }

    Mo mo(H);
    BIT<int> bit(W);
    int Q;
    cin >> Q;
    vector<tuple<int, int, int, int>> qs;
    rep(i, Q) {
        int sx, tx, sy, ty;
        cin >> sx >> tx >> sy >> ty;
        // 半開区間に
        tx++; ty++;
        qs.eb(cpx[{sx, -MOD}], cpy[sy], cpx[{tx, -MOD}], cpy[ty]);
        mo.add(cpy[sy], cpy[ty]);
    }
    auto add = [&](int y) -> void {
        for (int x : adj[y]) {
            bit.add(x, 1);
        }
    };
    auto erase = [&](int y) -> void {
        for (int x : adj[y]) {
            bit.add(x, -1);
        }
    };
    vvi ans(Q);
    auto out = [&](int i) -> void {
        auto [sx, sy, tx, ty] = qs[i];
        int cur = sx;
        vector<int> res;
        while (cur < tx) {
            cur = bit.bisearch_fore(cur, tx-1, 1);
            if (cur == -1 or cur >= tx) break;
            res.eb(bittoi[cur]);
            cur++;
        }
        sort(ALL(res));
        ans[i] = res;
    };
    mo.build(add, erase, out);

    rep(i, Q) {
        for (int j : ans[i]) print(j);
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
