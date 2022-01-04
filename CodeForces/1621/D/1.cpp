/*
参考：https://twitter.com/SSRS_cp/status/1478046206861639684
・自力ならず。。
・題意を読み取るのがちょっと難しい。
　ようは計4Nマスのグリッドがあって、左上Nマスにいる駒を右下Nマスに移動する感じ。
　移動は行か列ごとに、あと盤面の端はサイクルみたいにワープできる。
・ダイクストラしたり累積和取ったりしたけどダメで、もっと簡単だった。。
　右下エリアに出るには右上エリアか左下エリアの4隅、計8箇所のどこか1個開ければいい。
　こんな簡単でいいなら気付くべきだったよなー。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    N *= 2;
    vvl grid(N);
    ll ans = 0;
    rep(i, N) {
        grid[i] = LIST(N);
        if (i >= N/2) {
            rep(j, N/2, N) {
                ans += grid[i][j];
                grid[i][j] = 0;
            }
        }
    }

    ll add = INF;
    chmin(add, grid[0][N/2]);
    chmin(add, grid[0][N-1]);
    chmin(add, grid[N/2-1][N/2]);
    chmin(add, grid[N/2-1][N-1]);
    chmin(add, grid[N/2][0]);
    chmin(add, grid[N/2][N/2-1]);
    chmin(add, grid[N-1][0]);
    chmin(add, grid[N-1][N/2-1]);
    ans += add;
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
