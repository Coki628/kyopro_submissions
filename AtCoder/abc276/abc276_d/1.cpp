/*
・なんとか自力AC！
・素因数分解
・各A[i]を素因数分解。素因数2,3の個数の最小を取っておいて、全部それに合わせる。
　これで合えば減らした素因数の個数が答えで、合わないなら他の素因数が一致していないのでNG。
　なんだけど、最初全部A[0]に合わせる方針を取ろうとした名残で
　ループが[1,N)になってたのが原因でWAを量産。ケアレスミス踏んでつらかった。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vvpli fact(N);
    ll mn2 = INF, mn3 = INF;
    rep(i, N) {
        fact[i] = factorize(A[i]);
        ll cur2 = 0, cur3 = 0;
        for (auto [k, v] : fact[i]) {
            if (k == 2) {
                cur2 = v;
            } elif (k == 3) {
                cur3 = v;
            }
        }
        chmin(mn2, cur2);
        chmin(mn3, cur3);
    }
    ll ans = 0;
    rep(i, N) {
        for (auto [k, v] : fact[i]) {
            if (k == 2) {
                ans += v - mn2;
                A[i] /= pow(2, v - mn2);
            } elif (k == 3) {
                ans += v - mn3;
                A[i] /= pow(3, v - mn3);
            }
        }
    }
    set<ll> se(ALL(A));
    if (se.size() == 1) {
        print(ans);
    } else {
        print(-1);
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
