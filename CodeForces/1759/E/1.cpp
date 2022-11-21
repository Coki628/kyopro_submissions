/*
・自力AC！
・ソートして貪欲、順列全探索
・そろそろDPとかしたかったのに貪欲。
　弱い方から倒しまくって損しないのでAはソートしておく。
　1は倒しても得しないので別処理。倒せるだけ倒して無理な時にはアイテム使う脳筋戦略でOK(だと信じて進む)。
　ただしアイテム使用の順序で結果が変わるので、ここは全探索して試す。
　同じやつ考慮しなくても高々3!通りなので問題なし。
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
    ll N, H;
    cin >> N >> H;
    vector<ll> A(N);
    cin >> A;

    ll cnt1 = 0;
    vector<ll> A2;
    rep(i, N) {
        if (A[i] == 1) {
            cnt1++;
        } else {
            A2.eb(A[i]);
        }
    }
    vector<ll> serum = {2, 2, 3};
    sort(ALL(A2));
    N = A2.size();
    ll ans = 0;
    for (auto& perm : permutations(serum)) {
        ll cnt = 0;
        ll cur = H;
        ll j = 0;
        rep(i, N) {
            while (j < 3 and A2[i] >= cur) {
                cur *= perm[j];
                j++;
            }
            if (A2[i] < cur) {
                cur += A2[i] / 2;
                cnt++;
            } else {
                break;
            }
        }
        while (j < 3) {
            cur *= perm[j];
            j++;
        }
        if (cur > 1) {
            cnt += cnt1;
        }
        chmax(ans, cnt);
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
