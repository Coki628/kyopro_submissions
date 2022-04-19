/*
参考：https://simezi-tan.hatenadiary.org/entry/20140920/1411169324
　　　https://blog.hamayanhamayan.com/entry/2017/10/04/113042
・連結DP、bitDP、UnionFind、mapでDP
・はまやんさんの記事で紹介されてて、見てみたら未ACだったのでやってみた。
　自力は無理で、解説記事読んだけど、まあちゃんと通せて良かった。
・1列ずつの状態をビットで持っておいて、1列ずつ更新する。
　この時の連結成分の変化を、UFの連結情報を陽に持ってDPを進める。
　要素数は6しかないので、mapで雑に持ち回っても間に合う。
　状態更新の詳細はソース内コメントにて。
　それで合ってるかあんま自信はなかったけど、無事通って良かった。
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
using mint = ModInt<MOD>;
#include "template.hpp"

map<vector<int>, mint> dp[107][1<<6][6];

void solve() {
    ll H, W;
    cin >> H >> W;

    vector<int> init(H);
    iota(ALL(init), 0);
    // dp[i][j][k] := i列目まで見て、開始マスの属するグループ番号がj、連結情報がkの時の通り数
    dp[0][1][0][init] = 1;
    rep(i, W) {
        // 遷移元の1列分のマス目を表すビット
        rep(bit1, 1LL<<H) {
            rep(r, H) {
                for (auto& [info, val] : dp[i][bit1][r]) {
                    // 遷移先の1列分のマス目を表すビット
                    rep(bit2, 1LL<<H) {
                        UnionFind uf1(info), uf2(H);
                        rep(j, H-1) {
                            // 隣り合うマスの連結
                            if (bit2>>j & 1 and bit2>>(j+1) & 1) {
                                uf2.merge(j, j+1);
                            }
                        }
                        // 全マスペア
                        rep(j, H) {
                            rep(k, j+1, H) {
                                // 今回の列で両方塗られていてかつ、遷移元で連結だった場所を繋ぐ
                                if (bit2>>j & 1 and bit2>>k & 1 and uf1.same(j, k)) {
                                    uf2.merge(j, k);
                                }
                            }
                        }
                        // 遷移先での開始マスを含むグループを探す
                        ll nxr = -1;
                        rep(j, H) {
                            if (!(bit2>>j & 1)) continue;
                            bool ok = false;
                            rep(k, H) {
                                if (uf1.same(r, k) and uf2.same(j, k)) {
                                    ok = true;
                                    break;
                                }
                            }
                            if (ok) {
                                nxr = uf2.find(j);
                                break;
                            }
                        }
                        if (nxr == -1) continue;
                        dp[i+1][bit2][nxr][uf2.get_info()] += val;
                    }
                }
            }
        }
    }
    mint ans = 0;
    rep(bit, 1LL<<H) {
        rep(r, H) {
            for (auto& [info, val] : dp[W][bit][r]) {
                // 終了マスが開始マスと同じグループにあれば答えに追加
                if (r  == info[H-1]) {
                    ans += val;
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
