/*
・きっちり自力AC！
・S[i]が1のと0ので分けて、並びそのままで1のやつ優先に置く。
　0,1それぞれのグループ内で元の順序を保っておけば、
　元との差異は達成できるうち最小限にできる(はず)。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_dist/base.hpp"

#include "../../../_lib/cpp/_dist/macros.hpp"

#include "../../../_lib/cpp/_dist/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto P = LIST(N);
    rep(i, N) P[i]--;
    string S;
    cin >> S;

    vector<pll> PI;
    rep(i, N) {
        PI.eb(P[i], i);
    }
    sort(ALL(PI));

    vector<ll> P1, P2;
    rep(i, N-1, -1, -1) {
        auto [p, j] = PI[i];
        if (S[j] == '1') {
            P1.eb(j);
        } else {
            P2.eb(j);
        }
    }

    vector<ll> ans(N);
    ll q = N;
    for (auto j : P1) {
        ans[j] = q;
        q--;
    }
    for (auto j : P2) {
        ans[j] = q;
        q--;
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
