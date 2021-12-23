/*
・最初、mod 26でやろうとしたけど、位置ずらすのとか面倒に思えたので、
　結局zからaに行く所だけ場合分けした。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
string S, T;
    cin >> S >> T;
    ll N = S.size();

    rep(d, 26) {
        if (S == T) {
            Yes();
            return;
        }
        rep(i, N) {
            if (S[i] == 'z') {
                S[i] = 'a';
            } else {
                S[i]++;
            }
        }
    }
    No();
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
