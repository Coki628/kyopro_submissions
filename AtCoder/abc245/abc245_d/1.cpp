/*
・自力ならず？まあもう少し粘ればいけたかもしれないが、TL見ちゃったしね…。
・多項式の除算
・結局やっぱ筆算みたいにやるのが想定みたい。みんなかなり通しててさすが。
・一応、FPSライブラリ使う方法でも通せた。
　そもそも入力受け取りで+1なの見落としてたりとかがあって凡ミスなんだけど、
　それ整えて、いつも使ってる逆元掛ける方じゃなくて、
　除算の方使うとmintではちゃんと想定した答えが出る。
　で、今回は負数があるんだけど、最大値は大きくないので、
　計算後の値を見て、想定される最大値より大きかったらMODを引いてやればOK。
　最大値も大きい時にどうすればいいかは知らない…。
・あと結局、何で逆元掛けるのと除算するので答え変わっちゃうのかはよく分かんないんだよね…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    FPS<mint> A(N+1), C(N+M+1);
    rep(i, N+1) {
        cin >> A[i];
    }
    rep(i, N+M+1) {
        cin >> C[i];
    }

    auto B = C / A;
    vector<ll> ans(M+1);
    rep(i, M+1) {
        ans[i] = B[i];
        if (ans[i] > 1e6) {
            ans[i] -= MOD;
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
