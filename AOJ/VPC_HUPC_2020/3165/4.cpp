/*
参考：https://imoz.jp/algorithms/imos_method.html
・新履修：いもす法の次数拡張
・1次いもす法、区間等差数列加算、区間1次関数加算
・普段やっているいもすは(2次元いもすを含め)通常0次のいもすと呼ばれるもので、
　これを1次関数、2次関数に拡張できるというもの。
　tkppc4_2_fにて2次関数で使ったことで、1次関数のも確認したくなったので実施。
　1次関数と言えば、ちょうど区間等差数列加算なるものがあったのを思い出したのでこの問題を使った。
　この問題みたいに最終的な値だけ欲しいなら、
　セグ木に変なモノ乗せる区間等差数列加算よりずっと簡単にできるのが分かった。
　今回の左端から1,2,3,4とする形であれば、加算する区間を[l,r)とすると、
　imos[l] += 1, imos[r] -= r-l+1, imos[r+1] -= r-l
　の3点の加減でいいみたい。多分2,4,6とかはここに*2するだけでいいはず。
　これを2回累積和すれば元の等差数列加算した値が得られる。
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
#include "template.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;

    vector<ll> imos(N);
    rep(i, Q) {
        ll l, k;
        cin >> l >> k;
        l--;
        ll r = l + k;
        // 3点を加減
        imos[l]++;
        if (r < N) {
            imos[r] -= r - l + 1;
        }
        if (r+1 < N) {
            imos[r+1] += r - l;
        }
    }

    // 2回累積和
    rep(_, 2) {
        rep(i, 1, N) {
            imos[i] += imos[i-1];
        }
    }
    print(imos);
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
