/*
・自力AC！
・色々動かしてみると、左端の値はそこより左で出現してはダメ、
　右端の値はそこより右で出現してはダメ、の2点を満たすと有効っぽい。
　軽く実験を書いたところ、サンプルも合うのでこれを軸に進める。
　まず右端を固定して条件を満たす左端を検討すると、
　各値について最初に出現したものだけが有効な左端となるので、
　これは出現済をsetに詰めたりして管理できる。
　続いて右端についても検討すると、これはその先での出現有無が条件になるので、
　先にmultisetに全部詰めておいて、進みながら消していくようにした。　
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
    vector<ll> A(N);
    cin >> A;

    // ll ans = 0;
    // rep(l, N) {
    //     rep(r, l, N) {
    //         bool ok = true;
    //         rep(i, l) {
    //             if (A[l] == A[i]) {
    //                 ok = false;
    //                 break;
    //             }
    //         }
    //         rep(i, r + 1, N) {
    //             if (A[r] == A[i]) {
    //                 ok = false;
    //                 break;
    //             }
    //         }
    //         if (ok) ans++;
    //     }
    // }
    // print(ans);
    // -> sample OK!

    set<ll> sel;
    Multiset<ll> ser;
    rep(i, N) {
        ser.insert(A[i]);
    }
    ll ans = 0;
    rep(r, N) {
        sel.insert(A[r]);
        ser.erase(A[r]);
        if (not ser.exist(A[r])) {
            ans += sel.size();
        }
    }
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
