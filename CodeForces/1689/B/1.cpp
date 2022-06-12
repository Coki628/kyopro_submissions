/*
・きっちり自力AC！
・辞書順最小、貪欲
・とりあえず1から順に置けるならそれが一番良くて、それが無理な場所が来たら、
　1つ後と逆にして置く。末尾だったらそれもできないので、1つ手前とスワップ。
　(この時、1つ手前はi-1とは限らないので、答えの列を直接スワップする。)
　それも無理ならNG。(これは多分N=1の場合のみ)
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
    auto P = LIST(N);
    rep(i, N) P[i]--;

    vector<ll> ans(N);
    rep(i, N) {
        if (P[i] != i) {
            ans[i] = i;
        } elif (i < N-1) {
            ans[i] = i + 1;
            ans[i+1] = i;
            i++;
        } elif (i > 0) {
            ans[i] = i;
            swap(ans[i], ans[i-1]);
        } else {
            print(-1);
            return;
        }
    }
    rep(i, N) ans[i]++;
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
