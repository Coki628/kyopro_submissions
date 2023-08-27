/*
参考：https://twitter.com/N17805722/status/1695432027460518296
・自力ならず。。
・XOR、倍数
・3変数の桁DP、倍数かどうかをmodで状態持つDP
・ビット毎に3変数で桁DP進めるのは考えたけど、
　ビット毎に足し込んでいく際に倍数かどうかは変わってしまうので、そこをどう扱うかが見えず。
　倍数に使われるのが10までと小さいのを何かしら使うとは思ったけど、
　modで状態持つ所に結びつかなかった。ナップザック系だと
　この倍数判定にmodの状態持つDPは何度もやってたのにな…。
・その方針をTLで見た後は、3変数で実装重めだけどだいたいいつもの桁DPだった。
　遷移はxor=0の条件を満たすために立つビット偶奇が偶数になるようにだけやる。
　あと0を数えてしまう問題があったので、そこは0でないかどうかも状態に持たせた。
　10次元の大作ｗだけど、これは解けても良かったなー…。
・あと3回の同じの書くのだるくてsmaller判定を別関数に分けたけど、
　これ普段の桁DPでも流用できそうだな。条件いつもちょっと考えちゃうから、
　ノータイムで書ききるために活用してもいいかも。
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
    ll N;
    cin >> N;
    vector<ll> mod(3);
    cin >> mod;

    auto is_smaller = [](bool n, bool f, bool use) -> int {
        if (f) {
            return 1;
        }
        if (use == n) {
            return f;
        }
        if (not use and n) {
            return 1;
        }
        if (use and not n) {
            return -1;
        }
        assert(0);
    };
    ll L = 60;
    mint dp[L + 1][2][2][mod[0]][2][2][mod[1]][2][2][mod[2]] = {};
    dp[0][0][0][0][0][0][0][0][0][0] = 1;
    rep(i, L) {
        ll n = N >> (L - i - 1) & 1;
        rep(f0, 2) {
            rep(nonzero0, 2) {
                rep(a0, mod[0]) {
                    rep(f1, 2) {
                        rep(nonzero1, 2) {
                            rep(a1, mod[1]) {
                                rep(f2, 2) {
                                    rep(nonzero2, 2) {
                                        rep(a2, mod[2]) {
                                            if (dp[i][f0][nonzero0][a0][f1][nonzero1][a1][f2][nonzero2][a2] == 0) {
                                                continue;
                                            }
                                            rep(bit, 1 << 3) {
                                                if (popcount(bit) % 2 == 1) {
                                                    continue;
                                                }
                                                ll use0 = bit >> 0 & 1;
                                                ll use1 = bit >> 1 & 1;
                                                ll use2 = bit >> 2 & 1;
                                                ll nxf0 = is_smaller(n, f0, use0);
                                                ll nxf1 = is_smaller(n, f1, use1);
                                                ll nxf2 = is_smaller(n, f2, use2);
                                                if (nxf0 == -1 or nxf1 == -1 or nxf2 == -1) {
                                                    continue;
                                                }
                                                ll nxnonzero0 = nonzero0 or use0;
                                                ll nxnonzero1 = nonzero1 or use1;
                                                ll nxnonzero2 = nonzero2 or use2;
                                                ll add0 = use0 ? (1LL << (L - i - 1)) : 0;
                                                ll add1 = use1 ? (1LL << (L - i - 1)) : 0;
                                                ll add2 = use2 ? (1LL << (L - i - 1)) : 0;
                                                dp[i + 1][nxf0][nxnonzero0][(a0 + add0) % mod[0]][nxf1][nxnonzero1][(a1 + add1) % mod[1]][nxf2][nxnonzero2][(a2 + add2) % mod[2]]
                                                    += dp[i][f0][nonzero0][a0][f1][nonzero1][a1][f2][nonzero2][a2];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    mint ans = 0;
    rep(f0, 2) {
        rep(f1, 2) {
            rep(f2, 2) {
                ans += dp[L][f0][1][0][f1][1][0][f2][1][0];
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
