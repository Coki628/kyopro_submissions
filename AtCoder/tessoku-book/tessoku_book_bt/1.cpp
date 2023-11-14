/*
・きっちり自力AC！
・ビット全探索、貪欲
・片側の制約が小さいのでビット全探索して、そうすれば逆側は貪欲で済むやつ。
　いつかの何とかチョコレートを思い出した。あれは本番中通せなくて悔しかったんだ。
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

void solve() {
    ll H, W, K;
    cin >> H >> W >> K;
    vector<string> grid(H);
    cin >> grid;

    ll ans = 0;
    rep(bit, 1LL << H) {
        ll K2 = K - popcount(bit);
        if (K2 < 0) continue;
        auto cur = grid;
        rep(h, H) {
            if (bit >> h & 1) {
                rep(w, W) {
                    cur[h][w] = '#';
                }
            }
        }
        vector<pll> vec;
        rep(w, W) {
            ll cnt = 0;
            rep(h, H) {
                if (cur[h][w] == '#') cnt++;
            }
            vec.eb(cnt, w);
        }
        sort(ALL(vec));
        rep(i, min(K2, W)) {
            auto [_, w] = vec[i];
            rep(h, H) {
                cur[h][w] = '#';
            }
        }
        ll sm = 0;
        rep(h, H) {
            rep(w, W) {
                if (cur[h][w] == '#') sm++;
            }
        }
        chmax(ans, sm);
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
