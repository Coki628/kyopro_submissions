/*
参考：https://twitter.com/AllDirections4/status/1555233385034829824
　　　https://twitter.com/titia_til/status/1555232602369380353
・自力ならず。。
・セグ木、実装
・ジグザグをどこまでやってまっすぐ行くかの2N箇所全部見るをやる。
　ジグザグは1マスずつ進んで行き、その位置からまっすぐ行った場合の最小コストは、
　セグ木で一番重い場所を前計算しておくといい。
　セグ木2本でも行けるらしいけど、2行に加えて、
　行きがけ帰りがけの重み付けでも分けたかったので、計4本でやった。
　あとこの時セグ木は最小値を取る位置さえ分かればいいので、
　相対的な重み付けがちゃんとできていれば、各値に足す量は適当でいい。
　実際の値は元のグリッドから取れるから。これに気付くと、だいぶ見通しが立つ。
・元々グリッドの値が「その値まではそのマスに入れない」だったんだけど、
　「その値からそのマスに入れる」のが実装の都合上やりやすかったので(0の場所以外)+1した。
・ボトルネックになる位置が分かりさえすれば、そこまで行くのにその時点から最短で行くのと、
　そのマスに書かれた時間でmax取って、そこに残りの距離の分足せばOK。
・あと最後の1マスが要るかどうかも場合分けが要る。
・色々と注意点が多くて実装大変系だった。でもこういうのちゃんと通せるようになりたいね。
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
    auto grid = listnd(2, N, 0LL);
    rep(i, 2) {
        grid[i] = LIST(N);
        rep(j, N) {
            // 実装上「そのマスに入れる最小時間」のが都合よかったので調整
            if (grid[i][j]) grid[i][j]++;
        }
    }

    // 右に向かう移動用
    auto A = grid;
    // 左に向かう移動用
    auto B = grid;
    rep(i, N) {
        rep(j, 2) {
            // 重み付け
            A[j][i] += N - i;
            B[j][i] += i;
        }
    }
    auto f = [](ll a, ll b) { return max(a, b); };
    vector<SegmentTree<ll, decltype(f)>> sega(2, {f, -INF});
    vector<SegmentTree<ll, decltype(f)>> segb(2, {f, -INF});
    rep(j, 2) {
        sega[j].build(A[j]);
        segb[j].build(B[j]);
    }

    ll ans = INF;
    ll base = -1, h = 0;
    rep(w, N) {
        rep(i, 2) {
            base = max(base+1, grid[h][w]);
            // hの0/1によって時計回り/反時計回りする
            ll cur = base;
            ll mx = sega[h].query(w, N);
            // 右に向かう移動でボトルネックになる位置
            ll wr = sega[h].find_first(w, [&](ll x) { return x >= mx; });
            cur = max(cur+(wr-w), grid[h][wr]);
            cur += (N-1) - wr;
            // 戻りの最後の1マスが終わっているかどうか
            bool done_last = i % 2;
            mx = segb[1-h].query(w+done_last, N);
            // 左に向かう移動でボトルネックになる位置
            ll wl = segb[1-h].find_last(N, [&](ll x) { return x >= mx; });
            cur = max(cur+(N-1)-wl+1, grid[1-h][wl]);
            cur += wl - (w+done_last);
            chmin(ans, cur);
            // 各列で1回目の後だけ行を動かせばジグザグになる
            if (i%2 == 0) h = 1 - h;
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
