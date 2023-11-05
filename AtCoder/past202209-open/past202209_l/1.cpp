/*
参考：https://atcoder.jp/contests/past202209-open/editorial/5876
・自力ならず。こういうDPちゃんと解けるようにしたいね。
・難しいDP、終了時の値を決め打ちする
・Lの条件だけなら、mod 3で状態を持つDPでいけるが、Rの条件をどう処理するかが肝になる。
　これは予め、最終的に使った個数がいくつで終わるかを決め打っておくと、
　各時点でのRの条件で使う個数が全体-Lで求まるので、どのように加点を入れればいいかが分かる。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;
    // add[q][l][r] := q未満をl(mod 3)個、q以上をr(mod 3)個使った時の加点
    auto add = listnd(N + 1, 3, 3, 0LL);
    rep(i, M) {
        ll p, q, l, r;
        cin >> p >> q >> l >> r;
        q--;
        add[q][l][r] += p;
    }

    ll ans = -INF;
    rep(k, 3) {
        // dp[i][j] := i個目まで見て、j個使った場合の最大値
        auto dp = listnd(N + 1, 3, -INF);
        dp[0][0] = add[0][0][k];
        rep(i, N) {
            rep(j, 3) {
                chmax(dp[i + 1][j], dp[i][j] + add[i + 1][j][modulo(k - j, 3LL)]);
                chmax(dp[i + 1][(j + 1) % 3], dp[i][j] + A[i] + add[i + 1][(j + 1) % 3][modulo(k - (j + 1), 3LL)]);
            }
        }
        // 最終的にk個使った場合だけ答えに採用する
        chmax(ans, dp[N][k]);
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
