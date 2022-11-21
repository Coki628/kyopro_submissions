/*
・なんとか自力AC！
・グリッド、実装、ジグザグ
・つらい。種類毎に個数持っておいて、1列ずらしたら1列分削除と追加、みたいに。
　行が変わる時も同様。行の偶奇で列の進行方向を交互にすると、
　行が変わった時も差分が1行だけで済む。がしかしつらい。もっと簡単にできたはず。
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
    ll H, W, N, h, w;
    cin >> H >> W >> N >> h >> w;
    auto grid = listnd(H, W, 0);
    cin >> grid;

    vector<ll> C(N+1);
    ll cnt = 0;
    rep(i, H) {
        rep(j, W) {
            if (C[grid[i][j]] == 0) cnt++;
            C[grid[i][j]]++;
        }
    }

    rep(ch, h) {
        rep(cw, w) {
            C[grid[ch][cw]]--;
            if (C[grid[ch][cw]] == 0) cnt--;
        }
    }
    rep(ch, H-h+1) {
        vector<ll> ans;
        if (ch%2 == 0) {
            rep(cw, W-w+1) {
                // その行最初の列以外、新しい列を追加
                if (cw != 0) {
                    ll dw = cw + w - 1;
                    rep(dh, ch, ch+h) {
                        C[grid[dh][dw]]--;
                        if (C[grid[dh][dw]] == 0) cnt--;
                    }
                }
                ans.eb(cnt);
                if (cw != W-w) {
                    // その行最後の列以外、手前の列を減らす
                    ll dw = cw;
                    rep(dh, ch, ch+h) {
                        if (C[grid[dh][dw]] == 0) cnt++;
                        C[grid[dh][dw]]++;
                    }
                } else {
                    // その行最後の列では行をずらす
                    ll dh = ch;
                    rep(dw, W-w, W) {
                        if (C[grid[dh][dw]] == 0) cnt++;
                        C[grid[dh][dw]]++;
                    }
                    if (ch != H-h) {
                        dh = ch + h;
                        rep(dw, W-w, W) {
                            C[grid[dh][dw]]--;
                            if (C[grid[dh][dw]] == 0) cnt--;
                        }
                    }
                }
            }
        } else {
            rep(cw, W-w, -1, -1) {
                if (cw != W-w) {
                    ll dw = cw;
                    rep(dh, ch, ch+h) {
                        C[grid[dh][dw]]--;
                        if (C[grid[dh][dw]] == 0) cnt--;
                    }
                }
                ans.eb(cnt);
                if (cw != 0) {
                    ll dw = cw + w - 1;
                    rep(dh, ch, ch+h) {
                        if (C[grid[dh][dw]] == 0) cnt++;
                        C[grid[dh][dw]]++;
                    }
                } else {
                    ll dh = ch;
                    rep(dw, 0, w) {
                        if (C[grid[dh][dw]] == 0) cnt++;
                        C[grid[dh][dw]]++;
                    }
                    if (ch != H-h) {
                        dh = ch + h;
                        rep(dw, 0, w) {
                            C[grid[dh][dw]]--;
                            if (C[grid[dh][dw]] == 0) cnt--;
                        }
                    }
                }
            }
        }
        if (ch%2 == 1) {
            reverse(ALL(ans));
        }
        print(ans);
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
