/*
・テスト用愚直解
・なんか if (a.size() == b.size()) の判定が合ってないのにYesになってるぽくて、
　文字列の数値としての比較を工夫しないとできなかった。(0埋めしたらうまくいった。)
　デバッグビルドだと大丈夫で、本番ビルドだとそうなる。
　なんか未定義動作とか踏んでんのかなー…。
・TLE,MLE想定の愚直解だったのに、これ投げたら余裕で通ってしまった。
　1万のDPに長さ最大約5000の文字列を陽に持つ感じだから、
　まあ最悪5000万と思えば行けなくはないのか。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(M);

    vector<ll> need = {
        0, 2, 5, 5, 4, 5, 6, 3, 7, 6,
    };
    auto compare = [](const string &a, const string &b) {
        if (a == "*") return true;
        ll n = max(a.size(), b.size());
        return zfill(a, n) < zfill(b, n);
    };

    vector<string> dp(N+1, "*");
    dp[0] = "";
    rep(i, N) {
        if (dp[i] == "*") continue;
        for (auto a : A) {
            if (i+need[a] <= N and compare(dp[i+need[a]], dp[i]+tostr(a))) {
                dp[i+need[a]] = dp[i]+tostr(a);
            }
        }
    }
    auto ans = dp[N] == "*" ? "" : dp[N];
    print(ans);
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
