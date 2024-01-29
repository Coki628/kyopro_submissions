/*
・なんとか自力AC！むずかった…。
・寄与、区間加算
・a->bに行くとすると、これを近い側で回る時に通る辺を切った場合に損をする。
　各移動M-1回区間加算しておいて、最終的に一番損が軽かった場所を使って実際にシミュ。
　円環だけど2周でサボることもできずとても疲れた。。
・区間加算はいもすが想定解だった。まあ言われればそうだよね。
　そんなことより考察パートと円環の扱いがしんどかったのでそっちが本質と思ってる。
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

#include "datastructure/BIT2.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> X(M);
    cin >> X;
    X--;

    BIT2<ll> bit(N);
    rep(i, M - 1) {
        ll a = X[i];
        ll b = X[i + 1];
        if (a > b) swap(a, b);
        // 正周り
        ll d1 = b - a;
        // 負周り
        ll d2 = (a + N) - b;
        if (d1 < d2) {
            ll val = d2 - d1;
            bit.add(a, b, val);
        } else if (d1 > d2) {
            ll val = d1 - d2;
            bit.add(0, a, val);
            bit.add(b, N, val);
        }
    }
    // 一番損が軽い場所を見つける
    ll mni = -1;
    ll mn = INF;
    rep(i, N) {
        if (chmin(mn, bit[i])) {
            mni = i;
        }
    }
    // 実際にシミュ
    ll ans = 0;
    rep(i, M - 1) {
        ll a = X[i];
        ll b = X[i + 1];
        if (a > b) swap(a, b);
        ll d1 = b - a;
        ll d2 = (a + N) - b;
        if (d1 > d2) {
            if (mni < a or b <= mni) {
                ans += d1;
            } else {
                ans += d2;
            }
        } else if (d1 < d2) {
            if (a <= mni and mni < b) {
                ans += d2;
            } else {
                ans += d1;
            }
        } else {
            ans += d1;
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
