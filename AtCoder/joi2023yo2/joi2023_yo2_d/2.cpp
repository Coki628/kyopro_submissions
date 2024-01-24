/*
参考：https://www2.ioi-jp.org/joi/2022/2023-yo2/2023-yo2-t4-review.html
・自力完答ならず。結構いいとこまで行ってたけど、最後の詰めは気付けないやつだったな…。
・色々状態持ってDP
・基本的には部分点5のDPで良い。
　けど、これをWを削れないか悩んだんだけど、そこは方針ハズレだった。
　実際は、Wの値によってDの上限が小さくなるというものだった。
　Dが十分大きい時は、確実に全部の貨物が取れるのでDPする必要がない。
　Wの大きさによってまとめて回収してこれる貨物の数は変わるので、
　実際にシミュしてDがどのくらいあればいいか確認する。
　このシミュに近いのは部分点2をやろうとした時、やろうとしたんだけど、
　なんかうまく作れなくて。よく考えると、後ろからやったらやりやすかった。
　で、これで実質DPする必要のある計算量は3乗で済むので通る。
　なんだけど、450^3だから結構きつい。雑にやったらギリTLE(制約2秒)で、
　vectorを生配列に持ち替えたら通った。(AC0.84秒)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, W, D;
    cin >> N >> W >> D;
    vector<ll> A(N - 1);
    cin >> A;

    // 実質必要なD
    ll D2 = 0;
    // 一番遠い貨物
    ll mxw = N - 1;
    while (mxw >= 1) {
        D2 += mxw * 2;
        mxw -= W;
    }
    // 確実に全て取れる
    if (D >= D2) {
        ll ans = sum(A);
        print(ans);
        return;
    }

    A.insert(A.begin(), 0);
    // auto dp = listnd(2, D + 1, W + 1,  2, -INF);
    ll dp[2][D + 1][W + 1][2];
    rep(i, 2) {
        rep(j, D + 1) {
            rep(k, W + 1) {
                rep(l, 2) {
                    dp[i][j][k][l] = -INF;
                }
            }
        }
    }
    dp[1][0][0][0] = 0;
    rep(i, 1, N) {
        rep(j, D + 1) {
            rep(k, W + 1) {
                // 0 -> i + 1
                if (j + i + 1 <= D) {
                    chmax(dp[(i + 1) % 2][j + i + 1][0][1], dp[i % 2][j][k][0]);
                    chmax(dp[(i + 1) % 2][j + i + 1][1][1], dp[i % 2][j][k][0] + A[i]);
                }
                // i -> i + 1
                if (j + 1 <= D) {
                    chmax(dp[(i + 1) % 2][j + 1][k][1], dp[i % 2][j][k][1]);
                    if (k + 1 <= W) {
                        chmax(dp[(i + 1) % 2][j + 1][k + 1][1], dp[i % 2][j][k][1] + A[i]);
                    }
                }
                // i -> 0
                if (j + i <= D) {
                    chmax(dp[(i + 1) % 2][j + i][0][0], dp[i % 2][j][k][1]);
                    if (k < W) {
                        chmax(dp[(i + 1) % 2][j + i][0][0], dp[i % 2][j][k][1] + A[i]);
                    }
                }
                // 0 -> 0
                chmax(dp[(i + 1) % 2][j][0][0], dp[i % 2][j][k][0]);
                if (j + i * 2 <= D) {
                    chmax(dp[(i + 1) % 2][j + i * 2][0][0], dp[i % 2][j][k][0] + A[i]);
                }
                dp[i % 2][j][k][0] = -INF;
                dp[i % 2][j][k][1] = -INF;
            }
        }
    }
    ll ans = -INF;
    rep(j, D + 1) {
        rep(k, W + 1) {
            chmax(ans, dp[N % 2][j][k][0]);
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
