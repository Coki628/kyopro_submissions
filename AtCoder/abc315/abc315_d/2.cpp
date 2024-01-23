/*
・気まぐれ埋め
・自力ならず。やっとupsolveした。むずい。
・キューで効率良くシミュ
・各行/列に各文字種が何個残っているかと、
　文字種が何種類残っているかを適切に管理しながら、
　残り文字種が1種類で個数が2個以上の場所が増えたらキューに追加。
　キュー1回の処理で行/列が1個消えるので、毎回どちらかのループは回してよく、
　更に文字種のループは小さいので、毎回のチェックで雑に回していい。
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
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll M = 26;
    // rows[h][c] := h行に文字種cが残っている個数
    auto rows = listnd(H, M, 0);
    // cols[w][c] := w列に文字種cが残っている個数
    auto cols = listnd(W, M, 0);
    // {文字種, row or col}
    Deque<array<ll, 2>> que;
    // その行/列に何種類残っているか
    vector<ll> ccnth(H), ccntw(W);
    rep(h, H) {
        rep(w, W) {
            rows[h][grid[h][w] - 'a']++;
            cols[w][grid[h][w] - 'a']++;
        }
    }
    // 初期状態でキューに詰めれるものをチェックする
    rep(h, H) {
        ll cc = -1;
        rep(c, M) {
            if (rows[h][c] > 0) {
                ccnth[h]++;
                cc = c;
            }
        }
        if (ccnth[h] == 1 and rows[h][cc] >= 2) {
            que.pb({cc, 0});
        }
    }
    rep(w, W) {
        ll cc = -1;
        rep(c, M) {
            if (cols[w][c] > 0) {
                ccntw[w]++;
                cc = c;
            }
        }
        if (ccntw[w] == 1 and cols[w][cc] >= 2) {
            que.pb({cc, 1});
        }
    }

    ll ans = H * W, hcnt = H, wcnt = W;
    while (que.size()) {
        auto [c, hw] = que.pop_front();
        if (hw == 0) {
            // 1行消す
            ans -= wcnt;
            hcnt--;
            rep(w, W) {
                cols[w][c]--;
                if (cols[w][c] == 0) {
                    ccntw[w]--;
                    // 最後の1種類になって
                    if (ccntw[w] == 1) {
                        ll cc = -1;
                        rep(c, M) {
                            // それが2つ以上残ってるなら
                            if (cols[w][c] >= 2) {
                                cc = c;
                                break;
                            }
                        }
                        if (cc != -1) {
                            // 列wを消す候補に追加
                            que.pb({cc, 1});
                        }
                    }
                }
            }
        } else {
            // 1列消す
            ans -= hcnt;
            wcnt--;
            rep(h, H) {
                rows[h][c]--;
                if (rows[h][c] == 0) {
                    ccnth[h]--;
                    if (ccnth[h] == 1) {
                        ll cc = -1;
                        rep(c, M) {
                            if (rows[h][c] >= 2) {
                                cc = c;
                                break;
                            }
                        }
                        if (cc != -1) {
                            que.pb({cc, 0});
                        }
                    }
                }
            }
        }
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
