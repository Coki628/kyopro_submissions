/*
・きっちり自力AC！
・クエリ、区間桁和更新、BITにぶたん
・操作をまとめるのは無理そうに見える。
　だが桁和に更新する操作は、割と早い段階で1桁になってしまい、
　それ以上変化しなくなりそうだと思える。
　BITで集合管理して、1桁になった所は消すようにする。
　これで区間をBITにぶたんで走査していけば、
　操作しなくていい所は飛ばしていけるので高速に処理できる。
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

#include "numbers/digit_sum.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;

    BIT<ll> bit(vector<ll>(N, 1));
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll l, r;
            cin >> l >>  r;
            l--;
            ll x = l;
            while (1) {
                ll nxt = bit.bisearch_fore(x, r - 1, 1);
                if (nxt == -1) break;
                x = nxt;
                A[x] = digit_sum(A[x]);
                if (A[x] < 10) {
                    bit.add(x, -1);
                }
                x++;
            }
        } else {
            ll x;
            cin >> x;
            x--;
            print(A[x]);
        }
    }
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
