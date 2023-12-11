/*
・きっちり自力AC！
・グリッド、隣接スワップ、順列全探索、転倒数
・制限のない隣接スワップなので、回数さえあれば任意の順序が達成できる。
　縦横それぞれについて、順列全探索で全パターン見る。
　うまくいくのが見つかったら、転倒数を数えて操作回数とする。
　転倒数ライブラリ最近作ってたので、ちょっと楽できた。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "datastructure/get_inversion.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    auto A = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            cin >> A[h][w];
        }
    }
    auto B = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            cin >> B[h][w];
        }
    }

    vector<ll> P1(H), P2(W);
    iota(ALL(P1), 0);
    iota(ALL(P2), 0);
    ll ans = INF;
    for (auto posh : permutations(P1)) {
        for (auto posw : permutations(P2)) {
            bool ok = true;
            rep(h, H) {
                rep(w, W) {
                    if (A[posh[h]][posw[w]] != B[h][w]) {
                        ok = false;
                        break;
                    }
                }
                if (not ok) break;
            }
            if (ok) {
                ll cnt = get_inversion(posh, false) + get_inversion(posw, false);
                chmin(ans, cnt);
            }
        }
    }
    if (ans >= INF) ans = -1;
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
