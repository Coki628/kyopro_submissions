/*
・JOI埋め
・自力AC！
・筆算の実装
・ランレングスっぽい値を筆算していく。観察してみると、
　両方で同じ値が続く時は(多分)2桁目以降には違いが出ないと分かる。
　よって最初と2桁目以降で分けて、2桁目以降はまとめて処理としていい。
　実装を楽にするために、全体が少ない方を0埋めしたり、
　連続する値が多い方が前にあったらスワップしたりしてる。(それでも十分実装ゲー)
　あとループ抜けた後、最後に残った繰り上がりを忘れずに処理。(1WA)
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

#include "mystl/my_vector.hpp"

void solve() {
    ll N1, N2;
    cin >> N1;
    my_vector<pll> A1, A2;
    ll len1 = 0, len2 = 0;
    rep(i, N1) {
        ll a, l;
        cin >> a >> l;
        A1.eb(a, l);
        len1 += l;
    }
    cin >> N2;
    rep(i, N2) {
        ll a, l;
        cin >> a >> l;
        A2.eb(a, l);
        len2 += l;
    }

    // 0埋め
    if (len1 > len2) {
        ll a = 0, l = len1 - len2;
        A2.insert(A2.begin(), {a, l});
    }
    if (len1 < len2) {
        ll a = 0, l = len2 - len1;
        A1.insert(A1.begin(), {a, l});
    }
    vector<pll> ans;
    ll carry = 0;
    while (A1.size() and A2.size()) {
        if (A1.back().second > A2.back().second) {
            swap(A1, A2);
        }
        auto [a1, l1] = A1.pop();
        auto [a2, l2] = A2.back();
        if (l1 == l2) {
            A2.pop();
        } else {
            A2.back().second -= l1;
        }
        ll nxt1 = a1 + a2 + carry;
        tie(carry, nxt1) = divmod(nxt1, 10LL);
        l1--;
        if (ans.size() and ans.back().first == nxt1) {
            ans.back().second++;
        } else {
            ans.eb(nxt1, 1);
        }
        if (l1 > 0) {
            ll nxt2 = a1 + a2 + carry;
            tie(carry, nxt2) = divmod(nxt2, 10LL);
            if (ans.size() and ans.back().first == nxt2) {
                ans.back().second += l1;
            } else {
                ans.eb(nxt2, l1);
            }
        }
    }
    if (carry) {
        if (ans.size() and ans.back().first == 1) {
            ans.back().second++;
        } else {
            ans.eb(1, 1);
        }
    }
    reverse(ALL(ans));
    print(ans.size());
    print(ans, '\n');
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
