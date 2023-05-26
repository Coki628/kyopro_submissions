/*
参考：https://twitter.com/YFuka86/status/1661780711437922305
・自力ならず。
・数が合ってさえいれば、実は2パターンのどっちかにできるので最大2種類でいい。
　2値にはしてあったので、あとは正負の入れ替わる所でグループも変えればOK。
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
    string S;
    cin >> S;

    auto C = Counter(S);
    if (C['('] != C[')']) {
        print(-1);
        return;
    }

    vector<ll> B(N);
    rep(i, N) {
        if (S[i] == '(') {
            B[i] = 1;
        } else {
            B[i] = -1;
        }
    }

    ll cur = B[0];
    bool up = cur == 1;
    ll c = 0;
    vector<ll> ans(N);
    ans[0] = c;
    rep(i, 1, N) {
        cur += B[i];
        if (up and cur < 0) {
            c = 1 - c;
            up = false;
        } else if (not up and cur > 0) {
            c = 1 - c;
            up = true;
        }
        ans[i] = c;
    }
    ans++;
    print(max(ans));
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
